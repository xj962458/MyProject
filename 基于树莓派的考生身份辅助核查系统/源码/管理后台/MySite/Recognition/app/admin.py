from django.contrib import admin
from app.models import data, data1
from django.contrib.auth.models import Group, User
# Register your models here.


@admin.register(data)
@admin.register(data1)
class AppAdmin(admin.ModelAdmin):
    list_display = ['id', 'location', 'update_time', 'image_face',
                    'iamge_certificate', 'similarity', ]
    readonly_fields = ('image_face', 'iamge_certificate')  # 只读字段

    list_per_page = 5
    # 筛选器
    list_filter = ('update_time', 'similarity', 'location')  # 过滤器
    search_fields = ('id', 'update_time', 'similarity', 'location')  # 搜索字段

    admin.site.site_header = "基于树莓派的考生身份辅助核查系统"
    admin.site.site_title = "基于树莓派的考生身份辅助核查系统"

    def has_add_permission(self, request):
        return False

    def has_change_permission(self, request):
        return False
    # def has_delete_permission(self, request, obj=None):
    #     # 编辑页面禁用删除按钮
    #     return False

    admin.site.unregister(Group)  # 关闭对组的修改
    admin.site.unregister(User)  # 关闭对用户的修改
