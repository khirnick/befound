from django.conf.urls import url

from viewer import views

app_name = 'viewer'

urlpatterns = [
    url(r'^$', views.index, name='index'),
]