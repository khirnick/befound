import collections

LocationPacket = collections.namedtuple('LocationPacket', 'username, x, y, panic')

class LocationPacketList:

    def __init__(self):
        self.__location_packets = []

    def __repr__(self):
        return self.__location_packets

    @staticmethod
    def get_parsed_packetlist_from_string(line):
        splitted_line = line.split(";")
        return LocationPacket(*splitted_line)

    def add(self, packet):
        if type(packet) == Packet:
            self.__location_packets.append(packet)
        else:
            print('packet argument is not an instance of Packet')

    def clear(self):
        del self.__location_packets[:]

    def print_list(self):
        for el in self.__location_packets:
            print(el)
