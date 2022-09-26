from django.contrib import admin
from django.utils.safestring import mark_safe

from heart.models import Audio


# Register your models here.
@admin.register(Audio)
class AudioAdmin(admin.ModelAdmin):
    list_display = ['filename', 'filepath', 'illness', 'position', 'sr', "times", 'p11_display', 'p12_display',
                    'p13_display', 'p14_display', 'p21_display', 'p22_display', 'p23_display', 'p24_display',
                    'p3_display']
    list_per_page = 10

    list_filter = ('filename', 'filepath', 'illness', 'position', "times")  # 过滤器
    search_fields = ('filename', 'filepath', 'illness', 'position', "times")  # 搜索字段
    admin.site.site_header = "心音分析管理"
    admin.site.site_title = "心音分析管理"

    # 筛选器
    def p11_display(self, obj):
        return mark_safe(
            '<img width="100%" height="90%" boder="2px" alter="降噪前波形图" src="data:image/png;base64,{}"/>'.format(
                obj.p11))

    def p12_display(self, obj):
        return mark_safe(
            '<img width="100%" height="90%" boder="2px" alter="降噪前频谱图" src="data:image/png;base64,{}"/>'.format(
                obj.p12))

    def p13_display(self, obj):
        return mark_safe(
            '<img width="100%" height="90%" boder="2px" alter="降噪前语谱图" src="data:image/png;base64,{}"/>'.format(
                obj.p13))

    def p14_display(self, obj):
        return mark_safe(
            '<img width="100%" height="90%" boder="2px" alter="降噪前响度曲线" src="data:image/png;base64,{}"/>'.format(
                obj.p14))

    def p21_display(self, obj):
        return mark_safe(
            '<img width="100%" height="90%" boder="2px" alter="降噪后波形图" src="data:image/png;base64,{}"/>'.format(
                obj.p21))

    def p22_display(self, obj):
        return mark_safe(
            '<img width="100%" height="90%" boder="2px" alter="降噪后频谱图" src="data:image/png;base64,{}"/>'.format(
                obj.p22))

    def p23_display(self, obj):
        return mark_safe(
            '<img width="100%" height="90%" boder="2px" alter="降噪后语谱图" src="data:image/png;base64,{}"/>'.format(
                obj.p23))

    def p24_display(self, obj):
        return mark_safe(
            '<img width="100%" height="90%" boder="2px" alter="降噪后响度曲线" src="data:image/png;base64,{}"/>'.format(
                obj.p24))

    def p3_display(self, obj):
        return mark_safe(
            '<img width="100%" height="90%" boder="2px" alter="心率曲线" src="data:image/png;base64,{}"/>'.format(
                obj.p3))

    def has_add_permission(self, request):  # 禁止添加
        return False

    p11_display.short_description = u"降噪前波形图"
    p12_display.short_description = u"降噪前频谱图"
    p13_display.short_description = u"降噪前语谱图"
    p14_display.short_description = u"降噪响度曲线"

    p21_display.short_description = u"降噪后波形图"
    p22_display.short_description = u"降噪后频谱图"
    p23_display.short_description = u"降噪后语谱图"
    p24_display.short_description = u"降噪后响度曲线"
    p3_display.short_description = u"实时心率图"
