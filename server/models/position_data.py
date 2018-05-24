from sqlalchemy import Column, Integer, String, Float, create_engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import session

import settings


engine = create_engine(settings.POSTGRES_URL)
Session = session.sessionmaker(engine)
Base = declarative_base()


class PositionData(Base):
    __tablename__ = 'position_data'

    id = Column(Integer, primary_key=True)
    carrier_id = Column(Integer)
    longitude = Column(Float)
    latitude = Column(Float)
    speed = Column(Float)
    alarm_button = Column(String)

    def __init__(self, carrier_id, longitude, latitude, speed, alarm_button):
        self.carrier_id = carrier_id
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



