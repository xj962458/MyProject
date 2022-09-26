from django.contrib import admin
from app.models import LA


# Register your models here.

@admin.register(LA)
class LaAdmin(admin.ModelAdmin):
    info = ['user', 'time', 'sentence']  # 信息内容
    list_display = info  # 显示的信息
    list_per_page = 10  # 每页信息数
    list_filter = info  # 过滤器
    search_fields = info  # 搜索字段

    admin.site.site_title = "词法分析管理后台"
    admin.site.site_header = "词法分析"
    admin.site.index_title = "词法分析"

    def has_add_permission(self, request):  # 禁止添加
        return False
