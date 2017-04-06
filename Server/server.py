import socket
import threading
import time

class Server:
    udp_port   =    None
    udp_ip     =    None
    sock       =    None
    listen_udp =    None

    # port - server port for receiving, ip - ip end point
    def __init__(self, port, ip="127.0.0.1"):
        self.udp_port = port
        self.udp_ip = ip

    # start server, port detects automatically
    def start_server(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind((self.udp_ip, self.udp_port))
        self.listen_udp = threading.Thread(target=self.receiver_from_udp)
        self.listen_udp.start()

    # stop server, stop the thread for reveiving
    def stop_server(self):
        self.listen_udp.do_run = False
        self.listen_udp.join()
        self.sock.close()

    def receiver_from_udp(self):
        t = threading.currentThread()
        while getattr(t, "do_run", True):
            self.data = self.sock.recv(1024).decode()
            print(self.data)

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

server = Server(11006)
server.start_server()
time.sleep(4)
server.stop_server()
