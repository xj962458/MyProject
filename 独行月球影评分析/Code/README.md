## 一、问题描述

**课题：基于深度学习的情感分析模型实现对电影独行月球影评的分析**

​		 影评分析本质上是一个分类问题，是获取用户对电影的评论后，对数据进行处理，然后使用机器学习或深度学习的方法对用户的评论进行分类，一般可以分为好评、中评和差评。此处为简化问题，我们将电影分为好评和差评，即将问题转化成一个二分类问题。

​	    本课题影评分析的对象为《独行月球》影评，该电影于2022年7月29日上映，在豆瓣、猫眼和时光网等网站上已经有了大量的评论，需要使用爬虫等工具去获取这些评论，将这些数据获取之后需要进行数据整理、数据标注和数据清洗等一系列数据预处理操作。

​		在获取数据后，需要构建适当的机器学习或深度学习模型，将预处理好的数据放到模型中训练，训练完成后，我们将模型保存，以供其他程序调用。在训练模型的过程中，需要保证一定的准确率。



## 二、解决方案

* 数据采集：使用`requests`和`BeautifulSoup`库来编写爬虫程序，分别爬取豆瓣、猫眼和时光网等影评网站关于电影《独行月球》的评论，将爬取的评论内容和评分等数据保存到文件中，以便之后处理；
* 数据处理：在获得数据后，我们需要先对数据进行基本的处理，如去重、去空和标签转化等，除此之外，还需要划分数据集，将数据集划分为训练集、验证集和测试集。除此之外，在数据送入到模型之前，还需要获取词表、分词、将数据转化为id序列等操作。
* 模型构建：能够做影评分类的模型有很多，为保证准确率，我选用了百度的ERNIE 3.0预训练模型，并使用了百度飞桨的`paddlepaddle`模型进行模型的构建、训练和测试。
* 模型调用：训练好模型后，将其保存到文件中，然后创建程序去加载模型，以实现影评分析的任务。为了更好的人机交互，我使用了Qt创建了图形界面，方便了模型的调用。



## 三、开发环境

### 1、硬件环境

**训练模型的环境：**

* **CPU：**Intel(R) Xeon(R) Gold 6248 CPU（20） @ 2.50GHz

* **内存：**96GB

* **显卡：**Tesla A100 40GB

* **硬盘：**100GB SSD

**数据采集、处理和调用模型的环境**

* **CPU：**AMD 4800U
* **内存：**16GB
* **显卡：**Vega8核显
* **硬盘：**500GB SSD



### 2、软件环境

* **操作系统：**Windows11 64位专业版、Ubuntu18.04

* **开发工具：**VSCode、QtCreater、jupyterlab
* **网络爬虫工具：**requests、BeautifulSoup4
* **深度学习框架：**PaddlePaddle、paddlenlp
* **GUI界面框架：**Qt、PySide6
* **写作工具：**Typora、Word
* **其他第三方库：**numpy、pandas、matplotlib和wordcloud等，详见`requirements.txt`文件



## 四、项目结构

```bash
+---.vscode
+---data                         # 存储数据
|   +---databases			     # 数据库数据
|   +---datasets				 # 数据集
|   |   +---douban_data				# 从豆瓣采集的数据集
|   |   +---final_data				# 处理好的，用于训练的数据集
|   |   +---maoyan_data				# 从猫眼采集的数据集
|   |   \---mtime_data				# 从时光网采集的数据集
|   +---others						# 其他数据，包含词表、停用词表和字体文件等
|   +---pictures					# 包含项目中所用到的图片
|   \---ui							# Qt Designer设计的ui文件
+---GUI							 # 存储转化后的UI文件，转化后为python文件，供主程序调用
+---Model						 # 保存训练好的模型、模型参数和词表等，供主程序加载
+---数据处理					  # 数据处理相关的文件
|   \---数据采集					  # 爬虫程序，包含三个网站的爬虫程序
\---模型处理					  # 模型训练时的文件，模型在百度AI Studio上训练，训练好的下载出来的
    +---data						# 训练和测试模型时用到的数据
    |   \---data172897				# 数据
    \---results						保存测试结果
```



## 五、数据采集

​         本项目需要用到的数据都在各大影评网站上，需要使用爬虫进行爬取。Python语言是常见的爬虫开发语言之一，有着非常丰富的爬虫第三方库，如requests、BeautifulSoup4、SeIenium和urllib3等，我在之前的项目中或多或少都用过，比较熟悉，考虑到数据量不是很大，所以就使用了最简单的requests和BeautifulSoup4来编写爬虫程序。

