import requests
from bs4 import BeautifulSoup
from time import sleep

headers = {
    "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
    "Accept-Encoding": "gzip, deflate, br",
    "Accept-Language": "zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6",
    "Cache-Control": "max-age=0",
    "Connection": "keep-alive",
    "Cookie": 'll="118194"; bid=m7aupClnVrE; viewed="5266583"; gr_user_id=c624a60f-5d51-40f0-b6fd-7fc58c0d58a7; __utma=30149280.620411263.1660617402.1660617402.1660617402.1; __utmz=30149280.1660617402.1.1.utmcsr=baidu|utmccn=(organic)|utmcmd=organic; _vwo_uuid_v2=DDA938D6A12260060094446481F5849C0|4bc73c65f96b1ffae753710d6cbe4d2c; ct=y; ap_v=0,6.0; _pk_ref.100001.4cf6=["","",1665664792,"https://www.baidu.com/s?ie=UTF-8&wd=%E8%B1%86%E7%93%A3"]; _pk_ses.100001.4cf6=*; dbcl2="263610429:aK3sBC3BVOU"; ck=uzry; push_noty_num=0; push_doumail_num=0; _pk_id.100001.4cf6=baff9d322856fa9f.1665627001.2.1665667640.1665628948.',
    "Host": "movie.douban.com",
    "sec-ch-ua": '"Chromium";v="106", "Microsoft Edge";v="106", "Not;A=Brand";v="99"',
    "sec-ch-ua-mobile": "?0",
    "sec-ch-ua-platform": "Windows",
    "Sec-Fetch-Dest": "document",
    "Sec-Fetch-Mode": "navigate",
    "Sec-Fetch-Site": "none",
    "Sec-Fetch-User": "?1",
    "Upgrade-Insecure-Requests": "1",
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/106.0.0.0 Safari/537.36 Edg/106.0.1370.42",
}

scores = ['h', 'm', 'l']
for score in scores:
    with open(f"./data/comments/douban_data/{score}-reviews1.txt", "a+", encoding="utf-8") as f:
        for i in range(0, 20000, 20):
            url = f"https://movie.douban.com/subject/35183042/comments?percent_type={score}&start={i}&limit=20&status=P&sort=new_score"
            r = requests.get(url=url, headers=headers)
            # print(r.status_code)
            if r.status_code == 200:
                soup = BeautifulSoup(r.text, 'lxml')
                comments = soup.find_all(name="span", attrs={"class": "short"})
                for comment in comments:
                    f.write("{}\n".format(
                        comment.text.strip().replace("\n", " ")))

            else:
                print(f"{score}分影评爬取完成!")
                break
            sleep(1)
