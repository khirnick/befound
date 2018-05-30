import json, redis
import pickle
from json import JSONDecodeError

from channels.generic.websocket import WebsocketConsumer
from django.db.models import Avg, Max, Min

from viewer import settings
from viewer.models import PositionData, Carrier


class PositionDataConsumer(WebsocketConsumer):
    def connect(self):
        self.accept()

    def disconnect(self, code):
        pass

    def receive(self, text_data=None, bytes_data=None):
        carrier_id = json.loads(text_data)['carrier_id']
        carrier = Carrier.objects.get(pk=int(carrier_id))
        r = redis.StrictRedis(db=settings.REDIS_ACTUAL_DB_NUM)
        raw_data = r.get(carrier_id)

        if raw_data is None:
            self.send(text_data=json.dumps({
                'unavailable': True
            }))

            return

        data = pickle.loads(raw_data)

        self.send(text_data=json.dumps({
            'carrier': carrier.get_base_info_dict(),
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
        try:
            parsed_income_message = json.loads(text_data)

            carrier_id = int(parsed_income_message['carrier_id'])
            count_of_coordinates = int(parsed_income_message['count_of_coordinates'])

            carrier = Carrier.objects.get(pk=carrier_id)

            total_count_of_coordinates_for_carrier_id = PositionData.objects.filter(carrier_id=carrier_id).count()

            average_speed_on_these_coordinates = PositionData.objects.filter(carrier_id=carrier_id)\
                .order_by('-id')[0:count_of_coordinates]\
                .aggregate(Avg('speed'), Min('speed'), Max('speed'))

            coordinates = PositionData.objects.extra(select={'lng': 'longitude', 'lat': 'latitude'})\
                .values('lat', 'lng')\
                .filter(carrier_id=carrier_id)\
                .order_by('-id')[0:count_of_coordinates]
        except (ValueError, JSONDecodeError) as ex:
            # error_mesage for future logging
            error_message = ''

            if type(ex) == JSONDecodeError:
                error_message = "Error while decoding json"
            elif type(ex) == ValueError:
                error_message = "Invalid input. Input must be a digit"

            self.send(text_data=json.dumps({'error': 'Internal server error'}))
        else:
            self.send(text_data=json.dumps({
                'carrier': carrier.get_base_info_dict(),
                'coordinates': list(coordinates),
                'total_count_of_coordinates_for_carrier_id': total_count_of_coordinates_for_carrier_id,
                'avg_speed': average_speed_on_these_coordinates['speed__avg'],
                'min_speed': average_speed_on_these_coordinates['speed__min'],
                'max_speed': average_speed_on_these_coordinates['speed__max'],
            }))
