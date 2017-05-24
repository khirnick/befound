# DON'T RUN THIS FILE. BE CAREFUL!
from dbmanager import *
import datetime

dbmanager = DbManager('hitryy', '999', '212.22.92.159', 'be_found')
user_ab = dbmanager.get_by_id(UserAb, 1)
alarm_button = dbmanager.get_by_id(AlarmButton, 1)

used_ab = UsedAlarmButton(datetime.datetime.now(), datetime.datetime.now(), alarm_button, user_ab)
# dbmanager.add(used_ab)

dt = datetime.datetime.now()
print(dt)
dt2 = datetime.datetime.strptime(str(dt), "%Y-%m-%d %H:%M:%S.%f")
