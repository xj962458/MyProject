from django.db import models
import datetime
from django.utils.html import format_html
# Create your models here.


class data(models.Model):
    id = models.AutoField(primary_key=True)  # 检测的次数，自增
    face_image = models.ImageField(u"人脸照片路径", upload_to=str(  # 人脸图片
        'images/{time}'.format(time=datetime.datetime.now().strftime("%Y%m%d-%H%M%S"), null=True)))
    certificate_image = models.ImageField(u"人证照片路径", upload_to=str(  # 人脸图片
        'images/{time}'.format(time=datetime.datetime.now().strftime("%Y%m%d-%H%M%S"), null=True)))
    update_time = models.DateTimeField(
        u"更新时间", auto_now_add=True, null=True)  # 更新的时间
    location = models.CharField("考场位置", max_length=20, null=True)  # 考场位置

    def image_face(self):  # 在后台显示人脸图片
        return format_html(
            '<img src="{}" width="100px"/>',
            self.face_image.url,
        )

    image_face.short_description = u'人脸照片'

    def iamge_certificate(self):  # 在后台显示证件照片
        return format_html(
            '<img src="{}" width="100px"/>',
            self.certificate_image.url,
        )

    iamge_certificate.short_description = u'证件照片'
    similarity = models.CharField("相似度", max_length=20)

    class Meta:
        verbose_name = u"所有记录"   # 单数形式显示的字段
        verbose_name_plural = verbose_name     # 复数形式显示字段，默认admin后台显示复数形式


class data1(models.Model):
    id = models.AutoField(primary_key=True)  # 检测的次数，自增
    face_image = models.ImageField(u"人脸照片路径", upload_to=str(  # 人脸图片
        'images/{time}'.format(time=datetime.datetime.now().strftime("%Y%m%d-%H%M%S"), null=True)))
    certificate_image = models.ImageField(u"人证照片路径", upload_to=str(  # 人脸图片
        'images/{time}'.format(time=datetime.datetime.now().strftime("%Y%m%d-%H%M%S"), null=True)))
    update_time = models.DateTimeField(
        u"更新时间", auto_now_add=True, null=True)  # 更新的时间
    location = models.CharField("考场位置", max_length=20, null=True)  # 考场位置

    def image_face(self):  # 在后台显示人脸图片
        return format_html(
            '<img src="{}" width="100px"/>',
            self.face_image.url,
        )

    image_face.short_description = u'人脸照片'

    def iamge_certificate(self):  # 在后台显示证件照片
        return format_html(
            '<img src="{}" width="100px"/>',
            self.certificate_image.url,
        )

    iamge_certificate.short_description = u'证件照片'
    similarity = models.CharField("相似度", max_length=20)

    class Meta:
        verbose_name = u"未通过记录"   # 单数形式显示的字段
        verbose_name_plural = verbose_name     # 复数形式显示字段，默认admin后台显示复数形式
