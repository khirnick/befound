from django.db import models


class Carrier(models.Model):
    first_name = models.CharField(max_length=30)
    last_name = models.CharField(max_length=30)
    gender = models.CharField(max_length=1)
    age = models.IntegerField()
    email = models.CharField(max_length=50, null=True)
    phone = models.CharField(max_length=20)
    blood_type = models.CharField(max_length=5)

    class Meta:
        db_table = 'carriers'


class PositionData(models.Model):
    carrier = models.ForeignKey(Carrier, on_delete=models.CASCADE)
    longitude = models.FloatField()
    latitude = models.FloatField()
    speed = models.FloatField()
    alarm_button = models.CharField(max_length=1)

    class Meta:
        db_table = 'position_data'

