import socket

UDP_IP = "127.0.0.1"
UDP_PORT = 11006
MESSAGE = "info"

sock = socket.socket(socket.AF_INET,
                     socket.SOCK_DGRAM)
sock.sendto(MESSAGE.encode(), (UDP_IP, UDP_PORT))
