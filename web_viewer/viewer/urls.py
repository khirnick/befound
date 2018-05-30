from django.conf.urls import url

from viewer import views

app_name = 'viewer'

urlpatterns = [
    url(r'^$', views.viewer_realtime_monitoring, name='viewer_realtime_monitoring'),
    url(r'^viewer_route$', views.viewer_route, name='viewer_route'),
]