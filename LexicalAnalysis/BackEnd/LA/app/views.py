import random
import linecache
import random

from LAC import LAC
from django.http import JsonResponse, HttpResponse
from app.models import LA

# Create your views here.
word_class = {'n': '普通名词', 'f': '方位名词', 's': '处所名词', 'nw': '作品名', 'nz': '其他专名', 'v': '普通动词',
              'vd': '动副词', 'vn': '名动词', 'a': '形容词', 'ad': '副形词', 'an': '名形词', 'd': '副词', 'm': '数量词',
              'q': '量词', 'r': '代词', 'p': '介词', 'c': '连词', 'u': '助词', 'xc': '其他虚词', 'w': '标点符号',
              'PER': '人名', 'LOC': '地名', 'ORG': '机构名', 'TIME': '时间'}


def analysis(request):  # 词性分析
    if request.method == "GET":  # 判断请求类型
        text = request.GET.get("text").replace(" ", "")
    else:
        return HttpResponse("请求类型错误")  # 若不是GET请求，则提示请求错误
    lac = LAC(mode='lac')
    tmp = lac.run(text)
    result = dict(zip(tmp[0], [word_class[i] for i in tmp[1]]))
    add_to_database("root", text)
    return JsonResponse(result)


def add_to_database(user, sentence):  # 将记录添加到数据库
    LA.objects.create(user=user, sentence=sentence)


def random_text(request):  # 产生随机文本
    text = linecache.getline("./static/text.txt", random.randint(0, 100))
    return HttpResponse(text)
