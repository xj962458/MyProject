import requests
from datetime import datetime, timedelta
from time import sleep

movie_id = "1359034"  # 电影ID，可去豆瓣网站点击电影获取
# start_time = datetime.strptime(str(datetime.now()).split(".")[0], "%Y-%m-%d %H:%M:%S")  # 当前时间
start_time = datetime.strptime(
    "2022-07-30 00:46:49", "%Y-%m-%d %H:%M:%S")  # 爬虫遇到验证后更改时间继续爬取
release_time = datetime.strptime(
    "2022-07-29 00:00:00", "%Y-%m-%d %H:%M:%S")  # 电影上映时间

url = f"http://m.maoyan.com/mmdb/comments/movie/{movie_id}.json?v=yes&offset=15&startTime="


headers = {
    "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
    "Accept-Encoding": "gzip, deflate, br",
    "Accept-Language": "zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6",
    "Cache-Control": "max-age=0",
    "Connection": "keep-alive",
    "Host": "m.maoyan.com",
    "Sec-Fetch-Dest": "document",
    "Sec-Fetch-Mode": "navigate",
    "Sec-Fetch-Site": "none",
    "Sec-Fetch-User": "?1",
    "Upgrade-Insecure-Requests": "1",
    "User-Agent": "Mozilla/5.0 (iPhone; CPU iPhone OS 13_1_3 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/13.0.3 Mobile/15E148 Safari/604.1 Edg/106.0.0.0"
}

while start_time > release_time:
    url = f"http://m.maoyan.com/mmdb/comments/movie/{movie_id}.json?v=yes&offset=15&startTime={start_time}"
    r = requests.get(url=url, headers=headers)
    if r.status_code == 200:
        # print(r.json())
        try:
            info = r.json()
            with open("./comments.txt", "a+", encoding="utf-8") as f:
                for i in info['cmts']:
                    f.write("{}####{}####{}####{}####{}\n".format(i['score'], i['content'].strip(
                    ).replace('\n', ' '), i['cityName'], i['nickName'], i['startTime']))
            start_time = datetime.strptime(
                r.json()['cmts'][-1]['startTime'], "%Y-%m-%d %H:%M:%S") + timedelta(seconds=-1)
        except:
            print("现在爬虫需要美团验证，请点击跳转到美团验证界面再重新启用该爬虫。")
            print(
                f"跳转美团验证的链接为http://m.maoyan.com/mmdb/comments/movie/{movie_id}.json")
            print("验证完成后，注释代码的第6行，取消注释第7行，并将第7行中的时间改为运行最后输出的时间，可继续爬取!")
            break

    sleep(1)
    print(start_time)
