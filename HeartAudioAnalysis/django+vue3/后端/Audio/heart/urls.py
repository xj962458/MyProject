from django.urls import path

from . import views

urlpatterns = [
    path('single_fileinfo', views.single_file_info),  # 获取单一文件信息,包含所有信息和图像
    path('all_fileinfo', views.all_file_info),  # 获取所有文件信息,但不包含图像
    path("upload/", views.upload)  # 用于上传文件
]
