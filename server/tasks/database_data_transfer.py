from celery import Celery

import settings

app = Celery('database_data_transfer1', broker=settings.CELERY_BROKER_URL)


@app.on_after_configure.connect
def setup_periodic_tasks(sender, **kwargs):
    sender.add_periodic_task(3.0, do_task.s(), name='every 10 sec')


@app.task
def do_task():
    print(111)

