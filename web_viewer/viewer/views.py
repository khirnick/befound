from django.shortcuts import render

# Create your views here.


def viewer_realtime_monitoring(request):
    return render(request, 'viewer/viewer_realtime_monitoring.html')


def viewer_route(request):
    return render(request, 'viewer/viewer_route.html')
