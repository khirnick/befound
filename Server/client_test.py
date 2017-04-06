import socket

class Client:
    udp_port    = None
    udp_ip      = None
    sock        = None

    # port - port, to which we send data, ip - ip end point
    def __init__(self, port, ip = "127.0.0.1"):
        self.port = port
        self.ip = ip

    # start client
    def start_client(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # stop client
    def stop_client(self):
        self.sock.close()

    # send data to port
    def send_data(self, data):
        self.sock.sendto(data.encode(), (self.udp_ip, self.udp_port))
