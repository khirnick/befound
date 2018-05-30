import json, redis
import pickle

from channels.generic.websocket import WebsocketConsumer

from viewer import settings
from viewer.models import PositionData


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


class RouteConsumer(WebsocketConsumer):
    def connect(self):
        self.accept()

    def disconnect(self, code):
        pass

    def receive(self, text_data=None, bytes_data=None):
        count_of_coordinates = int(json.loads(text_data)['count_of_coordinates'])
        coordinates = PositionData.objects.extra(select={'lng': 'longitude', 'lat': 'latitude'}).values('lat', 'lng').order_by('-id')[0:count_of_coordinates]

        self.send(text_data=json.dumps({
            'coordinates': list(coordinates)
        }))
