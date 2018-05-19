from tornado import websocket, web, ioloop


class DataHandlerWebSocket(websocket.WebSocketHandler):
    # проверяет происхождение запроса на подключение
    def check_origin(self, origin):
        return True

    def open(self):
        print("connection openned")

    def on_message(self, message):
        print("message come: {0}".format(type(message)))

    def on_close(self):
        print("connection closed")


if __name__ == "__main__":
    app = web.Application([
        (r'/ws', DataHandlerWebSocket)
    ])

    app.listen(8888)
    ioloop.IOLoop.current().start()

