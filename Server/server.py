import socket
import threading
import time
import program_info
import sys
sys.path.append('/home/hitryy/_Projects/BeFOUND/BeFOUND/Server-settings/')
from server_settings import *
from connection import Connection

'''Socket multithreading server
for local server on station for communicating with raspberry(ies)'''
class Server:

    # init server based on port, host, count of listeners, client timeout
    def __init__(self, port, host = "127.0.0.1", port_count = 10,
        client_timeout = 8):
        self.port = port
        self.host = host
        self.__port_count = port_count
        self.__client_timeout = client_timeout
        self.__run = False
        self.__connected_clients = []
        print('Server init. ADDRESS: {0}, PORT: {1}'.format(self.host,
                                                            self.port))
        print("'stop' to stop server"
              "'info' to get info about server")

    # represent an instance
    def __repr__(self):
        return 'Server(port={}, host={})'.format(self.port, self.host)

    # start server, each client has own thread
    def start_listen(self):
        self.__sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # set options for reusing address (port)
        self.__sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.__sock.bind((self.host, self.port))
        self.__sock.listen(self.__port_count)
        self.__run = True
        print("Server started... Count of ports to listen: {0}\n"
              "Client timeout: {1} sec."
              .format(self.__port_count, self.__client_timeout))
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
        print("Server now is stopped")

    # for receiving data from client, binds to thread
    def __listen_to_client(self, client, addr, connection):
        while self.__run:
            try:
                self.data = client.recv(1024).decode()
                if (not self.data):
                    print('Client disconnected. ADDRESS: {0}, PORT: {1}'
                        .format(addr[0], addr[1]))
                    break
                print('Received: <{0}> from {1}'.format(self.data, addr[0]))
            except socket.timeout:
                print('Client timeout. ADDRESS: {0}, PORT: {1}'
                    .format(addr[0], addr[1]))
                break

        client.close()
        connection.closed = True

    # stop server
    def stop_listening(self):
        print("Trying to stop server...")
        self.__run = False
        self.__sock.close()
        socket.socket(socket.AF_INET, socket.SOCK_STREAM).connect((self.host,
                                                                   self.port))

    # chech all threads, join thread if connection.closed is True
    def check_clients_working(self):
        working_clients = []
        for c in self.__connected_clients:
            if c.closed:
                c.thread.join()
            else:
                working_clients.append(c)
        return working_clients

if __name__ == '__main__':
    server = Server(LOCAL_SERVER_PORT, LOCAL_SERVER_HOST, LOCAL_SERVER_PORT_COUNT, LOCAL_SERVER_CLIENT_TIMEOUT)
    t = threading.Thread(target=server.start_listen)
    t.start()

    while True:
        input_msg = input()
        if (input_msg == 'stop'):
            server.stop_listening()
            break
        elif (input_msg == 'info'):
            print(repr(server))

    t.join()

    print(program_info.CAPTION)
