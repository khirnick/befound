import aioredis
import settings
import handlers

from handlers.PositionDataWebSocketHandler import PositionDataWebSocketHandler
from tornado import websocket, web, ioloop, gen

if __name__ == "__main__":
    async def create_redis_connection_pool():
        redis_bucket_connection_pool = await aioredis.create_pool(settings.REDIS_BUCKET_URL, minsize=4, maxsize=10)
        redis_actual_connection_pool = await aioredis.create_pool(settings.REDIS_ACTIAL_URL, minsize=1, maxsize=4)

        PositionDataWebSocketHandler.set_redis_connection_pools(redis_bucket_connection_pool,
                                                                redis_actual_connection_pool)

    ioloop.IOLoop.run_sync(ioloop.IOLoop.current(), create_redis_connection_pool)

    app = web.Application([
        (r'/ws', PositionDataWebSocketHandler)
    ])

    app.listen(8888)
    ioloop.IOLoop.current().start()
