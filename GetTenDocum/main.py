# -*- coding: utf-8 -*-
import os

from Cookie.get_cookie import get_cookie_auto
from Download.download_file import downfile_from_link
from Download.get_template_link import get_template_link
from Download.path import project_path

if __name__ == "__main__":
    background = True  # 程序默认后台执行，如需前台执行，请将此致修改为False
    vip_down = False  # 下载VIP文档，需保证账号是VIP，否则可能会失败，默认为False，若账号为VIP，请修改问True
    if not os.path.exists(os.path.join(project_path, "AllFile/download_link.json")):  # 若没有文档的链接，则去调用函数获取
        get_template_link()
    if not os.path.exists(os.path.join(project_path, "AllFile/cookies.json")):  # 若没有cookie文件，调用相关函数获取
        get_cookie_auto()
    downfile_from_link(vip_down, background)  # 开始执行下载任务
