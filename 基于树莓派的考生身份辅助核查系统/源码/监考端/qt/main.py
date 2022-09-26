# This Python file uses the following encoding: utf-8
import json
import os
import sys
import threading

from PyQt5 import QtCore
from PyQt5.QtCore import QTimer, Qt
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QApplication, QMainWindow
from Function.Compare import Compare
from UI.UI import Ui_MainWindow
from Function.Function import Fun


class MyApp(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super(MyApp, self).__init__()
        self.setupUi(self)
        self.slot()
        self.show_index()
        self.load_config()
        self.com = Compare(self.label_status, self.config)
        self.showMaximized()  # 最大化·

    def load_config(self):
        with open("/home/pi/Desktop/qt/config.json", "r") as f:
            # with open("./config.json", "r") as f:
            self.config = json.load(f)

    def show_index(self):
        self.timer = QTimer()
        self.timer.timeout.connect(self.show_picture)
        self.timer.start(2000)

    def show_picture(self):
        if os.path.exists(os.path.join(self.config['local']['path'], '1.upload.jpg')):
            self.label_2.setPixmap(
                QPixmap(os.path.join(self.config['local']['path'], '1.upload.jpg')).scaled(345, 335,
                                                                                           QtCore.Qt.KeepAspectRatio))
            self.label_2.setScaledContents(True)

        if os.path.exists(os.path.join(self.config['local']['path'], '2.upload.jpg')):
            self.label_5.setPixmap(
                QPixmap(os.path.join(self.config['local']['path'], '2.upload.jpg')).scaled(345, 335,
                                                                                           QtCore.Qt.KeepAspectRatio))
            self.label_5.setScaledContents(True)

    def slot(self):
        self.pushButton_face.clicked.connect(self.face_ui)
        self.pushButton_cert.clicked.connect(self.cert_ui)
        self.pushButton_compa.clicked.connect(self.thread)

    def face_ui(self):
        self.face = Fun(self.config['local']['path'], 0)
        self.face.setAttribute(Qt.WA_DeleteOnClose, True)

    def cert_ui(self):
        self.cert = Fun(self.config['local']['path'], 1)
        self.cert.setAttribute(Qt.WA_DeleteOnClose, True)

    def compare(self):
        # com.local_compare()  #离线对比
        self.com.compare_face_baidu()  # 云端对比

    def thread(self):  # 人脸对比线程开启
        if not os.path.exists(os.path.join(self.config['local']['path'], '1.jpg')) or not os.path.exists(
                os.path.join(self.config['local']['path'], '2.jpg')):
            self.label_status.setText(u'图片不存在，请重新采集！')
        else:
            self.label_status.setText(u"对比中...")
            self.thread0 = threading.Thread(target=self.compare)
            self.thread0.start()

    def del_file(self, path):
        ls = os.listdir(path)
        for i in ls:
            c_path = os.path.join(path, i)
            if os.path.isdir(c_path):
                self.del_file(c_path)
            else:
                os.remove(c_path)

    def closeEvent(self, event):  # 定义关闭窗口所触发的操作try
        try:
            self.face.stop_all()
        except:
            pass
        try:
            self.cert.stop_all()
        except:
            pass
        try:
            self.del_file(self.config['local']['path'])
        except FileNotFoundError:
            pass


if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MyApp()
    win.show()
    win.setAttribute(Qt.WA_DeleteOnClose, True)
    sys.exit(app.exec_())
