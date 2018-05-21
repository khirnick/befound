import pickle
import pymemcache

from tornado import websocket


class PositionDataWebSocketHandler(websocket.WebSocketHandler):
    redis_bucket_connection_pool = None
    redis_actual_connection_pool = None

    def __init__(self, application, request, **kwargs):
        super().__init__(application, request, **kwargs)

    # проверяет происхождение запроса на подключение
    def check_origin(self, origin):
        return True

    async def open(self):
        pass

    async def on_message(self, message):
        message_string = str(message)
        pd = self.get_position_data_without_id_dict(message_string)
        await self.add_position_data_to_inmemory_db(pd)

    async def on_close(self):
        pass

    def data_received(self, chunk):
        pass

    async def add_position_data_to_inmemory_db(self, pd):
        pd_id = pd['id']

        serialized_pd = pickle.dumps(pd)

        await self.redis_bucket_connection_pool.execute('rpush', pd_id, serialized_pd)
        await self.redis_actual_connection_pool.execute('set', pd_id, serialized_pd)

    @staticmethod
    def get_position_data_without_id_dict(message):
        splitted_msg = message.split(';')
        return {'id': splitted_msg[0], 'long': splitted_msg[1], 'lat': splitted_msg[2],
                'spd': splitted_msg[3], 'ab': splitted_msg[4]}

    @classmethod
    def set_redis_connection_pools(cls, redis_bucket_connection_pool, redis_actual_connection_pool):
        cls.redis_bucket_connection_pool = redis_bucket_connection_pool
        cls.redis_actual_connection_pool = redis_actual_connection_pool
