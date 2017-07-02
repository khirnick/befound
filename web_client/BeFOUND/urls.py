from django.conf.urls import url

from . import views

urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^users_coords$', views.users_coords, name='users_coords'),
    url(r'^user_track/(?P<user_id>\d+)$', views.user_track, name='user_track'),
]