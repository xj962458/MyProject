### 一、项目介绍
?        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 该项目是为自动化采集腾讯文档模板页的所有模板而设计的，使用`Python`语言编写，主要使用python的第三方库`selenium`进行设计，运行该项目需要登录相关的账号和密码。运行后会将下载的的文件分类保存，当然，用户也可以选择全部保存在一个文件夹中。项目运行前请先到`Download/path.py`中添加项目所在的绝对路径。
### 二、项目结构如下

```bash
GetTenDocum
|
├─AllFile
│  └─腾讯文档模板
|  └─腾讯文档模板_测试
|  └─cookies.json
|  └─download_link.json
|
├─Cookie
│  └─__pycache__
|  └─cookie_login.py
|  └─get_cookie.py
└─Download
|  └─__pycache__
|  └─download_file.py
|  └─get_template_link.py
|  └─path.py
├─main.py
├─move.py
├─requirements.txt
└─README.MD
```

1. `AllFile`

   ?         &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;文件夹用于存储项目运行中产生的文件，一是保存的相关配置文件，二是下载的模板；`腾讯文档模板`是用来存储下载后的文档，`腾讯文档模板_测试`是之前测试时下载的所有模板，重新执行项目会删除`腾讯文档模板`里面的所有文档并重新下载。

2. `Cookie`

   ?		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;是python的一个包，包含两个与cookie有关的函数，其中`get_cookie.py`用于获取cookie，然后将获取的cookie存储到`AllFile`文件夹下的`cookies.json`文件中，`cookie_login`从文件获取cookie并执行登录操作。

3. `Download`

   ?		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;也是Python的一个包，包含和下载相关的函数，一个是`get_template_link.py`文件，用于获取所有模板的下载链接，获取后分类存储于`AllFile`文件夹下的`download_link.json`文件中。`download_file.py`包含可以读取`download_link.json`文件获取连接后模拟用户执行下载操作，下载的文件分类保存在`AllFile/腾讯文档模板`文件夹中。还有一个`path.py`，该文件存储了项目的绝对路径，运行项目前请自行添加，用于其他函数的调用，协调该项目既可以整体运行，又可以单模块运行。

4. 函数入口                           
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(1)、 `main.py`是该项目的入口，控制整个项目的执行，该模块运行时会检测`AllFile`文件夹下是否有`cookies.json`和`download_link.json`文件，若没有检测到，则会调用`get_cookie.py`文件去获取cookie，调用`get_template_link.py`文件去执行下载操作。                      
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(2)、因cookie有一定的时效，建议运行前删除`cookes.json`文件，并在`Cookie/get_cookie.py`中添加相应的账号密码，重新获取cookie，获取cookie使用的是qq登录，故提供的账号密码为qq账号和密码。若要下载VIP文档，需要添加vip账号，并将主函数中的`vip_down`更改为`True`。                
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(3)、程序默认后台执行，不在前台显示，若需要前台显示，请修改主函数中的`background`变量为`False`。                                        
   
5. 其他文件

   ?    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(1)、`requirements.txt`为程序运行所需要的第三方库要求，可以使用`pip install -r requirements.txt`进行自动化安装，本项目在Window11操作系统，AMD4800U处理器，16G内存，python==3.9.5下可以完美运行。      
   ?		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(2)、`move.py`是将所有下载的文档移动到一个文件夹中，不同用户有不同的选择，需要移动到同一个文件夹内的用户请运行该文件，运行后会将所有模板文档下载至`./腾讯文档模板/Document中`。默认根据模板类放在不同的文件夹中。       
   ?		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(3)、`README.MD`即本文件，是对项目的的进一步说明。

