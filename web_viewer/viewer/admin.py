from django.contrib import admin

# Register your models here.
from viewer.models import PositionData, Carrier


class CarrierAdmin(admin.ModelAdmin):
    list_display = ('first_name', 'last_name', 'age', 'gender', 'phone', 'email', 'blood_type')


admin.site.register(PositionData)
admin.site.register(Carrier, CarrierAdmin)