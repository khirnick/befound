from dbmanager import *
import datetime

dbmanager = DbManager('hitryy', '999', '212.22.92.159', 'be_found')
user_ab = UserAb("nikita", "khirnyy", "123", "9055120310", "khirnick@yandex.ru", datetime.datetime.now(), datetime.datetime.now(), datetime.datetime.now())
alarm_button = AlarmButton("255.255.255.0", datetime.datetime.now(), datetime.datetime.now())
coordinates = Coordinates(25.5, 25.5, 1, datetime.datetime.now(), alarm_button)
dbmanager.add(user_ab)
dbmanager.add(alarm_button)
dbmanager.add(coordinates)
