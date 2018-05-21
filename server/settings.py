REDIS_BUCKET_DB_NUM = '0'
REDIS_ACTUAL_DB_NUM = '1'
REDIS_BUCKET_URL = 'redis://localhost/{0}'.format(REDIS_BUCKET_DB_NUM)
REDIS_ACTUAL_URL = 'redis://localhost/{0}'.format(REDIS_ACTUAL_DB_NUM)

CELERY_BROKER_DB_NUM = '2'
CELERY_BROKER_URL = 'redis://localhost/{0}'.format(CELERY_BROKER_DB_NUM)
