import socket

class Client:
    udp_port    = None
    udp_ip      = None
    sock        = None

    def __init__(self, port, ip = "127.0.0.1"):
        self.port = port
        self.ip = ip

    def start_client(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def stop_client(self):
        self.sock.close()

    def send_data(self, data):
        self.sock.sendto(data.encode(), (self.udp_ip, self.udp_port))
