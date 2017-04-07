class Connection:

    def __init__(self):
        self.closed = False
        self.thread = None

    def set_thread(self, t):
        self.thread = t
