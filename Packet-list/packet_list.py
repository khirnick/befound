import collections

Packet = collections.namedtuple('Packet', 'username, x, y, panic')

class PacketList:

    def __init__(self):
        self.__packets = []

    def __repr__(self):
        return self.__packets

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

pl = PacketList()
pl.add(1)
pl.add(Packet('alex1', '1', 2, False))
pl.add(Packet('alex10', 1, 2, False))
pl.print_list()
