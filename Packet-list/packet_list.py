import collections

Packet = collections.namedtuple('Packet', 'username, x, y, panic')

class PacketList:

    def __init__(self):
        self.__packets = []
        
    def __repr__(self):
        return self.__packets

    @staticmethod
    def get_parsed_packetlist_from_string(line):
        splitted_line = line.split(";")
        return Packet(*splitted_line)

    def add(self, packet):
        if type(packet) == Packet:
            self.__packets.append(packet)
        else:
            print('packet argument is not an instance of Packet')

    def clear(self):
        del self.__packets[:]

    def print_list(self):
        for el in self.__packets:
            print(el)
