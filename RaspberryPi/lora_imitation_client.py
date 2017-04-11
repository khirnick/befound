import socket
import threading
import pickle

class Client:

 # port - port, to which we send data, ip - ip end point
 def __init__(self, port, host = "127.0.0.1"):
     self.port = port
     self.host = host
     self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
     self.sock.connect((self.host, self.port))

 # send data to port
 def send_data(self, data):
     self.sock.send(data.encode())

client = Client(14000)

def send_data_repeat_imitate_lora():
    threading.Timer(2.0, send_data_repeat_imitate_lora).start()
    client.send_data("Username:USER;x:14234.34;y:42342.23")

while True:
    input_msg = input()

    if (input_msg == 's'):
        send_data_repeat_imitate_lora()
    else:
        client.sock.close()
        break
