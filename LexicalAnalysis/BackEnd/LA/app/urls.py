from django.urls import path

from . import views

urlpatterns = [
    path('analysis', views.analysis),  # 获取结果
    path('random_text', views.random_text)  # 获取随机文本
]
