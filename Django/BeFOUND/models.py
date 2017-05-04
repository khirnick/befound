from django.db import models
from django.contrib.auth.models import User, UserManager

# Create your models here.
class Profile(User):
    avatar = models.ImageField(upload_to='avatars', default='avatars/user.png')
    # Use UserManager to get the create_user method, etc.
    objects = UserManager()

class UserABManager(models.Manager):
    # Возвращает пользователей, которые сейчас в "походе"
    def users_at_task(self):
        def is_user_at_task(user):
            button = user.used_buttons.last()
            return not button or not button.date_end
        return filter(is_user_at_task, self.all())

# Пользователь кнопки
class UserAB(models.Model):
    first_name = models.CharField(max_length=50)
    last_name = models.CharField(max_length=50)
    patronymic = models.CharField(max_length=50, blank=True)
    phone = models.CharField(max_length=30)
    email = models.EmailField(blank=True)
    birthday = models.DateField()
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)
    objects = UserABManager()

    class Meta:
        db_table = 'user_ab'

    def coordinates(self):
        button = self.alarm_buttons.last()
        if not button:
            return None, None
        coords = button.coordinates_set.last()
        if not coords:
            return None, None
        return coords.latitude, coords.longitude

    def coordinates_str(self):
        latitude, longitude = self.coordinates()
        return '{} {}'.format(latitude, longitude)

    # Статус: 0 - норма, 1 - тревога, 2 - Не в сети
    def status(self):
        used_button = self.alarm_buttons.last()
        if not used_button or not used_button.date_end:
            return 2
        coords = used_button.alarm_button.coordinates_set.last()
        if not coords:
            return 2
        return coords.status

    def status_str(self):
        st = self.status()
        if st == 0:
            return 'Норм'
        elif st == 1:
            return 'Тревога'
        else:
            return 'Не в сети'

    def __str__(self):
        return '{} {} {}'.format(self.last_name, self.first_name, self.patronymic)

# Тревожная кнопка
class AlarmButton(models.Model):
    mac = models.CharField(max_length=30)
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)
    users = models.ManyToManyField(UserAB, related_name='alarm_buttons', through='UsedAlarmButton')

    class Meta:
        db_table = 'alarm_button'

# Связующая таблица пользователь - кнопка
class UsedAlarmButton(models.Model):
    user = models.ForeignKey(UserAB, related_name='used_buttons')
    alarm_button = models.ForeignKey(AlarmButton)
    date_begin = models.DateTimeField(auto_now_add=True)
    date_end = models.DateTimeField(blank=True, null=True)

    class Meta:
        db_table = 'used_alarm_button'

# Координаты перемещения кнопки
class Coordinates(models.Model):
    # Широта
    latitude = models.FloatField()
    # Долгота
    longitude = models.FloatField()
    # Статус: 0 - норма, 1 - тревога
    status = models.IntegerField()
    time = models.DateTimeField(auto_now_add=True)
    alarm_button = models.ForeignKey(AlarmButton)

    class Meta:
        db_table = 'coordinates'
