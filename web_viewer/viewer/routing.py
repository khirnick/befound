from django.conf.urls import url

from viewer import consumers


websocket_url_pattern = [
    url(r'^position_data/$', consumers.PositionDataConsumer),
]