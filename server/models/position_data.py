from sqlalchemy import Column, Integer, String, Float, create_engine, ForeignKey, DateTime
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import session, relationship

import settings


engine = create_engine(settings.POSTGRES_URL)
Session = session.sessionmaker(engine)
Base = declarative_base()


class Carrier(Base):
    __tablename__ = 'carriers'

    id = Column('id', Integer, primary_key=True)
    first_name = Column('first_name', String(30))
    last_name = Column('last_name', String(30))
    gender = Column('gender', String(1))
    age = Column('age', Integer)
    email = Column('email', String(50), nullable=True)
    phone = Column('phone', String(20))
    blood_type = Column('blood_type', String(5))
    register_date = Column('register_date', DateTime)

    position_data = relationship('PositionData')

    def __init__(self, first_name, last_name, gender, age, email, phone, blood_type):
        self.first_name = first_name
        self.last_name = last_name
        self.gender = gender
        self.age = age
        self.email = email
        self.phone = phone
        self.blood_type = blood_type


class PositionData(Base):
    __tablename__ = 'position_data'

    id = Column('id', Integer, primary_key=True)
    carrier = Column('carrier_id', Integer, ForeignKey('carriers.id', ondelete="CASCADE"))
    longitude = Column(Float)
    latitude = Column(Float)
    speed = Column(Float)
    alarm_button = Column(String(1))

    def __init__(self, carrier_id, longitude, latitude, speed, alarm_button):
        self.carrier = carrier_id
        self.longitude = longitude
        self.latitude = latitude
        self.speed = speed
        self.alarm_button = alarm_button


Base.metadata.create_all(engine)


def add_position_data(carrier_id, longitude, latitude, speed, alarm_buttom):
    postgres_engine = create_engine(settings.POSTGRES_URL)
    session_class = session.sessionmaker(postgres_engine)
    s = session_class()

    s.add(PositionData(carrier_id, longitude, latitude, speed, alarm_buttom))
    s.commit()
    s.close()



