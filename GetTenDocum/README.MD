### һ����Ŀ����
?        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ����Ŀ��Ϊ�Զ����ɼ���Ѷ�ĵ�ģ��ҳ������ģ�����Ƶģ�ʹ��`Python`���Ա�д����Ҫʹ��python�ĵ�������`selenium`������ƣ����и���Ŀ��Ҫ��¼��ص��˺ź����롣���к�Ὣ���صĵ��ļ����ౣ�棬��Ȼ���û�Ҳ����ѡ��ȫ��������һ���ļ����С���Ŀ����ǰ���ȵ�`Download/path.py`��������Ŀ���ڵľ���·����
### ������Ŀ�ṹ����

```bash
GetTenDocum
|
����AllFile
��  ������Ѷ�ĵ�ģ��
|  ������Ѷ�ĵ�ģ��_����
|  ����cookies.json
|  ����download_link.json
|
����Cookie
��  ����__pycache__
|  ����cookie_login.py
|  ����get_cookie.py
����Download
|  ����__pycache__
|  ����download_file.py
|  ����get_template_link.py
|  ����path.py
����main.py
����move.py
����requirements.txt
����README.MD
```

1. `AllFile`

   ?         &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;�ļ������ڴ洢��Ŀ�����в������ļ���һ�Ǳ������������ļ����������ص�ģ�壻`��Ѷ�ĵ�ģ��`�������洢���غ���ĵ���`��Ѷ�ĵ�ģ��_����`��֮ǰ����ʱ���ص�����ģ�壬����ִ����Ŀ��ɾ��`��Ѷ�ĵ�ģ��`����������ĵ����������ء�

2. `Cookie`

   ?		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;��python��һ����������������cookie�йصĺ���������`get_cookie.py`���ڻ�ȡcookie��Ȼ�󽫻�ȡ��cookie�洢��`AllFile`�ļ����µ�`cookies.json`�ļ��У�`cookie_login`���ļ���ȡcookie��ִ�е�¼������

3. `Download`

   ?		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Ҳ��Python��һ������������������صĺ�����һ����`get_template_link.py`�ļ������ڻ�ȡ����ģ����������ӣ���ȡ�����洢��`AllFile`�ļ����µ�`download_link.json`�ļ��С�`download_file.py`�������Զ�ȡ`download_link.json`�ļ���ȡ���Ӻ�ģ���û�ִ�����ز��������ص��ļ����ౣ����`AllFile/��Ѷ�ĵ�ģ��`�ļ����С�����һ��`path.py`�����ļ��洢����Ŀ�ľ���·����������Ŀǰ���������ӣ��������������ĵ��ã�Э������Ŀ�ȿ����������У��ֿ��Ե�ģ�����С�

4. �������                           
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(1)�� `main.py`�Ǹ���Ŀ����ڣ�����������Ŀ��ִ�У���ģ������ʱ����`AllFile`�ļ������Ƿ���`cookies.json`��`download_link.json`�ļ�����û�м�⵽��������`get_cookie.py`�ļ�ȥ��ȡcookie������`get_template_link.py`�ļ�ȥִ�����ز�����                      
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(2)����cookie��һ����ʱЧ����������ǰɾ��`cookes.json`�ļ�������`Cookie/get_cookie.py`��������Ӧ���˺����룬���»�ȡcookie����ȡcookieʹ�õ���qq��¼�����ṩ���˺�����Ϊqq�˺ź����롣��Ҫ����VIP�ĵ�����Ҫ����vip�˺ţ������������е�`vip_down`����Ϊ`True`��                
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(3)������Ĭ�Ϻ�ִ̨�У�����ǰ̨��ʾ������Ҫǰ̨��ʾ�����޸��������е�`background`����Ϊ`False`��                                        
   
5. �����ļ�

   ?    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(1)��`requirements.txt`Ϊ������������Ҫ�ĵ�������Ҫ�󣬿���ʹ��`pip install -r requirements.txt`�����Զ�����װ������Ŀ��Window11����ϵͳ��AMD4800U��������16G�ڴ棬python==3.9.5�¿����������С�      
   ?		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(2)��`move.py`�ǽ��������ص��ĵ��ƶ���һ���ļ����У���ͬ�û��в�ͬ��ѡ����Ҫ�ƶ���ͬһ���ļ����ڵ��û������и��ļ������к�Ὣ����ģ���ĵ�������`./��Ѷ�ĵ�ģ��/Document��`��Ĭ�ϸ���ģ������ڲ�ͬ���ļ����С�       
   ?		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(3)��`README.MD`�����ļ����Ƕ���Ŀ�ĵĽ�һ��˵����
