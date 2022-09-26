# -*- coding: utf-8 -*-
import json
import os.path
from time import sleep

from selenium import webdriver
from selenium.webdriver.common.by import By

from Download.path import project_path

userinfo = {"username": "2291921855",  # 设置用户名
            "passwd": "f1299211231"  # 设置密码
            }


def get_cookie_auto():  # 自动获取cookie
    options = webdriver.ChromeOptions()  # 设置Chrome设置
    # options.add_argument('--headless')  # 添加设置1
    # options.add_argument('--disable-gpu')  # 添加设置2
    driver = webdriver.Chrome(options=options)  # 创建webdriver对象，并设置后台运行
    driver.implicitly_wait(10)  # 设置隐式等待
    driver.get("https://docs.qq.com/mall/index/doc?from_page=doc_list_tab")  # 访问网址
    # 以下是登录账号操作，为了下载模板
    driver.find_element(
        By.XPATH, '/html/body/div/div/div[1]/div/div/div/div/div[3]/button').click()  # 点击立即登录
    driver.find_element(
        By.XPATH, '/html/body/div[2]/div/div[2]/div/div/div[2]/div[2]/span').click()  # 切换QQ登录
    driver.switch_to.frame("login_frame")  # 切换登陆的frame
    driver.find_element(By.ID, "switcher_plogin").click()  # 切换账号密码登录
    driver.find_element(By.ID, 'u').send_keys(userinfo['username'])  # 输入账号
    driver.find_element(By.ID, 'p').send_keys(userinfo['passwd'])  # 输入密码
    driver.find_element(By.ID, 'login_button').click()  # 点击登录
    sleep(1)  # 等待1秒，等待cookie加载完成
    cookies = driver.get_cookies()  # 获取cookie
    driver.quit()  # 关闭浏览器对象
    with open(os.path.join(project_path, "AllFile/cookies.json"), "w") as f:  # 将获取的Cookie值josn序列化后写入文件
        json.dump(cookies, f)


def get_cookie_manual(t=10):  # 手动获取cookie
    driver = webdriver.Chrome()  # 创建webdriver对象
    driver.implicitly_wait(10)  # 设置隐式等待
    driver.get("https://docs.qq.com/mall/index/doc?from_page=doc_list_tab")  # 访问网址
    sleep(t)  # 根据设定的时间，等待人操作完成，默认10秒
    cookies = driver.get_cookies()  # 获取cookie
    driver.quit()  # 关闭浏览器对象
    with open(os.path.join(project_path, "AllFile/cookies.json"), "w") as f:  # 将获取的Cookie值josn序列化后写入文件
        json.dump(cookies, f)


if __name__ == "__main__":
    get_cookie_auto()  # 设置自动获取cookie
