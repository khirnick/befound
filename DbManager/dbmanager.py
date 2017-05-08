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


class Location(Base):
    __tablename__ = 'locations'
    id = Column(Integer, primary_key=True)
    username = Column(String)
    first_name = Column(String)
    last_name = Column(String)
    xcoord = Column(Float)
    ycoord = Column(Float)
    email = Column(String)
    phone = Column(String)
    status = Column(SmallInteger)
    last_update = Column(Date)

    def __init__(self, username, first_name, last_name, xcoord, ycoord, email, phone, status, last_update):
        self.username = username
        self.first_name = first_name
        self.last_name = last_name
        self.xcoord = xcoord
        self.ycoord = ycoord
        self.email = email
        self.phone = phone
        self.status = status
        self.last_update = last_update
