from time import sleep
import requests
import json
import threading
import time

movie_id = "269454"  # 要获取的影评ID,可前往时光网官网查看

k = 500  # 设置一下返回多少条数据,即每页多少条数据
page_thread = 2  # 每个线程中处理几页
# 模拟请求标头
header = {
    "Accept": "application/json, text/plain, */*",
    "Accept-Encoding": "gzip, deflate",
    "Accept-Language": "zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6",
    "Content-Type": "application/json",
    "Cookie": "sajssdk_2015_cross_new_user=1; sensorsdata2015jssdkcross=%7B%22distinct_id%22%3A%22183cf3e506854-00547d93b34e2b68-7b555473-1338645-183cf3e5069819%22%2C%22first_id%22%3A%22%22%2C%22props%22%3A%7B%22%24latest_traffic_source_type%22%3A%22%E7%9B%B4%E6%8E%A5%E6%B5%81%E9%87%8F%22%2C%22%24latest_search_keyword%22%3A%22%E6%9C%AA%E5%8F%96%E5%88%B0%E5%80%BC_%E7%9B%B4%E6%8E%A5%E6%89%93%E5%BC%80%22%2C%22%24latest_referrer%22%3A%22%22%7D%2C%22identities%22%3A%22eyIkaWRlbnRpdHlfY29va2llX2lkIjoiMTgzY2YzZTUwNjg1NC0wMDU0N2Q5M2IzNGUyYjY4LTdiNTU1NDczLTEzMzg2NDUtMTgzY2YzZTUwNjk4MTkifQ%3D%3D%22%2C%22history_login_id%22%3A%7B%22name%22%3A%22%22%2C%22value%22%3A%22%22%7D%2C%22%24device_id%22%3A%22183cf3e506854-00547d93b34e2b68-7b555473-1338645-183cf3e5069819%22%7D; Hm_lvt_07aa95427da600fc217b1133c1e84e5b=1665629312,1665630632,1665641201; searchHistoryCookie=%u72EC%u884C%u6708%u7403%2C%u4F60%u597D%uFF0C%u65E7%u65F6%u5149%2C%u6218%u72FC; Hm_lpvt_07aa95427da600fc217b1133c1e84e5b=1665653200",
    "Host": "front-gateway.mtime.com",
    "Origin": "http://movie.mtime.com",
    "Proxy-Connection": "keep-alive",
    "Referer": "http://movie.mtime.com/",
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/106.0.0.0 Safari/537.36 Edg/106.0.1370.42",
    "X-Mtime-Wap-CheckValue": "mtime",
}


def get_total_page():  # 获取目标影片有多少页影评
    t1 = int(time.time())  # 获取当前时间
    url = f"http://front-gateway.mtime.com/library/movie/comment.api?tt={t1}&movieId={movie_id}&pageIndex=1&pageSize={k}&orderType=1"
    r = requests.get(url, headers=header)  # 请求数据
    s = json.loads(r.text)  # 将请求道的json字符串转化为字典
    total = int(s['data']['count'])  # 计算总共有多少条数据
    return total // k + 1 if total % k else 0  # 每页有k条数据，判断一共有多少页


def get_data(start, end):
    for page in range(start, end + 1):
        t = int(time.time())
        url = f"http://front-gateway.mtime.com/library/movie/comment.api?tt={t}&movieId={movie_id}&pageIndex={page}&pageSize={k}&orderType=1"
        r = requests.get(url, headers=header)
        if r.status_code:  # 判断是否请求成功
            s = json.loads(r.text)  # 将请求获得的json数据转化为字典类型
            with open("./data/mtime_data/reviews.txt", "a+", encoding="utf-8", errors="ignore") as f:  # 将评论保存至文件，采用追加的方式
                for i in s['data']['list']:  # 获取的是一个页面的评论，需要遍历每一个将其写入到文件中
                    # ,i['rating']))  # 写入到文件中
                    f.write("{}\n".format(
                        i['content'].strip().replace("\n", " ")))
        else:
            return -1  # 表示请求错误

        # sleep(0.5)  # 暂定0.5s，防止频繁请求被拉黑


def start_get(page_size):  # 开始获取数据，并判断是否使用多线程
    use_multithread = True if page_size > page_thread else False  # 页面数量大于设置值时使用，否则使用
    if use_multithread:  # 使用多线程操作，每20个页面送进一个线程
        threads = []  # 用于存放线程
        i = 1
        while page_size - i > k:
            threads.append(threading.Thread(
                target=get_data, args=(i, i + k - 1)))  # 添加线程
            i = i + k
        threads.append(threading.Thread(target=get_data, args=(i, page_size)))
        for thread in threads:  # 开始线程
            thread.start()

        for thread in threads:  # 等待线程结束
            thread.join()

    else:  # 不使用多线程，直接获取数据
        get_data(1, page_size + 1)


if __name__ == "__main__":
    total_page = get_total_page()  # 获取影评页面个数
    start_get(total_page)  # 开始爬取
