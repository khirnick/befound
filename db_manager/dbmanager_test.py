from dbmanager import *
import datetime

"""
НЕ ЗАПУСКАТЬ ЭТОТ ФАЙЛ. СОЗДАН ДЛЯ ДОБАВЛЕНИЯ ТЕСТОВЫХ ДАННЫХ В БД
"""

dbmanager = DbManager('befound', '123456', '212.22.85.121', 'befound')
alarm_button = AlarmButton("123", datetime.datetime.now(),datetime.datetime.now())
dbmanager.add(alarm_button)
