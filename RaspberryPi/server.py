import socket
import threading
import time

'''Socket server UDP non-multithreading for receiving data
from LoRa'''
class ServerMediator:

    def __init__(self, port, port_to_send, socket_timeout = 8, host = "127.0.0.1", host_to_send = "127.0.0.1"):
        self.port = port
        self.host = host
        self.port_to_send = port_to_send
        self.host_to_send = host_to_send
        self.__socket_timeout = socket_timeout
        self.__run = False
        print('Server init. ADDRESS: {0}, PORT: {1}'.format(self.host,
                                                            self.port))
        print("'stop' to stop server"
              "'info' to get info about server")

    def __repr__(self):
        return 'Server(port={}, host={})'.format(self.port, self.host)

    def start_listen_and_send(self):
        self.__sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.__sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.__sock.bind((self.host, self.port))
        self.__sock.settimeout(self.__socket_timeout)

        self.__sock_to_send = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.__sock_to_send.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.__sock_to_send.connect((self.host_to_send, self.port_to_send))

        self.__run = True
        print("Server started... Socket timeout: {0} sec.".format(self.__socket_timeout))
        while self.__run:
            try:
                self.data = self.__sock.recv(1024).decode()
                time.sleep(0.01)
                self.__sock_to_send.send(self.data.encode())
                print('Received: <{0}>'.format(self.data))
            except socket.timeout:
                print('Socket timeout. Dont pay attention to this message')

        self.__sock.close()
        self.__sock_to_send.close()
        print('Server now is stopped')

    def stop_listening(self):
        self.__run = False
        print('Server is closing...')

server = ServerMediator(14000, 15000)
t = threading.Thread(target=server.start_listen_and_send)
t.start()

while True:
    input_msg = input()
    if (input_msg == 'stop'):
        server.stop_listening()
        break
    elif (input_msg == 'info'):
        print(repr(server))

t.join()
