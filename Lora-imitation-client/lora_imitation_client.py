import socket
import threading
import pickle
import sys
import logging
sys.path.append('../../BeFOUND/Network-settings/')
from network_settings import *

class LoRaClient:

 # port - port, to which we send data, ip - ip end point
    def __init__(self, port, host = "127.0.0.1"):
        self.port = port
        self.host = host
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.connect((self.host, self.port))

 # send data to port
    def send_data(self, data):
        self.sock.send(data.encode())
        logging.info('send: {0}'.format(data.encode()))

if __name__ == '__main__':
    logging.basicConfig(format = u'%(levelname)-8s [%(asctime)s] %(message)s',
                        level = logging.DEBUG, filename = u'lora_im.log')
    client = LoRaClient(LORA_IMITATION_PORT_TO_SEND, LORA_IMITATION_HOST_TO_SEND)

    def send_data_repeat_imitate_lora():
        threading.Timer(2.0, send_data_repeat_imitate_lora).start()
        client.send_data("USERNAME;FIRSTNAME;LASTNAME;14234.34;42342.23;EMAIL@EMAIL.COM;8-900-000-00-00;0")

    while True:
        input_msg = input()

        if (input_msg == 's'):
            send_data_repeat_imitate_lora()
        else:
            client.sock.close()
            break
