# Generated by Django 2.0.5 on 2018-05-30 14:57

import datetime
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('viewer', '0002_auto_20180530_1354'),
    ]

    operations = [
        migrations.AddField(
            model_name='carrier',
            name='register_date',
            field=models.DateTimeField(default=datetime.datetime(2018, 5, 30, 14, 57, 51, 225039)),
        ),
    ]