数据共取自三个网站：豆瓣、猫眼和时光网。

* 豆瓣上的数据最多，有20多万条，但豆瓣限制每类评论只能够查看600条左右，高、中和低影评均爬取了600多条，共1800余条，准备使用该数据集作为UI界面中可供用户选择的数据；

* 猫眼数据次之，数据有14多万条，获取耗时最长，获取的数据最多，共6万余条，猫眼数据获取最多，所以使用猫眼数据去训练和测试模型；

* 时光网界面使用Vue创建，找到前端向后端请求的数据接口即可获取所有数据，但时光网得影评数量太少，只有600余条，所以并不使用该数据。



### 1、豆瓣爬虫

**豆瓣独行月球：**[https://movie.douban.com/subject/35183042/](https://movie.douban.com/subject/35183042/)

<img src="http://doc.xjfyt.top/markdown_img/20221014204849.png" alt="image-20221014204848566" style="zoom: 25%;" />

#### （1）网站分析

​        豆瓣上关于独行月球的评论是最多的，但是豆瓣有限制，最多只能够查看一千余条数据。如上图所示，豆瓣的评论包含全部、好评、一般和差评，为防止数据重复，我们只爬取好评、一般和差评三中类别，并分别保存到对应的文件中。

三种评论的请求链接如下：

```bash
好评：https://movie.douban.com/subject/35183042/comments?percent_type=h&start=0&limit=20&status=P&sort=new_score

一般：https://movie.douban.com/subject/35183042/comments?percent_type=m&start=0&limit=20&status=P&sort=new_score

差评：https://movie.douban.com/subject/35183042/comments?percent_type=l&start=0&limit=20&status=P&sort=new_score
```

通过访问并分析以上URL，我们可以看出:

* 三种链接的不同之处在于`percent_type`字段，高、中、低三种评价分别对应h、m和l，编写程序时，只要让其在这三者间遍历即可爬取所有数据。
* `start`字段为每页开始的影评序号，此处为0，代表是第一页，第二页为2*页面影评数，以此类推；
* `limit`字段为每页影评数目，默认是20，使用默认即可；
* 其他字段不用关心，当切换页面时不会该变；
* 实测，若不登陆账号，每种类别只能够爬取200多条数据，登陆后每种类别能够爬取600多条数据；

#### （2）爬虫思路

* 使用`requests`取请求URL，然后判断状态码为200时，使用`BeautifulSoup4`进行解析，并查找相应的标签，获取其中的数据；
* 在网站登陆后获取`COOKIE`，添加到请求头中；
* 设置等待时间，防止频繁请求被封；
* 爬取三种类别的数据，分别存储在不同的文件中；

#### （3）验证问题

爬虫爬取次数过多时，将需要验证，所以若爬取失败请检查是否需要人工验证，验证方式为手动使用浏览器访问爬取的地址，看有无一下内容，若有，则验证后再进行爬取。

<img src="http://doc.xjfyt.top/markdown_img/20221018184600.png" alt="image-20221018184559749" style="zoom:33%;" />

#### （4）爬虫程序

我们使用`requests`来爬取数据，使用`BeautifulSoup4`来解析数据，爬取的代码如下（COOKIE已打乱）:

```python
import requests
from bs4 import BeautifulSoup
from time import sleep

headers = {
    "Accept": "text/html,ion/signed-exchange;v=b3;q=0.9",
    "Cookie": 'll="1894"; bid=m7aunVrE; v7402.1660617402.1;utaffaf1.165627001.2.1665667640.1665628948.',
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
```

### 2、猫眼爬虫

**猫眼独行月球：**[https://www.maoyan.com/films/1359034](https://www.maoyan.com/films/1359034)

<img src="http://doc.xjfyt.top/markdown_img/20221019152700.png" alt="image-20221014204804415" style="zoom: 25%;" />

#### （1）网站分析

经过分析，在PC端浏览器中，只能够看到几条影评，经查找资料，得知爬取猫眼的数据需要以移动端的UA进行请求，且有一个数据请求地址，我们使用`requests`对该地址进行多次请求，即可获取数据。请求的地址如下：

```bash
http://m.maoyan.com/mmdb/comments/movie/{movie_id}.json?v=yes&offset=15&startTime={start_time}
```

* `movie_id`为电影在猫眼网站上对应的ID，访问猫眼中对应电影，即可在地址栏中进行获取，本电影的ID为`1359034`;
* `offset`为每页影评数量，经实测，无论该值改成多少，只会返回15条数据，所以此处使用默认值；
* `start_time`，此字段为爬取的时间，此字段尤其关键，不同的时间取请求数据，将会得到不同的数据；
* 该接口在PC端进行请求时，需要更改浏览器UA为移动端，否则可能无法爬取，更改方法自行搜素；
* 无论是否登录，都可以一直爬取，且都会遇见人工验证，所以选择不登陆；



我们在浏览器中发起一个请求，得到的结果如下：

<img src="http://doc.xjfyt.top/markdown_img/20221018192346.png" alt="image-20221018192345213" style="zoom: 33%;" />

如上图所示，我们得到的是一个json数据，一个json数据中包含15条数据，将数据中有用的字段例举如下：

* `content`：影评的内容；
* `score`：影评评分；
* `startTime`：评论的发表时间，此字段非常有用，请求的15条数据中该字段是降序排列的，通过该数据，我们可以知道我们爬取到了哪一天的评论，对程序的暂停和恢复有很大帮助，当需要验证之后，也可以根据该数据获取程序最后爬取的时间，从而接着爬取；
* `cityName`：评论发表的城市；
* `nickName`：评论者昵称；

#### （2）爬虫思路

由以上分析可知：

* 确定电影的ID之后，将浏览器UA改为移动端，即可进行爬取；
* 爬取的时候我们以当前时间为出发点，依次减少时间，当时间到达电影发布日期，便可以截止爬取；
* 编写异常处理程序，即当爬虫遇见验证时，提醒用户手动验证；
* 设置等待时间，防止频繁请求被封IP。

#### （3）验证问题

​	   爬虫爬取的时候每过一段时间就会需要验证，在不加`COOKIE`的情况下，手动验证后即可接着爬取，在加`COOKIE`的情况下，手动验证也可能失败，所以建议爬取时不要添加`COOKIE`。
​	   在验证时，可能会出现不会自动跳转到验证界面的情况，这是因为本地有缓存，这时请打开InPrivate窗口进行访问验证。

<img src="http://doc.xjfyt.top/markdown_img/20221014205143.png" alt="image-20221014205142858" style="zoom: 43%;" />

#### （4）爬虫程序

```python
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
    "User-Agent": "Mozilla/5.0 (iPhone; CPU iPhone OS 13_1_3 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/13.0.3 Mobile/15E148 Safari/604.1 Edg/106.0.0.0"
}

while start_time > release_time:
    url = f"http://m.maoyan.com/mmdb/comments/movie/{movie_id}.json?v=yes&offset=15&startTime={start_time}"
    r = requests.get(url=url, headers=headers)
    if r.status_code == 200:
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
```

### 3、时光网爬虫

**时光网独行月球：**[http://movie.mtime.com/269454/](http://movie.mtime.com/269454/)

<img src="http://doc.xjfyt.top/markdown_img/20221014205104.png" alt="image-20221014205055489" style="zoom: 33%;" />

​        时光网的界面使用VUE编写，是前后端分离的设计模式，所以只要找到前端向后端请求的接口，就可以通过请求接口的形式获取数据，实测，该网站的后台接口没有访问次数限制，且可以通过修改参数，一下拿到所有数据。因该网站影评数目较少，本项目中没有用到，所以不多介绍爬取方法。



## 六、数据处理

### 1、基本数据处理

```python
# 对爬取的数据进行基本的处理，如去重、去空、值转换等
comment_type = {5.0: 1, 4.5: 1, 4.0: 1, 3.5: 1, 3.0: 0,
                2.5: 0, 2.0: 0, 1.5: 0, 1.0: 0, 0.5: 0, 0.0: 0}

comments = pd.read_csv("../data/comments/maoyan_data/comments.txt",
                       sep="####", engine='python')  # 读取数据，以####作为分割，使用python作为读取引擎

origin_size=len(comments)
# 进行去重操作，根据评论一列的数据进行去重，在原数据上进行修改
comments.drop_duplicates('评论', keep='first', inplace=True)
comments.dropna(inplace=True)  # 去除可能的空值
comments['评分'] = comments['评分'].apply(
    lambda x: comment_type[x])  # 将评分体系归类为好评、中评和差评体系
print(f"去重前数据:{origin_size},去重后数据:{len(comments)}")

#去重前数据:62100,去重后数据:55244
```

​		爬取数据时，我设置爬取的评论每列之间以`####`来分割，所以读取数据时也需要指定分隔符，使用`pandas`可以很简单的对数据进行处理。这里主要做的处理有，根据评论内容去重，将可能的空值去除、将评分转化为好评和差评。

### 2、统计词频并构建词表

```python
# 对评论内容进行进一步处理，统计词频，以及获取生成词云的字符串
import re
import jieba
# 停用词设置，此处采用的是哈工大的停用词表
stop_words=[i.strip() for i in open("../data/others/hit_stopwords.txt","r",encoding="utf-8").readlines()] # 加载停用词
text_s="" # 用于保存生成词云的字符串
result=[] # 用于存储所有数据
vacab={} # 用于统计词频
jieba.load_userdict("../data/others/user.txt")

for text,label in zip(X,y): # 此处的X即为上一步获取的所有评论
    tmp=""
    cut_list=jieba.lcut("".join(re.findall("[\u4e00-\u9fa5a-zA-Z0-9]",text))) # 只取汉字、英文字母和数字，\u4e00-\u9fa5为unicode表中所有汉字，获取后用jieba进行全模式分词
    for word in cut_list: # 遍历分出的词，统计词频
        if word not in stop_words:
            vacab[word]=vacab.get(word,0)+1
            tmp+=" "+word
            text_s+=" "+word
    result.append({'label':label,"text":tmp})

data=pd.DataFrame(data=result) # 由数据构建一个DataFrame，为了更好的写入文件
data.to_csv("../data/datasets/final_data/all_data.txt",sep="\t",index=False)# 将句子分词后写入文件中

# 根据统计的词频创建词表
vacab=list(vacab.items())
vacab=sorted(vacab,key=lambda x:x[1],reverse=True) # 按照词频对词进行排序，词频大的在前
with open("../data/datasets/others/vocab.txt","w+",encoding="utf-8") as f:
    for word,_ in vacab:
        f.write(word+"\n")
```

* 该步骤包含了数据清洗，为正则表达式匹配和去停用词；

* 使用jieba进行分词，并加载自定义词表，自定义词表主要是一些人名，设置自定义词表是为了让jieba将其认为是一个词；

* 使用re库进行正则匹配，评论中包含了很多标点和表情包，数量巨大，且在分析数据情感时作用有限，故将其去掉，此处使用正则表达式进行匹配，只读取汉字、英文字母和数字，读取后进行分词；

* 设置停用词表，此处使用了哈工大的停用词表，停用词没有什么实际含义，对语义影响不深，故将其去除；

* 设置一个字典，用于存储词表，创建词表的目的是实现word2id，即完成词语到id的映射，统计完成后，将词表根据词频进行排序，词频越大的其id越小，这样是为了更好的加快访问，建立好词表后将其写入到文件中；

* 将原本的数据进行数据清洗后分词，然后将分词的结果以空格为分割，并写入文件中。


### 3、划分数据集

```python
# 划分数据集，将数据集划分为训练集、开发集和测试集，比例为8:1:1
# 获取构建、训练和测试模型所需的X,Y
y = data['label']
X = data['text']

# 数据集划分
X_train, X_temp, y_train, y_temp = train_test_split(
    X, y, test_size=0.2, shuffle=True)
X_test, X_dev, y_test, y_dev = train_test_split(
    X_temp, y_temp, test_size=0.5, shuffle=True)

# 将划分好的数据集保存至文件
pd.concat([y_train, X_train], axis=1).to_csv(
    "./train.txt", index=False, sep="\t")  # 将训练集保存到文件
pd.concat([y_dev, X_dev], axis=1).to_csv(
    "./dev.txt", index=False, sep="\t")  # 将开发集保存到文件
pd.concat([y_test, X_test], axis=1).to_csv(
    "./test.txt", index=False, sep="\t")  # 将测试机保存到文件
```

* 此处划分数据集利用了`sklearn`库中的`train_test_split`函数；
* 划分的数据集由训练集、验证集（开发集）和测试集，比例为8:1:1;
* 划分好的数据集分别保存到对应的文件中，方面训练模型时使用；

### 4、绘制词云图

```python
from wordcloud import WordCloud
import matplotlib.pyplot as plt
wc = WordCloud(
    background_color="white",  # 背景颜色
    font_path='msyh.ttc',  # 调用font里的simsun.tff字体，需要提前安装
    scale=32,                     # 清晰度
    random_state=1000,  # 设置随机生成状态，即有多少种配色方案
)
myword = wc.generate(text_s)  # 用 wl的词语 生成词云
# 展示词云图
plt.imshow(myword)
plt.axis("off")
plt.show()
```

上面我们已经进行了词频统计，词频能够描述某一出现的频率，但不够直观，此处，我们使用`wordcloud`来绘制词云图，来更为直观的查看评论中出现次数最多的词，运行结果如下：

<img src="http://doc.xjfyt.top/markdown_img/20221019211916.png" alt="Figure_1" style="zoom:67%;" />

### 5、图形界面数据处理

* 在图形界面中，我设置了一个可以选择评论的控件，这些控件中的数据便来源于从豆瓣爬取的数据；
* 豆瓣中爬取的数据较少，只有1800多条，不适合用来训练模型，所以将其作为图形界面中供用户选择的数据；
* 豆瓣爬虫编写时，是分类爬取，分别存储到不同的文件中，我们将各个文件读取，然后将文件打乱，汇总到一个文件中；
* 最终处理后的数据命名为`reviews.txt`，利用Navicate、DataGrip等数据库工具将其导入入到sqlite数据库文件中，也可以自己编写SQL语句导入，导入到数据库是为了图形界面更好的加载数据和提升数据加载速度；



## 七、模型构建、训练与测试

​       解决影评分类问题我选用了百度的ERNIE 3.0模型，该模型是一个预训练模型，能够解决文本分类、实体识别、机器翻译等多种NLP问题，此处选用该模型是因为该模型训练效果非常好，而且在百度AI Studio平台使用该模型有免费的计算资源。使用该模型，不可避免的要使用到`paddlepaddle`框架，该框架在我以前的项目中有接触到，还是比较熟悉的。

​		使用预训练模型解决问题和自己搭建模型解决问题差不多，都需要数据集、封装DataSet和DataLoader、定义评价标准、衡量指标和损失函数等，不同的是使用预训练模型不用自己去定义网络结构，且准确率较高。

### 1、模型介绍

​		ERNIE 3.0首次在百亿级预训练模型中引入大规模知识图谱，提出了海量无监督文本与大规模知识图谱的平行预训练方法(Universal Knowledge-Text Prediction)，通过将知识图谱挖掘算法得到五千万知识图谱三元组与4TB大规模语料同时输入到预训练模型中进行联合掩码训练，促进了结构化知识和无结构文本之间的信息共享，大幅提升了模型对于知识的记忆和推理能力。

​		ERNIE 3.0框架分为两层。第一层是通用语义表示网络，该网络学习数据中的基础和通用的知识。第二层是任务语义表示网络，该网络基于通用语义表示，学习任务相关的知识。在学习过程中，任务语义表示网络只学习对应类别的预训练任务，而通用语义表示网络会学习所有的预训练任务。

<img src="http://doc.xjfyt.top/markdown_img/20221019161246.png" alt="img" style="zoom: 50%;" />

### 2、模型加载

我们使用的paddlepaddle框架已经内置了该模型，使用简单的函数，即可完成模型的加载：

```python
from paddlenlp.transformers import AutoModelForSequenceClassification, AutoTokenizer

model_name = "ernie-3.0-medium-zh" # 模型名称
# 加载模型
model = AutoModelForSequenceClassification.from_pretrained(model_name, num_classes=len(train_ds.label_list))
tokenizer = AutoTokenizer.from_pretrained(model_name) # 加载分词器
```

* 程序会根据模型名称，自动取下载模型文件，并使用内置的函数进行加载。

* 除了加载模型之外，还需要加载一个分词器，该分词器的主要作用是将输入的文本分词并转化为id序列。如下图所示，将输入的文本转化为一个id序列。输出的结果是一个字典，`input_ids`是转化为后结果。有了该分词器，我们就不需要自己去实现分词并转化为id序列了，`token_type_ids`是标签id，即label2id，该项默认为0，我们数据集已标注，不需要使用此项。
  ![image-20221019162520847](http://doc.xjfyt.top/markdown_img/20221019162521.png)

### 3、封装数据集

​		深度学习在训练模型前都需要对数据进行封装，常见的封装方法是先将数据集封装成一个dataset类型，然后再将dataset封装成dataloader类型，封装成dataloader类型时需要指定batch_size，有时还需要对数据进行padding等操作。不同的深度学习框架可能有差异，但大抵类似，对于百度paddlepaddle框架来说，也是一样，需要封装成dataset类型，然后再进一步封装为dataloader类型，不过paddlepaddle框架对数据的封装更加方便，使用其内置的类或函数可以非常简单的实现。

 **读取数据并封装为dataset类型，paddle框架中对应的为MapDataSet类型：**

```python
from paddlenlp.datasets import load_dataset
def read(data_path): # 读取数据
    i = 1
    with open(data_path, 'r', encoding='utf-8') as f: # 读取文件
        next(f)  # 跳过列名
        for line in f:
            label,text = line.strip().split('\t') # 以\t分割数据
            yield {'text': text, 'label': int(label)} # 协程返回数据
train_ds = load_dataset(read, data_path='./data/data172897/train.txt', lazy=False) # 读取训练集数据
dev_ds = load_dataset(read, data_path='./data/data172897/dev.txt', lazy=False)  # 读取验证集数据
test_ds = load_dataset(read, data_path='./data/data172897/test.txt', lazy=False) # 读取测试集数据
```

**将数据进一步封装为dataloader类型，paddle中对应的为DataLoader类型**

```python
import functools
import numpy as np
from paddle.io import DataLoader, BatchSampler
from paddlenlp.data import DataCollatorWithPadding

# 数据预处理函数，利用分词器将文本转化为整数序列
def preprocess_function(examples, tokenizer, max_seq_length, is_test=False):
    result = tokenizer(text=examples["text"], max_seq_len=max_seq_length)
    if not is_test:
        result["labels"] = examples["label"]
    return result

trans_func = functools.partial(preprocess_function, tokenizer=tokenizer, max_seq_length=256)
train_ds = train_ds.map(trans_func)
dev_ds = dev_ds.map(trans_func)

# collate_fn函数构造，将不同长度序列充到批中数据的最大长度，再将数据堆叠
collate_fn = DataCollatorWithPadding(tokenizer)

# 定义BatchSampler，选择批大小和是否随机乱序，进行DataLoader
train_batch_sampler = BatchSampler(train_ds, batch_size=128, shuffle=True)
dev_batch_sampler = BatchSampler(dev_ds, batch_size=128, shuffle=False)
train_data_loader = DataLoader(dataset=train_ds, batch_sampler=train_batch_sampler, collate_fn=collate_fn)
dev_data_loader = DataLoader(dataset=dev_ds, batch_sampler=dev_batch_sampler, collate_fn=collate_fn)
```

​      封装成dataloader类型后就需要将数据送入模型中训练，模型无法处理文本数据，所以需要先利用分词器将文本转化为id序列，在模型中会将id序列进一步转化为词向量。

### 4、定义训练参数

```python
optimizer = paddle.optimizer.AdamW(learning_rate=2e-5, parameters=model.parameters())# Adam优化器
criterion = paddle.nn.loss.CrossEntropyLoss() # 交叉熵损失函数
metric = paddle.metric.Accuracy() # accuracy评价指标
```

​        以上三行代码分别定义了优化器、损失函数和评价指标，使用了常用的Adam优化器，二分类问题常用的交叉熵损失函数，以及使用准确率作为评价指标。

### 5、模型训练

* 模型的训练需要很大的计算性能，即需要高性能的GPU，我的电脑显然不能够满足训练要求，为了更快的训练模型，我使用了百度AI Studio上免费的训练资源完成了模型训练。

* 我选择的配置是拥有40GB显存、6912个CUDA核心的Tesla V100显卡进行运算，大幅提升了计算速度，使用ERNIE 3.0预训练模型，设置batch_size为128，epoch为5和max_seq_length=256的参数下，对五万余条影评数据进行训练，共花费324.643秒训练完成。

* 在训练过程中，每迭代10次，将会打印一次损失函数值、准确率、计算速度；每迭代100次，将会评估当前训练的模型、保存当前模型参数和分词器的词表等。训练过程中的部分数据如下：
<img src="http://doc.xjfyt.top/markdown_img/20221019174329.png" alt="image-20221019174328978" style="zoom:50%;" />

### 6、模型测试

在模型训练并保存完成后，使用模型对测试集进行预测，预测的结果如下：

<img src="http://doc.xjfyt.top/markdown_img/20221019174450.png" alt="image-20221019174449129" style="zoom: 43%;" />

* 从训练集、验证集和测试集的结果来看，准确率均能达到94%以上，符合预期。
* 当训练测试结束后，将保存的模型下载到本地，并设计GUI界面完成模型的调用。



## 八、GUI界面设计

### 1、界面介绍

为了更为直观的使用模型，我设计了一个GUI界面，用于用户和模型的交互，GUI界面使用Qt框架设计，界面如下：

<img src="http://doc.xjfyt.top/markdown_img/20221019153529.png" alt="image-20221019103006091" style="zoom: 43%;" />

如图所示，界面主要分为四个区域：

* 最上方的是影评输入区，用户可以在这里输入要分析的影评，也会显示选择的影评；
* 中间是文本分析按钮，当输入要分析的影评后，点击开始分析，就会调用模型进行分析；
* 左下方是影评选择区，此处有多条影评，用户可在此处选择影评，程序会自动将其显示在影评输入区，并将分析后的结果显示在结果显示区。
* 右下方是结果显示区，该区域用于显示结果，由两部分组成，一部分是结果的图片，好评和差评对应两个不同的表情，另一部分是评论的文字，由好评和差评两种。
* 由以上描述可知，用户可以自己输入影评进行分析，也可以选择已有的文本进行分析；
* GUI界面和后台模型联动，输入的影评会被后台获取，然后传入模型中进行预测，然后将预测结果显示到界面中。



### 2、设计思路

#### （1）界面设计

GUI界面使用使用Qt Designer进行设计，添加必要的控件，并设置好布局

<img src="http://doc.xjfyt.top/markdown_img/20221019153847.png" alt="image-20221019114414295" style="zoom: 25%;" />

#### （2）将ui文件转化为py文件

可以利用Qt Designer菜单栏中的`预览`->`View Python Code`，即可查看转化后的Python代码。

#### （3）调用UI界面

分析转化后的python文件可知，UI界面的程序是封装在一个类中的，我们编写一个新的类，继承`QMainWindow`类和这个类：

```python
class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setupUi(self)  # 加载图形界面
        self.init_ui()  # 初始化图形界面上现实的数据
        self.slot()  # 设置槽映射
```

然后创建主函数，创建该类的对象，以及显示UI界面：

```python
if __name__ == "__main__":
    app = QApplication(sys.argv)  # 开始一个QT应用
    app.setStyle('Fusion')  # 设置界面为Fusion风格
    win = MainWindow()  # 创建主窗口类
    win.show()  # 显示窗口
    sys.exit(app.exec())  # 进入消息循环
```

#### （4）定义UI数据初始函数

UI界面中有很多的数据，需要我们自己去初始化，在`MainWindow`类中创建`init_ui`函数去初始化这些数据

```python
def init_ui(self):  # 初始化UI上显示的内容
    self.load_reviews()  # 从数据库加载评论
    self.plainTextEdit.setPlainText(
        "虽然无厘头，但是搞笑+感动，袋鼠演技加分，喜欢沈腾马丽的组合，贱萌贱萌的，值得一看。") # 设置输入框初始文本
    self.label_4.setPixmap(QPixmap("./data/pictures/好评.png")) # 设置结果区域初始现实的图片
    self.label_4.setScaledContents(True) # 设置图片自适应
    self.label_5.setText("好评")  # 设置结果区初始显示的文字
```

此处还创建了一个`load_reviews`函数，该函数的作用是从`sqlite`数据库加载数据，然后将加载的数据显示在GUI界面上。

#### （5）定义信号和槽

​		Qt中很重要的概念就是信号和槽，简单地说，就是捕获界面中控件的各种事件，如点击、选择和滑动等事件，然后设置相应的槽（函数）去处理这些事件。在本项目中，我们定义了两个槽，用于捕获两个事件：

* 按钮点击事件。当用户点击`开始分析`按钮后，触发点击操作，然后内部调用函数去获取输入框的文本，并将其输入到模型中进行预测，然后将预测的结果显示到结果区。

  ```python
  def start_analyze(self):  # 进行分析
  	comment_context = self.plainTextEdit.toPlainText()  # 从输入框分析的文本
      if comment_context:  # 如果获取的文本内容不为空
  		result = self.yp_model.predict(comment_context)
  		self.label_4.setPixmap(
  			QPixmap(f"./data/pictures/{result}.png"))  # 将评论的图标设置为相应的图标
  		self.label_5.setText(result)  # 设置显示好评、差评
  ```

* 选中行事件。界面中有影评选择区，这里有很多条影评，每条影评占一行，当选中某一行时，将该行的数据显示在文本编辑框中，然后调用按钮点击事件的槽函数进行分析，并将预测的结果显示在结果区。

  ```python
  def do_currentRowChanged(self, current, previous):  # 处理选中tableView某一行的操作
  	curRec = self.model.record(current.row())  # 获取当前记录,QSqlRecord类型
  	self.plainTextEdit.setPlainText(
  		curRec.value("review"))  # 将文本输入框中的文本设置为当前选中行的文本
  	self.start_analyze()
  ```



#### （6）模型与GUI界面结合

我们创建一个类，用于加载模型和执行预测任务

```python
class MyModel:  # 用于加载模型和执行预测任务
    def __init__(self, model_name, pdparams_path):  # 指定模型名称和模型参数路径
        self.model = AutoModelForSequenceClassification.from_pretrained(
            model_name, num_classes=2)  # 加载模型
        model_pdparams = paddle.load(pdparams_path)  # 加载训练的模型参数
        self.model.load_dict(model_pdparams)  # 将加载的模型和模型参数合二为一
        self.tokenizer = AutoTokenizer.from_pretrained(model_name)  # 加载分词器
        self.label_map = {0: '差评', 1: '好评'}  # 评论映射。模型输出的结果为0或1，将其映射到好、差评中

    def predict(self, text):  # 定义预测函数
        input_ids, token_type_ids = self.tokenizer(
            text, max_seq_len=256).values()  # 调用分词器，将输入的文本分词并转化为id,即word2id
        self.model.eval()  # 进入模型评估模式
        with paddle.no_grad():  # 自动梯度计算
            input_ids = paddle.to_tensor([input_ids])  # 将word2id转化为张量
            token_type_ids = paddle.to_tensor(
                [token_type_ids])  # 将token_type_ids转化为张量
            logits = self.model(input_ids=input_ids,
                                token_type_ids=token_type_ids)  # 调用模型，将数据输入到模型中，得到预测结果
            # 模型输出的是属于每一类的概率，利用softmax函数去概率的大的
            probs = F.softmax(logits, axis=-1)
            preds = paddle.argmax(probs, axis=1).numpy()[
                0]  # 对结果进一步处理，得到类别属于0，还是1
            return self.label_map[preds]  # 返回解析后的结果，好评/差评
```

​       我们在之前GUI界面的类中，创建一个MyModel对象，该对象调用`predict`方法对从图形界面中获取的文本进行预测，然后返回预测结果，图形界面再显示预测结果。



## 九、项目总结

​       本次实验，是一次比较综合的实验，在实验过程中，不仅需要设计和训练模型，还需要自己采集数据和设计交互界面，非常考验个人的综合能力。在做本次实验中，我遇见了很多问题，如爬虫爬取不到数据、数据该如何处理、模型应如何搭建等问题，但经过多次查找资料，最终解决了各种问题，完成了项目。

​       以前做的很多课设和实验，数据都是老师给的，或可以很简单获取的。但本次的实验，数据的获取非常困难，需要去网站自行爬取。我先后尝试了爬取豆瓣、时光网和猫眼等网站，遇见了很多问题，要么网站做了限制（豆瓣），要么数据量不足（时光网），经过了一番折腾，最终在猫眼爬取了足够的数据。在本次的采集数据过程中，我了解到了很多数据采集的工具和方法，完善了自己的数据采集能力。

​	  获取数据后，需要对数据进行处理，我使用了`pandas`库对数据进行了基本的处理，如数据提取、数据去空、数据去重等，然后使用`sklearn`中的`train_test_split`函数将数据集经过两次划分，划分为了训练集、验证集和测试集，其比例为8:1:1。除了基本的数据处理外，NLP任务需要统计词频、获得word2id和label2id等，我也做了相应的处理，但在最后挑选模型时，选用了预训练模型，所以并没有用到，但让我学会了基本的处理方法，为下学期毕设提前做好了准备。

​	   数据处理之后，就需要选择模型进行训练和评估了，最初我选择了普通的LSTM和GRU模型，但一方面准确率不是很高，不能够达到预期，另一方面以我电脑孱弱的性能，训练起来也是十分缓慢的。所以最终综合考虑，我选择了百度的ERNIE 3.0预训练模型来完成这次任务，并在AI Studio平台开启了训练，结果训练迅速，准确率也符合预期。模型训练完成后，将最优的模型和参数保存下来，我使用Qt框架创建了一个简单的GUI界面来调用模型，最终取得的效果较为满意，能够实现简单的预测和良好的交互。

​		本次实验，时间紧，任务中，项目中还有很多不完善的地方，需要通过之后的学习不断提升自己的能力，以使之后的项目趋于完善。虽然弄了好久，花费了很多精力，但是却学到了很多东西，且完善了自己的综合能力，对个人的提升巨大，收获颇丰。



​     


​		





