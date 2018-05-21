from datetime import timedelta

CELERYBEAT_SCHEDULE = {
    'say-hello-every-30-seconds': {
        'task': 'tasks.database_data_transfer.do_task',
        'schedule': timedelta(seconds=3),
    },
}