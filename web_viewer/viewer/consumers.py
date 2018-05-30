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
        parsed_income_message = json.loads(text_data)

        carrier_id = int(parsed_income_message['carrier_id'])
        count_of_coordinates = int(parsed_income_message['count_of_coordinates'])

        coordinates = PositionData.objects.extra(select={'lng': 'longitude', 'lat': 'latitude'})\
            .values('carrier_id', 'lat', 'lng')\
            .filter(carrier_id=carrier_id)\
            .order_by('-id')[0:count_of_coordinates]

        print(coordinates)

        self.send(text_data=json.dumps({
            'coordinates': list(coordinates)
        }))
