import socket
import threading
import pickle
import sys
import logging
import datetime
sys.path.append('../../BeFOUND/Network-settings/')
from network_settings import *
import random

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
        xcoord = random.uniform(54.0, 56.0)
        ycoord = random.uniform(36.0, 38.0)
        client.send_data("1;1;{0};{1};0;{2}".format(round(xcoord, 4), round(ycoord, 4), datetime.datetime.now()))

    while True:
        input_msg = input()

        if (input_msg == 's'):
            send_data_repeat_imitate_lora()
        else:
            client.sock.close()
            break
