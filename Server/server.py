import socket
import threading
import time
import pickle
import sys
import logging
import pymysql
import datetime
from enum import Enum
sys.path.append('../../BeFOUND/Network-settings/')
sys.path.append('../../BeFOUND/Packet-list/')
sys.path.append('../../BeFOUND/DbManager/')
from network_settings import *
from packet_list import *
from connection import Connection
from program_info import *
from dbmanager import *

class Request(Enum):
    ONLINE_USERS = 0
    ALL_USERS = 1
    USER_TRACK = 2
    NEW_USER = 3
    SET_USER = 4
    NEW_BUTTON = 5
    SET_BUTTON = 6
    DELETE_BUTTON = 7
    USER_BUTTON = 8

'''Socket multithreading server
for local server on station for communicating with raspberry(ies)'''
class Server:


    # init server based on port, host, count of listeners, client timeout
    def __init__(self, port, host = "127.0.0.1", port_count = 10,
                 client_timeout = 8):
        """
        Инициализирует объект сервера
        port - порт сервера
        host - IP сервера
        port_count - максимальное количество клиентов
        client_timeout - время ожидания клиента в секундах

        self.run - запущен ли сервер
        self.__connected_clients - список подключений клиентов
        self.__packet_list - список пришедших пакетов, для отложенного добавления
        self.__packets_counter_adding - количество пакетов при котором следует
        осуществить запись в бд
        self.__dbmanager - объект подключения к БД. Используется модуль pymysql
        """
        self.port = port
        self.host = host
        self.__port_count = port_count
        self.__client_timeout = client_timeout
        self.__run = False
        self.__connected_clients = []
        self.__dbmanager = DbManager('befound', '123456', '212.22.85.121', 'befound')

        log = '{0} Server init. ADDRESS: {1}, PORT: {2}'.format(
            SERVER_NAME,
            self.host,
            self.port)
        logging.info(log)
        print(log)

        print("'stop' to stop server"
              "'info' to get info about server")

    def __repr__(self):
        """
        Вывод информации о сервере: порт и IP
        """
        return 'Server(port={}, host={})'.format(self.port, self.host)

    def start_listen(self):
        """
        Запуск сервера. Начать прослушивания клиентов.
        Прослушивание происходит в бесконечном цикле и заканчивается при
        усановки self.__run в False. Каждое подключение клиента реализовано в
        виде объекта Connection(), который помещается в список соединений.
        После стопа клиента (self.__run в False), ждем когда когда пройдет
        таймаут каждого клиента и закрываем подключение к БД.
        После каждого нового клиента проверяем остальных
        """
        self.__sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # set options for reusing address (port)
        self.__sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.__sock.bind((self.host, self.port))
        self.__sock.listen(self.__port_count)
        self.__run = True

        log = "Server started... Count of ports to listen: {0}\nClient timeout: {1} sec.".format(self.__port_count, self.__client_timeout)
        logging.info(log)
        print(log)

        while self.__run:
            try:
                client, addr = self.__sock.accept()
                client.settimeout(self.__client_timeout)

                connection = Connection()
                client_thread = threading.Thread(
                    target = self.__listen_to_client,
                    args = (client, addr, connection))
                connection.set_thread(client_thread)
                self.__connected_clients.append(connection)

                client_thread.start()
            except:
                pass
            self.__connected_clients = self.check_clients_working()

        self.__sock.close()
        for c in self.__connected_clients:
            c.thread.join()

        self.__dbmanager.close()

        log = "Server now is stopped"
        logging.info(log)
        print(log)

    # for receiving data from client, binds to thread
    def __listen_to_client(self, client, addr, connection):
        """
        Для каждого клиента уникальный поток этого метода для получения данных
        Когда приходят данные, сплитаем их по ';'
        [first_name_id] - id пользователя, которого ищем в БД
        [alarm_button_id] - id тревожной кнопки
        [x] - координата X
        [y] - координата Y
        [panic] - статус оборудования
        [date] - время прихода координат
        После каждого прихода координат, обновляем время в кнопке и время у
        пользователя
        """
        while self.__run:
            try:
                self.data = client.recv(1024).decode()

                if (not self.data):
                    log = 'Client disconnected. ADDRESS: {0}, PORT: {1}'.format(addr[0], addr[1])
                    logging.info(log)
                    print(log)

                    break
                else:
                    log_recv = 'Received: <{0}> from {1}'.format(self.data, addr[0])

                    logging.info(log_recv)
                    print(log_recv)

                    #TODO здесь исправить формат передачи. Уточнить какую информацию передавать на ответ
                    if (self.data[0] == Request.ALL_USERS):
                        all_users = self.__dbmanager.get_all(UserAb)
                        client.send(all_users.encode())

                    splitted_packet = self.data.split(";")

                    user = self.__dbmanager.get_by_id(UserAb, int(splitted_packet[0]))
                    alarm_button = self.__dbmanager.get_by_id(
                        AlarmButton, int(splitted_packet[1]))

                    coordinates = Coordinates(float(splitted_packet[2]),
                                              float(splitted_packet[3]),
                                              int(splitted_packet[4]),
                                              datetime.datetime.strptime(
                                                  splitted_packet[5],
                                                  "%Y-%m-%d %H:%M:%S.%f"),
                                              alarm_button)

                    self.__dbmanager.update_time(user)
                    self.__dbmanager.update_time(alarm_button)

                    self.__dbmanager.add(coordinates)

            except socket.timeout:
                log_ex = 'Client timeout. ADDRESS: {0}, PORT: {1}'.format(addr[0],
                                                                          addr[1])

                logging.warning(log_ex)
                print(log_ex)

                break

        client.close()
        connection.closed = True

    def stop_server(self):
        """
        Остановка сервера, закрываем сокет. Пытаемся законнектиться к самим себе
        для остановки цикла и возбуждения исключения
        """
        log = "Trying to stop server..."
        logging.info(log)
        print(log)

        self.__run = False
        self.__sock.close()
        socket.socket(socket.AF_INET, socket.SOCK_STREAM).connect((self.host,
                                                                   self.port))

    def check_clients_working(self):
        """
        Проверяем всех клиентов. Если соединение закрыто (закончено),
        ждем конец выполнения его потока
        """
        working_clients = []
        for c in self.__connected_clients:
            if c.closed:
                c.thread.join()
            else:
                working_clients.append(c)
        return working_clients

if __name__ == '__main__':
    logging.basicConfig(format = u'%(levelname)-8s [%(asctime)s] %(message)s',
                        level = logging.DEBUG, filename = u'main_s.log')

    server = Server(LOCAL_SERVER_PORT, LOCAL_SERVER_HOST,
                    LOCAL_SERVER_PORT_COUNT, LOCAL_SERVER_CLIENT_TIMEOUT)
    t = threading.Thread(target=server.start_listen)
    t.start()

    while True:
        input_msg = input()
        if (input_msg == 'stop'):
            server.stop_server()
            break
        elif (input_msg == 'info'):
            print(repr(server))

    t.join()

    print(CAPTION)
