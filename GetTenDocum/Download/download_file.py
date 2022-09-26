# -*- coding: utf-8 -*-
import json
import os
from time import sleep

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys

from Cookie.cookie_login import cookie_login
from Download.path import project_path


def download_file(url_list, path, vip=False, back=True):  # 用于下载文件
    options = webdriver.ChromeOptions()  # 用于修改Chrome的设置
    if back:
        options.add_argument('--headless')  # 添加设置1
        options.add_argument('--disable-gpu')  # 添加设置2
    options.add_experimental_option(
        'prefs', {'download.default_directory': path})  # 改变下载保存的路径
    driver = webdriver.Chrome(options=options)  # 以设置好的路径创建webdriver对象
    driver.implicitly_wait(10)  # 设置隐式等待

    driver = cookie_login(driver)  # 使用cookie登录浏览器
    for url in url_list:  # 进行同类模板的下载
        driver.get(url)  # 访问文档链接
        if not vip:  # 如果不是VIP
            driver.find_element(  # 找到“立即使用”按钮并进行点击
                By.XPATH, '//*[@class="template-btn template-btn-blue"]').click()
        else:
            driver.find_element(  # 找到"会员免费用"按钮并进行点击
                By.XPATH, '//*[@class="template-btn template-btn-gold"]').send_keys(Keys.ENTER)
        # 以下几行为模拟下载时的点击操作
        driver.find_element(By.XPATH, "/html/body/div[1]/div/div[1]/div/div[2]/div[2]/div/div/div").click()
        driver.find_element(
            By.CSS_SELECTOR, "li.dui-menu-item.dui-menu-submenu.mainmenu-submenu-export-as").click()
        driver.find_element(
            By.CSS_SELECTOR, "li.dui-menu-item.mainmenu-item-export-as-docx").click()
        sleep(1)
        driver.find_element(
            By.CSS_SELECTOR, "div.export-dialog-button-large-line").click()
        sleep(5)  # 等待下载完成
    driver.quit()  # 关闭浏览器


def make_dirs(path):  # 用于创建文件夹的
    if not os.path.exists(path):  # 若文件夹不存在，则创建
        os.makedirs(path)


def del_file(path):  # 用于清空一个文件夹及其子文件夹下的所有文件
    for i in os.listdir(path):
        c_path = os.path.join(path, i)
        if os.path.isdir(c_path):
            del_file(c_path)
        else:
            os.remove(c_path)


def downfile_from_link(vip_down=False, back=True):  # 从获取的链接中下载文档
    root_path = os.path.join(project_path, "AllFile\\腾讯文档模板")  # 设置下载保存的根路径
    del_file(root_path)  # 下载前，先清空目标文件夹
    with open(os.path.join(project_path, "AllFile/download_link.json"), "r") as f:  # 加载获取到的模板文档链接
        data = json.load(f)  # 加载json文件，并转化为字典对象

    for i in data.keys():  # 遍历所有的模板类
        normal, vip = data[i][0]['normal'], data[i][1]['vip']  # 获取每个模板类的普通模板和VIP模板
        path = os.path.join(root_path, i.replace("/", "&"))  # 有一个模板类中出现'/'，会造成创建文件夹错误
        make_dirs(path)  # 创建用于存储相应模板类的文件夹，以类名为文件夹名
        download_file(list(normal.values()), path, vip_down, back)  # 执行普通模板文档下载
        if vip_down:  # 执行VIP下载，需保证登录账号为VIP
            download_file(list(vip.values()), path, vip_down, back)  # 执行VIP模板文档下载，暂未启用
