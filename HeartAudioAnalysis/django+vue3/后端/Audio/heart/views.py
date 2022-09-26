import os
from threading import Thread

from django.core import serializers
from django.http import JsonResponse, HttpResponse
from django.shortcuts import redirect
from django.views.decorators.csrf import csrf_exempt

from heart.get_data import AudioProce
from heart.models import Audio


# Create your views here.
def single_file_info(request):  # 指定文件路径，查询音频文件信息
    filepath = None
    if request.method == "GET":  # 判断请求类型
        filepath = request.GET.get("filepath").replace("\\", "/")  # 获取请求的路径
    else:
        return HttpResponse("请求错误")  # 若不是GET请求，则提示请求错误
    if not filepath:  # 若请求体中不包含文件路径，则提示未指定文件路径
        return HttpResponse("未指定文件路径")
    if not os.path.isfile(filepath):  # 判断是否指定的文件路径是否存在，若不存在则提示不是有效路径
        return HttpResponse("不是有效路径")
    filename = filepath.split("/")[-1]  # 获取请求时包含的文件名称

    # 去数据库查询具体数据，返回结果为json字符串
    data = Audio.objects.filter(filename=filename)
    if data:  # 若查找到数据，则直接返回数据
        audio_data = serializers.serialize('json', data, fields=(
            "filename", "sr", "illness", "times", "position", "p11", "p12", "p13", "p14", "p21", "p22", "p23", "p24",
            "p3"))
        return HttpResponse(audio_data, content_type='application/json')
    else:  # 若未查找到数据，则调用音频处理类生成数据，再从数据库查询后返回数据
        audio = AudioProce(filepath)  # 调用AudioProce类生成数据并存入数据库
        audio_data = serializers.serialize('json', Audio.objects.filter(filename=filename), fields=(  # 重新查找数据
            "filename", "sr", "illness", "position", "times", "p11", "p12", "p13", "p14", "p21", "p22", "p23", "p24",
            "p3"))
        return HttpResponse(audio_data, content_type='application/json')


file_type = ['wav', 'ogg', 'mp3']  # 支持上传的文件格式


@csrf_exempt  # 标识该视图可以被跨域访问
def upload(request):  # 处理用户上传文件请求
    if request.method == "POST":  # 判断请求的类型是否为POST请求
        filename = str(request.FILES['file'])  # 获取请求发来的文件名称
        if filename.split(".")[-1] not in file_type:  # 判断上传的文件类型，若不符合规范，则返回上传文件类型错误
            return JsonResponse({'msg': '上传文件类型错误', 'success': False})
        FileOperation.handle_upload_file(request.FILES.get('file'), filename)  # 将接受的文件数据写入到指定的文件中
        filepath = os.path.join(r'./static/audio_data/', filename)  # 获取文件路径
        if not os.path.exists(filepath):
            t = Thread(target=AudioProce, args=[filepath])  # 调用多线程去处理数据
            t.start()  # 多线程开始
        return JsonResponse({'msg': '上传成功', 'success': True})
    else:
        return JsonResponse({"msg": "错误的请求", 'success': False})


# 将上传的文件写入到具体文件
class FileOperation:
    @staticmethod  # 声明为类的静态方法，可以直接通过类名调用
    def handle_upload_file(file, filename):
        path = r'./static/audio_data/'  # 文件保存路径
        if not os.path.exists(path):  # 判断文件夹是否存在
            os.makedirs(path)
        with open(os.path.join(path, filename), 'wb') as destination:  # 将前端发送的文件内容写入到具体的文件中
            for chunk in file.chunks():
                destination.write(chunk)


def all_file_info(request):  # 从数据库查询所有文件的信息
    data = serializers.serialize('json', Audio.objects.all(),
                                 fields=("filename", "sr", "illness", "position", "times"))  # 从数据库中获取文件名 采样率 疾病类型 采集位置
    return HttpResponse(data, content_type='application/json')


# 首页
def index(request):
    return redirect("http://localhost:8080/")
