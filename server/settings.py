from sqlalchemy import create_engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import session


REDIS_BUCKET_DB_NUM = 0
REDIS_ACTUAL_DB_NUM = 1
REDIS_BUCKET_URL = 'redis://localhost/{0}'.format(REDIS_BUCKET_DB_NUM)
REDIS_ACTUAL_URL = 'redis://localhost/{0}'.format(REDIS_ACTUAL_DB_NUM)

CELERY_BROKER_DB_NUM = 2
CELERY_BROKER_URL = 'redis://localhost/{0}'.format(CELERY_BROKER_DB_NUM)

REDIS_ACTUAL_EXPIRE_SECONDS = 30

POSTGRES_DB_NAME = 'befound'
POSTGRES_USER = 'khirnick'
POSTGRES_PSW = '123456'
POSTGRES_ADDRESS = 'localhost'
POSTGRES_PORT = '5432'
POSTGRES_URL = 'postgresql+psycopg2://{0}:{1}@{2}:{3}/{4}'.format(POSTGRES_USER, POSTGRES_PSW,
                                                                  POSTGRES_ADDRESS, POSTGRES_PORT,
                                                                  POSTGRES_DB_NAME)

engine = create_engine(POSTGRES_URL)
Session = session.sessionmaker(engine)
session = Session()
Base = declarative_base()
