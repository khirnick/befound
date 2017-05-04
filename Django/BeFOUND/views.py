from django.shortcuts import render
from .models import Profile, UserAB, AlarmButton, UsedAlarmButton

# Create your views here.
def index(request):
    users_ab = UserAB.objects.users_at_task()
    users_in_alarm = UserAB.objects.users_in_alarm()
    return render(request, 'BeFOUND/index.html', {
        'users_ab': users_ab,
        'users_in_alarm': users_in_alarm
    })