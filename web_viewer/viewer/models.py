import datetime

from django.db import models


class Carrier(models.Model):
    first_name = models.CharField(name='first_name', max_length=30)
    last_name = models.CharField(name='last_name', max_length=30)
    gender = models.CharField(name='gender', max_length=1)
    age = models.IntegerField(name='age')
    email = models.CharField(name='email', max_length=50, null=True)
    phone = models.CharField(name='phone', max_length=20)
    blood_type = models.CharField(name='blood_type', max_length=5)
    register_date = models.DateTimeField(name='register_date', default=datetime.datetime.now())

    class Meta:
        db_table = 'carriers'

    def __str__(self):
        return "{0} {1}".format(self.first_name, self.last_name)

    def get_full_info_dict(self):
        return {'first_name': self.first_name,
                'last_name': self.last_name,
                'gender': self.gender,
                'age': self.age,
                'email': self.email,
                'phone': self.phone,
                'blood_type': self.blood_type,
                }

    def get_base_info_dict(self):
        return {'first_name': self.first_name,
                'last_name': self.last_name,
                'gender': self.gender,
                'age': self.age,
                }


class PositionData(models.Model):
    carrier = models.ForeignKey(name='carrier_id', to=Carrier, on_delete=models.CASCADE)
    longitude = models.FloatField(name='longitude')
    latitude = models.FloatField(name='latitude')
    speed = models.FloatField(name='speed')
    alarm_button = models.CharField(name='alarm_button', max_length=1)

    class Meta:
        db_table = 'position_data'

