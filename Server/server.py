import socket
import threading
import time

class Server:
    __sock          = None
    __listen_udp    = None
    __started       = None
    udp_port        = None
    udp_ip          = None
    data            = None

    # port - server port for receiving, ip - ip end point
    def __init__(self, port, ip = "127.0.0.1"):
        self.udp_port = port
        self.udp_ip = ip

    # start server, port should detects automatically
    def start_server(self):
        if (not self.__started):
            self.__sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            self.__sock.bind((self.udp_ip, self.udp_port))
            self.__listen_udp = threading.Thread(target = self.__receiver_from_udp)
            self.__listen_udp.start()
            self.__started = True
        else:
            print('server is already started')

    # stop server, stop the thread for reveiving
    def stop_server(self):
        if (self.__started):
            self.__listen_udp.do_run = False
            self.__listen_udp.join()
            self.__sock.close()
            self.__sock = None
            self.__started = False
        else:
            print('server is already stopped')

    def __receiver_from_udp(self):
        t = threading.current_thread()
        while getattr(t, "do_run", True):
            self.data = self.__sock.recv(1024).decode()
            print(self.data)

    @property
    def is_alive(self):
        return __started
        
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

server = Server(11020)
server.start_server()
server.stop_server()
