from PySide2.QtCore import QThread
import paramiko
import pymysql
import sqlite3
import os
import time


class Data(QThread):
    def __init__(self) -> None:
        super(Data, self).__init__()
        self.ls = []
        self.status = 1

    def run(self):
        self.sql()
        time.sleep(10)

    def sql(self):
        try:
            conn = pymysql.connect(host='106.15.59.28', port=3306,
                                   user='root', passwd='root', db='recognition', charset='utf8')
            conn1 = sqlite3.connect('./data.db3')
            cursor = conn.cursor()
            cursor1 = conn1.cursor()
            if self.status == 1:
                cursor1.execute("create table data(\
                                    id integer not null constraint data_pk primary key,\
                                    face_image        varchar(100) not null,\
                                    certificate_image varchar(100) not null,\
                                    update_time       varchar(20),\
                                    location          varchar(20) not null,\
                                    similarity        varchar(20) not null)")
                cursor1.execute(
                    "create unique index data_id_uindex on data(id)")
                conn1.commit()
            self.status += 1
            data = cursor.execute("select * from app_data")
            data = cursor.fetchall()
            for i in data:
                if i[0] not in self.ls:
                    self.face_image = i[1].split("/")[-1]
                    self.cert_image = i[2].split("/")[-1]
                    self.time = i[3].strftime("%Y%m%d-%H%M%S")
                    self.localpath = "./images/{}/".format(self.time)
                    self.ls.append(i[0])
                    sql = "INSERT INTO data(face_image, certificate_image, update_time, location, similarity) \
                        VALUES('{}','{}','{}','{}','{}')".format(self.localpath+self.face_image, self.localpath+self.cert_image, i[3], i[5], i[4])
                    ret = cursor1.execute(sql)
                    conn1.commit()
                    self.download_image()
            conn.commit()
            cursor.close()
            conn.close()
            cursor1.close()
            conn1.close()
            return True
        except:
            return False

    def download_image(self):  # 将本地捕获到的图片通过sftp协议传输到服务器指定文件夹
        try:
            tran = paramiko.Transport("106.15.59.28", 22)  # 获取Transport实例
            tran.connect(username="root", password="w20010129F")  # 连接SSH服务端
            sftp = paramiko.SFTPClient.from_transport(tran)  # 获取SFTP实例
            if not os.path.exists(self.localpath):
                os.makedirs(self.localpath)
            sftp.get(
                "/home/admin/MySite/Recognition/static/media/images/{}/".format(self.time)+self.face_image, "{}{}".format(self.localpath, self.face_image))
            sftp.get(
                "/home/admin/MySite/Recognition/static/media/images/{}/".format(self.time)+self.cert_image, "{}{}".format(self.localpath, self.cert_image))
            tran.close()  # 关闭连接
            return True
        except:
            return False
