import os
from PyQt5 import QtGui, QtWidgets
from PyQt5.QtCore import QTimer
from PyQt5.QtWidgets import QWidget
import cv2
from UI.UI import Ui_widget_Face, Ui_widget_Cert


class Fun(QWidget):
    def __init__(self, path, fun=0):
        super(Fun, self).__init__()
        self.fun = fun
        if not self.fun:
            self.ui = Ui_widget_Face()
        else:
            self.ui = Ui_widget_Cert()
        self.ui.setupUi(self)
        self.showMaximized()  # 最大化界面
        self.path = path
        self.img_size = (self.ui.label.width() - 10,
                         self.ui.label.height() - 10)
        self.show()
        self.init_camera()
        self.slot()

    def init_camera(self):  # 初始化用于摄像头刷新的timer
        self.timer = QTimer()
        self.timer.timeout.connect(self.show_image)
        self.update_image()

    def slot(self):
        self.ui.pushButton.clicked.connect(self.photograph)

    def show_image(self):
        ret, self.image = self.cap.read()  # 读取摄像头画面
        if ret:
            self.image = cv2.resize(self.image, self.img_size)  # 重新设置图片尺寸
            self.image = cv2.cvtColor(self.image, cv2.COLOR_RGB2BGR)
            self.ui.label.setPixmap(QtGui.QPixmap.fromImage(QtGui.QImage(
                self.image.data, self.image.shape[1], self.image.shape[0], QtGui.QImage.Format_RGB888)))
            self.ui.label.setScaledContents(True)

    def update_image(self):  # 更新摄像头画面，并更新开关按钮
        self.cap = cv2.VideoCapture(0)  # 打开摄像头
        self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, self.img_size[0])
        self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, self.img_size[1])
        self.cap.set(cv2.CAP_PROP_FPS, 30)
        if not self.timer.isActive():
            flag = self.cap.open(0)
            if not flag:
                msg = QtWidgets.QMessageBox.warning(self, u"警告", u"请检测相机与电脑是否连接正确",
                                                    buttons=QtWidgets.QMessageBox.Ok,
                                                    defaultButton=QtWidgets.QMessageBox.Ok)
                self.stop_all()
            else:
                self.timer.start(20)

    def photograph(self):  # 进行拍照处理，将拍照所得图片放在指定目录
        ret, frame = self.cap.read()  # 读取摄像头画面
        if ret:
            cv2image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)  # 色彩转化
            cv2.imwrite(os.path.join(self.path, "{}.upload.jpg".format(self.fun+1)),
                        frame)  # 保存用于上传的人脸照片
            cv2.imwrite(os.path.join(self.path, "{}.jpg".format(self.fun+1)),
                        cv2image)  # 保存用于对比的人脸照片
            self.stop_update_image()
            msg = QtWidgets.QMessageBox.information(self, u"Tips", u"拍照完成，请返回主界面进行对比",  # 弹出警告
                                                    buttons=QtWidgets.QMessageBox.Ok,
                                                    defaultButton=QtWidgets.QMessageBox.Ok)
            self.close()  # 关闭界面

    def stop_update_image(self):  # 停止摄像头画面刷新
        if self.timer.isActive():  # 判断timer是否启动
            self.timer.stop()  # 若已经启动则停止
        if self.cap.isOpened():  # 判断摄像头是否打开
            self.cap.release()  # 若已打开则释放摄像头

    def stop_all(self):  # 停止摄像头画面刷新并关闭窗口
        self.stop_update_image()
        self.close()

    def closeEvent(self, event):  # 关闭窗口事件
        self.stop_all()
