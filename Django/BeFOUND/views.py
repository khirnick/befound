from django.shortcuts import render
from .models import Profile, UserAB, AlarmButton, UserAlarmButton

# Create your views here.
def index(request):
    users_ab = UserAB.objects.users_at_task()
    return render(request, 'BeFOUND/index.html', {
        'users_ab': users_ab
    })