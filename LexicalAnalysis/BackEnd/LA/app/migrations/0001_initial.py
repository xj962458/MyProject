# Generated by Django 4.0.6 on 2022-07-31 02:26

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='LA',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('user', models.CharField(max_length=20, verbose_name='用户名')),
                ('time', models.DateTimeField(auto_now_add=True, verbose_name='提交时间')),
                ('sentence', models.TextField(null=True, verbose_name='句子')),
            ],
        ),
    ]
