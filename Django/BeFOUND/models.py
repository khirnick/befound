from django.db import models
from django.contrib.auth.models import User, UserManager

# Create your models here.
class Profile(User):
    avatar = models.ImageField(upload_to='avatars', default='avatars/user.png')
    # Use UserManager to get the create_user method, etc.
    objects = UserManager()

# Пользователь кнопки
class UserAB(models.Model):
    first_name = models.CharField(max_length=50)
    last_name = models.CharField(max_length=50)
    patronymic = models.CharField(max_length=50, blank=True)
    phone_number = models.CharField(max_length=30)
    email = models.EmailField(blank=True)
    birthday = models.DateField()
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)

    class Meta:
        db_table = 'user_ab'

# Тревожная кнопка
class AlarmButton(models.Model):
    mac = models.CharField(max_length=30)
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)
    users = models.ManyToManyField(UserAB, related_name='alarm_buttons', through='UserAlarmButton')

    class Meta:
        db_table = 'alarm_button'

# Связующая таблица пользователь - кнопка
class UserAlarmButton(models.Model):
    user = models.ForeignKey(UserAB)
    alarm_button = models.ForeignKey(AlarmButton)
    date_begin = models.DateTimeField(auto_now_add=True)
    date_end = models.DateTimeField(blank=True)

    class Meta:
        db_table = 'user_alarm_button'

# Координаты перемещения кнопки
class Coordinates(models.Model):
    # Широта
    latitude = models.FloatField()
    # Долгота
    longitude = models.FloatField()
    # Статус: 0 - норма, 1 - тревога
    status = models.IntegerField()
    time = models.DateTimeField(auto_now_add=True)

    class Meta:
        db_table = 'coordinates'
