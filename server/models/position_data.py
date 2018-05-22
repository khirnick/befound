import settings
from sqlalchemy import Column, Integer, String, Float


class PositionData(settings.Base):
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


settings.Base.metadata.create_all(settings.engine)


def add_position_data(carrier_id, longitude, latitude, speed, alarm_buttom):
    settings.session.add(PositionData(carrier_id, longitude, latitude, speed, alarm_buttom))
    settings.session.commit()
    settings.session.close()




