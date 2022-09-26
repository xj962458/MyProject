import paramiko
import pymysql

# 将文件上传到服务器上的类


class Upload:
    def __init__(self, time, local_face_image, local_certificate_image, similarity, config):
        self.config = config
        self.timedir = time.replace(':', '').replace('-', '').replace(' ', '-')
        self.face_image = "{}/face_image.jpg".format(self.timedir)
        self.certificate_image = "{}/certificate_image.jpg".format(
            self.timedir)
        self.sim = similarity
        self.similarity = "{:.2f}%".format(similarity)
        self.time = time
        self.local_face_image = local_face_image
        self.local_certificate_image = local_certificate_image
        self.location = self.config['local']['classroom']

    def launch(self):  # 用来判断数据库和服务器连接是否正常
        if self.ssh():
            if self.sql():
                self.sftp()
                return True
            else:
                return False
        else:
            return False

    def sql(self):  # 将捕获到的数据存入云端MySQL数据库
        try:
            conn = pymysql.connect(host=self.config['database']['ip'], port=3306,
                                   user=self.config['database']['user'], passwd=self.config['database']['password'],
                                   db=self.config['database']['db'], charset='utf8')
            cursor = conn.cursor()
            ret = cursor.execute(
                "insert into app_data(face_image,certificate_image,update_time,similarity,location) \
                    values('images/{}','images/{}','{}','{}','{}')".format(self.face_image, self.certificate_image,
                                                                           self.time,
                                                                           self.similarity, self.location))
            if self.sim <= 80:
                ret = cursor.execute(
                    "insert into app_data1(face_image,certificate_image,update_time,similarity,location) \
                        values('images/{}','images/{}','{}','{}','{}')".format(self.face_image, self.certificate_image,
                                                                               self.time,
                                                                               self.similarity, self.location))
            conn.commit()
            cursor.close()
            conn.close()
            return True
        except:
            return False

    def ssh(self):  # 连接数据库，创建相应文件夹
        try:
            s = paramiko.SSHClient()
            s.set_missing_host_key_policy(paramiko.AutoAddPolicy())
            s.connect(hostname=self.config['server']['ip'], port=self.config['server']['port'],
                      username=self.config['server']['user'], password=self.config['server']['password'])
            s.exec_command(
                'mkdir -p {}'.format(self.config['server']['image_path'] + self.timedir))
            s.close()
            return True
        except:
            return False

    def sftp(self):  # 将本地捕获到的图片通过sftp协议传输到服务器指定文件夹
        try:
            tran = paramiko.Transport(
                self.config['server']['ip'], self.config['server']['port'])  # 获取Transport实例
            tran.connect(username=self.config['server']['user'],
                         password=self.config['server']['password'])  # 连接SSH服务端
            sftp = paramiko.SFTPClient.from_transport(tran)  # 获取SFTP实例
            sftp.put(
                self.local_face_image, self.config['server']['image_path'] + self.face_image)
            sftp.put(
                self.local_certificate_image, self.config['server']['image_path'] + self.certificate_image)
            tran.close()  # 关闭连接
            return True
        except:
            return False
