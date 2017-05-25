from django.shortcuts import render, HttpResponse, get_object_or_404
from .models import Profile, UserAB, AlarmButton, UsedAlarmButton
import json


class HttpResponseAjax(HttpResponse):
    def __init__(self, status='ok', **kwargs):
        kwargs['status'] = status
        super(HttpResponseAjax, self).__init__(content=json.dumps(kwargs), content_type='application/json')


class HttpResponseAjaxError(HttpResponseAjax):
    def __init__(self, code, message):
        super(HttpResponseAjaxError, self).__init__(status='error', code=code, message=message)


# Create your views here.
def index(request):
    users_ab = UserAB.objects.users_at_task()
    users_in_alarm = UserAB.objects.users_in_alarm()
    return render(request, 'BeFOUND/index.html', {
        'users_ab': users_ab,
        'users_in_alarm': users_in_alarm
    })


def users_coords(request):
    users_ab = UserAB.objects.users_at_task()
    res = []
    for user in users_ab:
        if user.coordinates()[0]:
            res.append(
                {
                    'position': {'lat': user.coordinates()[0], 'lng': user.coordinates()[1]},
                    'label': user.last_name[0],
                    'title': str(user)
                }
            )
    return HttpResponseAjax(
        users=res
    )
