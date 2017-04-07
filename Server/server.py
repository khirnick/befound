import socket
import threading
import time
from connection import Connection

'''Socket multithreading server
for local server on station for communicating with raspberry(ies)'''
class Server:

    # port - server port for receiving, ip - ip end point
    def __init__(self, port, host = "127.0.0.1"):
        self.port = port
        self.host = host
        self.__connected_clients = []
        print('Server init. ADDRESS: {0}, PORT: {1}'.format(self.host, self.port))

    # start server, port should detects automatically
    def start_listen(self):
        PORT_COUNT = 10
        CLIENT_TIMEOUT = 8
        self.__sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.__sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.__sock.bind((self.host, self.port))
        self.__sock.listen(PORT_COUNT)
        self.run = True
        print('Server started... Count of ports to listen: {0}\nClient timeout: {1} sec.'.format(PORT_COUNT, CLIENT_TIMEOUT))
        while self.run:
            try:
                client, addr = self.__sock.accept()
                client.settimeout(CLIENT_TIMEOUT)
                connection = Connection()
                client_thread = threading.Thread(target = self.__listen_to_client, args = (client, addr, connection))
                connection.set_thread(client_thread)
                self.__connected_clients.append(connection)
                client_thread.start()
            except:
                pass
            self.__connected_clients = self.check_clients_working()
        print("Trying to stop server...")
        self.__sock.close()
        for c in self.__connected_clients:
            c.thread.join()
        print("Server now is stopped")

    def __listen_to_client(self, client, addr, connection):
        while self.run:
            try:
                self.data = client.recv(4096).decode()
                print(self.data)
            except socket.timeout:
                print('Client timeout. ADDRESS: {0}, PORT: {1}'.format(addr[0], addr[1]))
        client.close()
        connection.closed = True

    def stop_listening(self):
        self.run = False
        self.__sock.close()
        socket.socket(socket.AF_INET, socket.SOCK_STREAM).connect((self.host, self.port))

    def check_clients_working(self):
        working_clients = []
        for c in self.__connected_clients:
            if c.closed:
                c.thread.join()
            else:
                working_clients.append(c)
        return working_clients

    # update db, add
    def update_db(self, data):
        pass

    # sync local db with db on cloud server
    def sync_with_cloud_server(self):
        pass

    # send signal for alarming
    def send_alarm(self, user_dict):
        pass

    # check user's status
    def check_status(self, user):
        pass

server = Server(13433)
t = threading.Thread(target=server.start_listen)
t.start()
t.join()
