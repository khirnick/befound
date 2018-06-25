import aioredis
import settings

from tornado import web, ioloop

from handlers.position_data_web_socket_handler import PositionDataWebSocketHandler


def create_redis_connection_pools():
    async def create_redis_connection_pool():
        redis_bucket_connection_pool = await aioredis.create_pool(settings.REDIS_BUCKET_URL, minsize=4, maxsize=10)
        redis_actual_connection_pool = await aioredis.create_pool(settings.REDIS_ACTUAL_URL, minsize=1, maxsize=4)

        PositionDataWebSocketHandler.set_redis_connection_pools(redis_bucket_connection_pool,
                                                                redis_actual_connection_pool)

    ioloop.IOLoop.run_sync(ioloop.IOLoop.current(), create_redis_connection_pool)


def start_app():
    app = web.Application([
        (r'/ws', PositionDataWebSocketHandler)
    ])

    app.listen(8888)
    ioloop.IOLoop.current().start()


def main():
    create_redis_connection_pools()
    start_app()


if __name__ == "__main__":
    main()
