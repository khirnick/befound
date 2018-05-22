import pickle

from celery import Celery
import redis

import settings
from models.position_data import PositionData, add_position_data


app = Celery('database_data_transfer', broker=settings.CELERY_BROKER_URL)


@app.on_after_configure.connect
def setup_periodic_tasks(sender, **kwargs):
    sender.add_periodic_task(3.0, transfer_data.s(), name='every 10 sec')


@app.task
def transfer_data():
    r = redis.StrictRedis(db=settings.REDIS_BUCKET_DB_NUM)

    keys = r.keys()
    pipe = r.pipeline()

    for key in keys:
        pipe.lrange(key, 0, -1)

    for key in keys:
        pipe.delete(key)

    position_data_pipe_result = pipe.execute()

    position_data_list = []

    for position_data_list_raw in position_data_pipe_result[0:-len(keys)]:
        for position_data_raw in position_data_list_raw:
            position_data_list.append(pickle.loads(position_data_raw))

    for position_data in position_data_list:
        add_position_data(position_data['id'], position_data['long'], position_data['lat'], position_data['spd'],
                          position_data['ab'])
