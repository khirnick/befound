from sqlalchemy import *
from sqlalchemy.orm import *
from sqlalchemy.ext.declarative import *
from sqlalchemy import *
from sqlalchemy.orm import *

Base = declarative_base()

'''
DbManager class for manage db using sqlalchemy, mysql, pymysql
'''
class DbManager:
    def __init__(self, username, password, host, db_name):
        self.username = username
        self.__password = password
        self.host = host
        self.db_name = db_name

        self.__engine = create_engine('mysql+pymysql://{0}:{1}@{2}/{3}'.format(self.username, self.__password, self.host, self.db_name))
        self.__session = sessionmaker()
        self.__session.configure(bind=self.__engine)

        Base.metadata.create_all(self.__engine)

    def add(self, data):
        s = self.__session()

        s.add(data)
        s.commit()
        s.close()

    def add_based_on_count(self, count, data):
        if (count > len(data)):
            return False

        s = self.__session()

        for el in data:
            s.add(el)

        s.commit()
        s.close()

        print('data added to db successfully')
        return True

    def close(self):
        self.__engine.dispose()


class DbManagerRemote(DbManager):
    def __init__(self, username, password, host, db_name, update_count=10):
        super(DbManagerRemote, self).__init__(username, password, host, db_name)
        self.update_count = update_count

####################################################

class AlarmButton(Base):
    __tablename__ = 'alarm_button'
    alarm_button_id = Column(Integer, primary_key=True)
    mac = Column(String)
    created_at = Column(Date)
    updated_at = Column(Date)

    def __init__(self, mac, created_at, updated_at):
        self.mac = mac
        self.created_at = created_at
        self.updated_at = updated_at

class Coordinates(Base):
    __tablename__ = 'coordinates'
    coordinates_id = Column(Integer, primary_key=True)
    latitude = Column(Float)
    longitude = Column(Float)
    status = Column(Integer)
    time = Column(Date)
    alarm_button_id = Column(Integer, ForeignKey('alarm_button.alarm_button_id'))
    alarm_button = relationship(AlarmButton)

    def __init__(self, latitude, longitude, status, time, alarm_button):
        self.latitude = latitude
        self.longitude = longitude
        self.status = status
        self.time = time
        self.alarm_button = alarm_button

class UserAb(Base):
    __tablename__ = "user_ab"
    user_ab_id = Column(Integer, primary_key=True)
    first_name = Column(String)
    last_name = Column(String)
    patronymic = Column(String)
    phone = Column(String)
    email = Column(String)
    birthday = Column(Date)
    created_at = Column(Date)
    updated_at = Column(Date)

    def __init__(self, first_name, last_name, patronymic, phone, email, birthday, created_at, updated_at):
        self.first_name = first_name
        self.last_name = last_name
        self.patronymic = patronymic
        self.phone = phone
        self.email = email
        self.birthday = birthday
        self.created_at = created_at
        self.updated_at = updated_at

class UsedAlarmButton(Base):
    __tablename__ = "used_alarm_button"
    used_ab_id = Column(Integer, primary_key=True)
    date_begin = Column(Date)
    date_end = Column(Date)
    alarm_button_id = Column(Integer, ForeignKey('alarm_button.alarm_button_id'))
    user_ab_id = Column(Integer, ForeignKey('user_ab.user_ab_id'))
    alarm_button = relationship(AlarmButton)
    user_ab = relationship(UserAb)

    def __init__(self, date_begin, date_end, alarm_button, user_ab):
        self.date_begin = date_begin
        self.date_end = date_end
        slef.alarm_button = alarm_button
        self.user_ab = user_ab
#####################################################
