## 安装依赖
```bash
python -m pip install -r ./requirements.txt
```

## 配置好数据库后先删除`./heart/migrations/`下除`__init__.py`外的文件，然后依次执行：
```bash
python ./manage.py makemigrations  # 查找变更
python ./manage.py migrate         # 将变更应用到数据库中
python ./manage.py createsuperuser # 创建管理员用户
```

## 运行
```bash
python ./manage.py runserver 0.0.0.0:8000
```