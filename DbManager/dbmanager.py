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

class Location(Base):
    __tablename__ = 'locations'
    id = Column(Integer, primary_key=True)
    user = Column(String)
    xcoord = Column(Float)
    ycoord = Column(Float)
    panic = Column(SmallInteger)

    def __init__(self, user, xcoord, ycoord, panic):
        self.user = user
        self.xcoord = xcoord
        self.ycoord = ycoord
        self.panic = panic
