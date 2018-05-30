import json, redis
import pickle

from channels.generic.websocket import WebsocketConsumer

from viewer import settings


class PositionDataConsumer(WebsocketConsumer):
    def connect(self):
        self.accept()

    def disconnect(self, code):
        pass

    def receive(self, text_data=None, bytes_data=None):
        carrier_id = json.loads(text_data)['carrier_id']
        r = redis.StrictRedis(db=settings.REDIS_ACTUAL_DB_NUM)
        raw_data = r.get(carrier_id)

        if raw_data is None:
            self.send(text_data=json.dumps({
                'unavailable': True
            }))

            return

        data = pickle.loads(raw_data)

        self.send(text_data=json.dumps({
            'carrier_id': data['id'],
            'long': data['long'],
            'lat': data['lat'],
            'spd': data['spd'],
            'ab': data['ab'],
        }))
