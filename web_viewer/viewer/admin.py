from django.contrib import admin

# Register your models here.
from viewer.models import PositionData, Carrier

admin.site.register(PositionData)
admin.site.register(Carrier)