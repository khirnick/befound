from sqlalchemy import *
from sqlalchemy.orm import *
from sqlalchemy.ext.declarative import *
from sqlalchemy import *
from sqlalchemy.orm import *
import datetime

Base = declarative_base()

class DbManager:
    """
    Класс для мэнеджмента данными в БД
    Используется стек MySQL + pymysql + sqlalchemy (ORM движок)
    """
    def __init__(self, username, password, host, db_name):
        """
        Инициализация БД
        username - имя пользователя для подключения к БД
        password - пароль
        host - IP, где развернута БД
        db_name - имя БД

        self.__engine - движок для подключения к БД
        self.__session - конфигурация класса
        """
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

    def get_by_id(self, obj, id):
        s = self.__session()
        find_row = s.query(obj).get(id)
        s.close()

        return find_row

    def update_time(self, obj):
        s = self.__session()

        obj.updated_at = datetime.datetime.now()
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


class AlarmButton(Base):
    __tablename__ = 'alarm_button'
    id = Column(Integer, primary_key=True)
    mac = Column(String)
    created_at = Column(Date)
    updated_at = Column(Date)

    def __init__(self, mac, created_at, updated_at):
        self.mac = mac
        self.created_at = created_at
        self.updated_at = updated_at


class Coordinates(Base):
    __tablename__ = 'coordinates'
    id = Column(Integer, primary_key=True)
    latitude = Column(Float)
    longitude = Column(Float)
    status = Column(Integer)
    time = Column(Date)
    alarm_button_id = Column(Integer, ForeignKey('alarm_button.id'))
    alarm_button = relationship(AlarmButton)

    def __init__(self, latitude, longitude, status, time, alarm_button):
        self.latitude = latitude
        self.longitude = longitude
        self.status = status
        self.time = time
        self.alarm_button = alarm_button


class UserAb(Base):
    __tablename__ = "user_ab"
    id = Column(Integer, primary_key=True)
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
    id = Column(Integer, primary_key=True)
    date_begin = Column(Date)
    date_end = Column(Date)
    alarm_button_id = Column(Integer, ForeignKey('alarm_button.id'))
    user_id = Column(Integer, ForeignKey('user_ab.id'))
    alarm_button = relationship(AlarmButton)
    user = relationship(UserAb)

    def __init__(self, date_begin, date_end, alarm_button, user):
        self.date_begin = date_begin
        self.date_end = date_end
        self.alarm_button = alarm_button
        self.user = user
