from django.conf.urls import url

from . import views

urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^users_coords$', views.users_coords, name='users_coords'),
]