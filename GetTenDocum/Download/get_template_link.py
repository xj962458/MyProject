# -*- coding: utf-8 -*-
import json
from time import sleep

from selenium import webdriver
from selenium.webdriver.common.by import By

from Download.path import project_path

def get_template_link():
    options = webdriver.ChromeOptions()  # 设置Chrome设置
    options.add_argument('--headless')  # 添加设置1
    options.add_argument('--disable-gpu')  # 添加设置2
    driver = webdriver.Chrome(options=options)  # 构造一个webdriver对象，此处使用的使Edge浏览器
    driver.implicitly_wait(10)  # 设置隐式等待
    # 设置访问的网站，使用get方法
    driver.get("https://docs.qq.com/mall/index/doc?from_page=doc_list_tab")
    sleep(1)  # 强制等待1s，等待页面加载完成
    for i in range(2):  # 多次下拉滚轮，加载所有界面
        driver.execute_script(
            "window.scrollTo(0, document.body.scrollHeight)")  # 执行js脚本来实现下拉操作
        sleep(0.5)  # 缓冲时间

    template_class = {}  # 创建一个空字典，用于存储所有的模板
    templates = driver.find_elements(
        By.XPATH, '//div[@class="template-list is-all"]')  # 查找包含所有的模板的标签
    for template in templates:  # 在所有的模板标签中遍历每个标签
        normal, vip = {}, {}  # 设置两个空字典，用于存储每一类模板中的普通模板和vip模板
        header = template.find_element(
            By.XPATH, './div[1]/div/div[1]').text  # 获取模板类类名
        content = template.find_elements(
            By.XPATH, './div[2]/div[@class="template-card v "]')  # 查找每一类模板所包含的所有模板的标签
        for document in content:  # 在本类模板标签中遍历所有模板标签
            t = document.find_element(
                By.XPATH, "./div[2]/div[1]/a")  # 找到包含模板文档名称和链接的标签
            text, href = t.text, t.get_attribute("href")  # 获取模板文档名称和链接
            if document.get_attribute('data-free-for-vip') == 'false':  # 如果不是VIP模板
                normal[text] = href  # 将模板信息插入到普通模板中
            else:  # 如果使VIP模板
                vip[text] = href  # 将VIP模板信息插入到VIP模板中
        template_class[header] = [{"normal": normal},
                                  {"vip": vip}]  # 将每一类模板信息插入到总模板中
    with open(project_path + "/AllFile/download_link.json", "w") as f:  # 创建一个文件，以待写入
        json.dump(template_class, f, ensure_ascii=False)  # 将所有模板信息写入json文件
    driver.quit()  # 结束操作，关闭浏览器


if __name__ == "__main__":
    get_template_link()
