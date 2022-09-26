from django.db import models

# Create your models here.
from django.utils.html import format_html


class Audio(models.Model):
    filename = models.CharField(u"文件名", max_length=20)
    filepath = models.CharField(u"文件路径", max_length=100)
    illness = models.CharField(u"疾病类型", max_length=30)
    position = models.CharField(u"检测位置", max_length=30)
    sr = models.IntegerField(u"采样率")
    times = models.CharField(u"音频时长", max_length=10)

    p11 = models.TextField(u"降噪前波形图", null=True)
    p12 = models.TextField(u"降噪前频谱图", null=True)
    p13 = models.TextField(u"降噪前语谱图", null=True)
    p14 = models.TextField(u"降噪前响度曲线", null=True)

    p21 = models.TextField(u"降噪后波形图", null=True)
    p22 = models.TextField(u"降噪后频谱图", null=True)
    p23 = models.TextField(u"降噪后语谱图", null=True)
    p24 = models.TextField(u"降噪后响度曲线", null=True)

    p3 = models.TextField(u"心率曲线", null=True)

    class Meta:
        verbose_name = u"心音数据"  # 单数形式显示的字段
        verbose_name_plural = verbose_name  # 复数形式显示字段，默认admin后台显示复数形式
