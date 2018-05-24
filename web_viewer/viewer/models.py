from django.db import models


class PositionData(models.Model):
    carrier_id = models.IntegerField(blank=True, null=True)
    longitude = models.FloatField(blank=True, null=True)
    latitude = models.FloatField(blank=True, null=True)
    speed = models.FloatField(blank=True, null=True)
    alarm_button = models.CharField(max_length=1, blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'position_data'
