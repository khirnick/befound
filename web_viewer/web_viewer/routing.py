from channels.auth import AuthMiddlewareStack
from channels.routing import ProtocolTypeRouter, URLRouter
from django.urls import path

import viewer.routing
from viewer.consumers import PositionDataConsumer, RouteConsumer

application = ProtocolTypeRouter({
    "websocket": AuthMiddlewareStack(
        URLRouter([
            path("ws/position_data/", PositionDataConsumer),
            path("ws/route/", RouteConsumer),
        ]),
    ),
})