import socket
import pickle

class Client:

    # port - port, to which we send data, ip - ip end point
    def __init__(self, port, host = "127.0.0.1"):
        self.port = port
        self.host = host
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((self.host, self.port))

    # send data to port
    def send_data(self, data):
        self.sock.send(data.encode())

client = Client(13433)

while True:
    input_msg = input()

    if (input_msg == 's'):
        client.send_data("msg")
    else:
        client.sock.close()
        break
