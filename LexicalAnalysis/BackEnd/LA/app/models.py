from django.db import models


# Create your models here.
class LA(models.Model):
    user = models.CharField(u"用户名", max_length=20)
    time = models.DateTimeField(u"提交时间", auto_now_add=True)
    sentence = models.TextField(u"句子", null=True)
