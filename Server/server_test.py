import unittest
import server

class ServerPortTestCase(unittest.TestCase):

    def test_ports(self):
        servers = [
            [Server(11900), 11900],
            [Server(12000), 12000]
        ]

        for server, port in servers:
            self.assertEqual(server.udp_port, port)

suite = unittest.defaultTestLoader.loadTestsFromTestCase(ServerPortTestCase)
unittest.TextTestRunner().run(suite)
