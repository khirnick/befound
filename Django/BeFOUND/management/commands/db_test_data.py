# -*- coding: utf-8 -*-
from django.core.management.base import BaseCommand, CommandError
from BeFOUND.models import Profile
import random
import time

# Команда для генерации тестовых данных
# ./manage db_test_data
class Command(BaseCommand):
    def handle(self, *args, **options):
        # Создание пользователей
        for i in range(0, 30):
            Profile(
                first_name=random.choice(
                    ["Александр", "Саша", "Петя", "Вася", "Иван", "Маша", "Даша", "Нина", "Макс", "Артём", "Никита"]
                ),
                last_name=random.choice(
                    ["Кирьяненко", "Иванов", "Петров", "Сидоров", "Хирный", "Колотовкин", "Куклина", "Попов", "Самарёв"]
                ),
                email=str(i) + '_' + str(time.time()) + random.choice(
                    ["kiryanenkoav@mail.ru", "alex@mail.ru", "petrov@mail.ru", "qwerty@mail.ru", "krot@mail.ru"]
                ),
                username=random.choice(
                    ["kiryanenko", "alex", "username", "sidor", "krot", "qwerty", "samsa", 'super', 'hitryy', 'grenom']
                ) + str(i) + '_' + str(time.time())
            ).save()
        users = Profile.objects.all()

        # TODO: Написать генерацию тестовых данных для каждой модели
