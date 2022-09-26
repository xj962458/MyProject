# -*- coding: utf-8 -*-
import json
import os.path

from selenium import webdriver

from Download.path import project_path


def cookie_login(driver):  # 根据cookie自动登录
    with open(os.path.join(project_path, "AllFile/cookies.json"), "r", encoding="utf8") as f:  # 打卡文件，获取cookie
        cookies = json.load(f)
    driver.get("https://docs.qq.com/mall/index/doc?from_page=doc_list_tab")  # 设置访问的网站，使用get方法
    driver.delete_all_cookies()  # 删除所有已存在的cookie
    for cookie in cookies:  # 将cookie添加到浏览器中
        driver.add_cookie(
            {
                'domain': cookie['domain'],
                'name': cookie['name'],
                'value': cookie['value'],
                'path': cookie['path']
            }
        )
    driver.refresh()  # 刷新页面
    return driver  # 将浏览器对象返回


if __name__ == "__main__":
    driver = webdriver.Chrome()
    cookie_login(driver)
