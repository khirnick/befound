import threading
import paho.mqtt.client as mqtt
import socket
import pickle
import sys
sys.path.append('../../BeFOUND/Network-settings/')
from network_settings import *

TOPIC_SUB = 'devices/lora/00'

class LoRaMqttClient(mqtt.Client):

	def __init__(self):
		super().__init__()
		self.lora_udp_client = LoRaUdpClient(MEDIATOR_SERVER_HOST,
											 MEDIATOR_SERVER_PORT)

		self.on_connect = self.on_connect_event
		self.on_message = self.on_message_event

		self.connect('localhost', 1883, 60)
		self.loop_forever()

	def on_connect_event(self, client, userdata, rc, x):
		print('Connected with code: ' + str(rc['session present']))
		self.subscribe(TOPIC_SUB)

	def on_message_event(self, client, userdata, msg):
		message = msg.payload.decode('utf-8')

		self.lora_udp_client.send_data(message)
		print("Topic: {}, message: <{}>".format(msg.topic, message))

class LoRaUdpClient():

	def __init__(self, host, port):
		self.port = port
		self.host = host
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		self.sock.connect((self.host, self.port))

	def send_data(self, data):
		self.sock.send(data.encode())

if __name__ == '__main__':
	lora_mqtt_client = LoRaMqttClient()
