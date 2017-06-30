import collections

Packet = collections.namedtuple('Packet', 'first_name_id alarm_button_id x y panic date')

class PacketList:

    def __init__(self):
        self.__packets = []

    def __repr__(self):
        return self.__packets

    def __iter__(self):
        for p in self.__packets:
            yield p

    @property
    def length(self):
        return len(self.__packets)

    @staticmethod
    def get_parsed_packet_from_string(line):
        splitted_line = line.split(";")
        print(len(splitted_line))
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
