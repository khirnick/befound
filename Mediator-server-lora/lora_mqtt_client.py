import threading
import paho.mqtt.client as mqtt
import socket
import pickle

topic_sub = 'devices/lora/00'

class LoRaMqttClient():
	
	def __init__(self):
		self.lora_udp_client = LoRaUdpClient(30010, '10.42.0.76')		

		self.client = mqtt.Client()
		self.client.on_connect = self.on_connect
		self.client.on_message = self.on_message

		self.client.connect('localhost', 1883, 60)
		self.client.loop_forever()

	def on_connect(self, client, userdata, rc, x):
		print('Connected with result code: ' + str(rc))
		self.client.subscribe(topic_sub)

	def on_message(self, client, userdata, msg):
		print(msg.topic + " " + str(msg.payload))
		self.lora_udp_client.send_data(str(msg.payload))

class LoRaUdpClient():
	
	def __init__(self, port, host):
		self.port = port
		self.host = host
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		self.sock.connect((self.host, self.port))

	def send_data(self, data):
		self.sock.send(data.encode())

if __name__ == '__main__':
	lora_mqtt_client = LoRaMqttClient()