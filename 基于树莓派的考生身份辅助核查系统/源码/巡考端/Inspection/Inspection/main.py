from PySide2.QtCore import QItemSelectionModel, QTimer, Qt
from PySide2.QtGui import QPixmap
from PySide2.QtWidgets import QApplication, QDataWidgetMapper, QMainWindow, QMessageBox
from ui import Ui_MainWindow
from databases import Data
from PySide2.QtSql import QSqlDatabase, QSqlTableModel
import os


class MyApp(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super(MyApp, self).__init__()
        self.setupUi(self)
        self.init()
        self.refresh()

    def init(self):
        self.data = Data()
        self.data.start()
        self.open_database()
        self.status = 1

    def refresh(self):
        self.timer = QTimer()
        self.timer.timeout.connect(self.open_data)
        self.timer.start(10000)

    def open_data(self):
        self.data.sql()
        # self.selModel.clear()
        self.open_database()

    def open_database(self):
        self.db = QSqlDatabase.addDatabase('QSQLITE')
        self.db.setDatabaseName("./data.db3")
        if not self.db.open():
            QMessageBox.critical(
                None, ("无法打开数据库连接"), ("无法建立到数据库的连接"), QMessageBox.Cancel)
            return False

        self.model = QSqlTableModel()
        self.model.setTable('data')
        self.model.setEditStrategy(QSqlTableModel.OnFieldChange)
        self.model.select()
        self.model.setHeaderData(1, Qt.Horizontal, "人脸照片")
        self.model.setHeaderData(2, Qt.Horizontal, "证件照片")
        self.model.setHeaderData(3, Qt.Horizontal, "识别时间")
        self.model.setHeaderData(4, Qt.Horizontal, "相似度")
        self.model.setHeaderData(5, Qt.Horizontal, "识别教室")

        self.tableView.setWindowTitle("未识别通过的数据")
        self.dataMapper = QDataWidgetMapper()
        self.dataMapper.setModel(self.model)
        self.dataMapper.setSubmitPolicy(QDataWidgetMapper.AutoSubmit)
        self.dataMapper.addMapping(self.label, 1)
        self.dataMapper.addMapping(self.label_2, 2)
        self.dataMapper.addMapping(self.label_13, 3)
        self.dataMapper.addMapping(self.label_7, 4)
        self.dataMapper.addMapping(self.label_10, 5)
        self.dataMapper.toLast()

        self.selModel = QItemSelectionModel(self.model)  # 选择模型
        self.selModel.currentRowChanged.connect(
            self.do_currentRowChanged)  # 选择行变化时

        self.tableView.setModel(self.model)
        self.tableView.setSelectionModel(self.selModel)

    def do_currentRowChanged(self, current, previous):
        self.dataMapper.setCurrentIndex(current.row())  # 更新数据映射的行号
        curRec = self.model.record(current.row())  # 获取当前记录,QSqlRecord类型
        self.label_13.setText(curRec.value("update_time"))
        self.label_10.setText(curRec.value("location"))
        self.label_7.setText(curRec.value("similarity"))
        if curRec.isNull("face_image"):  # 图片字段内容为空
            self.label.clear()
        else:
            data1 = curRec.value("face_image")
            self.label.setPixmap(
                QPixmap(data1).scaled(340, 338, Qt.KeepAspectRatio))
            self.label.setScaledContents(True)

        if curRec.isNull("certificate_image"):  # 图片字段内容为空
            self.label_2.clear()
        else:
            data2 = curRec.value("certificate_image")
            self.label_2.setPixmap(
                QPixmap(data2).scaled(240, 330, Qt.KeepAspectRatio))
            self.label_2.setScaledContents(True)

    def del_file(self, path):
        ls = os.listdir(path)
        for i in ls:
            c_path = os.path.join(path, i)
            if os.path.isdir(c_path):
                self.del_file(c_path)
                os.removedirs(c_path)
            else:
                os.remove(c_path)

    def closeEvent(self, event):
        self.db.close()
        self.status = 0
        os.remove("./data.db3")
        self.del_file("./images")
        self.close()


if __name__ == "__main__":
    app = QApplication([])
    win = MyApp()
    win.show()
    app.exec_()
