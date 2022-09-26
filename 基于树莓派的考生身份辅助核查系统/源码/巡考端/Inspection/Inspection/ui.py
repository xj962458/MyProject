# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'test1wQWDQT.ui'
##
## Created by: Qt User Interface Compiler version 5.15.2
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide2.QtCore import *
from PySide2.QtGui import *
from PySide2.QtWidgets import *


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(1280, 800)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.horizontalLayout = QHBoxLayout(self.centralwidget)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.splitter_9 = QSplitter(self.centralwidget)
        self.splitter_9.setObjectName(u"splitter_9")
        self.splitter_9.setOrientation(Qt.Horizontal)
        self.tableView = QTableView(self.splitter_9)
        self.tableView.setObjectName(u"tableView")
        sizePolicy = QSizePolicy(
            QSizePolicy.MinimumExpanding, QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.tableView.sizePolicy().hasHeightForWidth())
        self.tableView.setSizePolicy(sizePolicy)
        self.tableView.setMinimumSize(QSize(750, 0))
        self.tableView.setMaximumSize(QSize(750, 16777215))
        self.splitter_9.addWidget(self.tableView)
        self.splitter_8 = QSplitter(self.splitter_9)
        self.splitter_8.setObjectName(u"splitter_8")
        self.splitter_8.setOrientation(Qt.Vertical)
        self.splitter_3 = QSplitter(self.splitter_8)
        self.splitter_3.setObjectName(u"splitter_3")
        self.splitter_3.setMinimumSize(QSize(0, 280))
        self.splitter_3.setOrientation(Qt.Vertical)
        self.splitter = QSplitter(self.splitter_3)
        self.splitter.setObjectName(u"splitter")
        self.splitter.setOrientation(Qt.Horizontal)
        self.label_3 = QLabel(self.splitter)
        self.label_3.setObjectName(u"label_3")
        self.label_3.setMaximumSize(QSize(16777215, 20))
        self.label_3.setAlignment(Qt.AlignCenter)
        self.splitter.addWidget(self.label_3)
        self.label_4 = QLabel(self.splitter)
        self.label_4.setObjectName(u"label_4")
        self.label_4.setMaximumSize(QSize(16777215, 20))
        self.label_4.setAlignment(Qt.AlignCenter)
        self.splitter.addWidget(self.label_4)
        self.splitter_3.addWidget(self.splitter)
        self.splitter_2 = QSplitter(self.splitter_3)
        self.splitter_2.setObjectName(u"splitter_2")
        self.splitter_2.setOrientation(Qt.Horizontal)
        self.label = QLabel(self.splitter_2)
        self.label.setObjectName(u"label")
        self.label.setStyleSheet(u"background-color: rgb(0, 0, 0);")
        self.label.setAlignment(Qt.AlignCenter)
        self.splitter_2.addWidget(self.label)
        self.label_2 = QLabel(self.splitter_2)
        self.label_2.setObjectName(u"label_2")
        self.label_2.setStyleSheet(u"background-color: rgb(0, 0, 0);")
        self.label_2.setAlignment(Qt.AlignCenter)
        self.splitter_2.addWidget(self.label_2)
        self.splitter_3.addWidget(self.splitter_2)
        self.splitter_8.addWidget(self.splitter_3)
        self.splitter_7 = QSplitter(self.splitter_8)
        self.splitter_7.setObjectName(u"splitter_7")
        self.splitter_7.setMinimumSize(QSize(0, 252))
        self.splitter_7.setOrientation(Qt.Vertical)
        self.splitter_6 = QSplitter(self.splitter_7)
        self.splitter_6.setObjectName(u"splitter_6")
        self.splitter_6.setOrientation(Qt.Horizontal)
        self.label_11 = QLabel(self.splitter_6)
        self.label_11.setObjectName(u"label_11")
        sizePolicy1 = QSizePolicy(QSizePolicy.Maximum, QSizePolicy.Preferred)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(
            self.label_11.sizePolicy().hasHeightForWidth())
        self.label_11.setSizePolicy(sizePolicy1)
        self.label_11.setMinimumSize(QSize(100, 0))
        self.label_11.setMaximumSize(QSize(100, 80))
        font = QFont()
        font.setPointSize(20)
        self.label_11.setFont(font)
        self.label_11.setStyleSheet(u"background-color: rgb(0, 85, 255);")
        self.splitter_6.addWidget(self.label_11)
        self.label_13 = QLabel(self.splitter_6)
        self.label_13.setObjectName(u"label_13")
        sizePolicy2 = QSizePolicy(
            QSizePolicy.MinimumExpanding, QSizePolicy.Preferred)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(
            self.label_13.sizePolicy().hasHeightForWidth())
        self.label_13.setSizePolicy(sizePolicy2)
        self.label_13.setMaximumSize(QSize(16777215, 80))
        self.label_13.setFont(font)
        self.label_13.setStyleSheet(u"background-color: rgb(170, 255, 255);")
        self.splitter_6.addWidget(self.label_13)
        self.splitter_7.addWidget(self.splitter_6)
        self.splitter_4 = QSplitter(self.splitter_7)
        self.splitter_4.setObjectName(u"splitter_4")
        self.splitter_4.setOrientation(Qt.Horizontal)
        self.label_6 = QLabel(self.splitter_4)
        self.label_6.setObjectName(u"label_6")
        sizePolicy1.setHeightForWidth(
            self.label_6.sizePolicy().hasHeightForWidth())
        self.label_6.setSizePolicy(sizePolicy1)
        self.label_6.setMinimumSize(QSize(100, 0))
        self.label_6.setMaximumSize(QSize(100, 80))
        self.label_6.setFont(font)
        self.label_6.setStyleSheet(u"background-color: rgb(85, 85, 0);")
        self.splitter_4.addWidget(self.label_6)
        self.label_7 = QLabel(self.splitter_4)
        self.label_7.setObjectName(u"label_7")
        sizePolicy2.setHeightForWidth(
            self.label_7.sizePolicy().hasHeightForWidth())
        self.label_7.setSizePolicy(sizePolicy2)
        self.label_7.setMaximumSize(QSize(16777215, 80))
        self.label_7.setFont(font)
        self.label_7.setStyleSheet(u"background-color: rgb(170, 255, 255);")
        self.splitter_4.addWidget(self.label_7)
        self.splitter_7.addWidget(self.splitter_4)
        self.splitter_5 = QSplitter(self.splitter_7)
        self.splitter_5.setObjectName(u"splitter_5")
        self.splitter_5.setOrientation(Qt.Horizontal)
        self.label_9 = QLabel(self.splitter_5)
        self.label_9.setObjectName(u"label_9")
        sizePolicy1.setHeightForWidth(
            self.label_9.sizePolicy().hasHeightForWidth())
        self.label_9.setSizePolicy(sizePolicy1)
        self.label_9.setMinimumSize(QSize(100, 0))
        self.label_9.setMaximumSize(QSize(100, 80))
        self.label_9.setFont(font)
        self.label_9.setStyleSheet(u"background-color: rgb(255, 255, 0);")
        self.splitter_5.addWidget(self.label_9)
        self.label_10 = QLabel(self.splitter_5)
        self.label_10.setObjectName(u"label_10")
        sizePolicy2.setHeightForWidth(
            self.label_10.sizePolicy().hasHeightForWidth())
        self.label_10.setSizePolicy(sizePolicy2)
        self.label_10.setMaximumSize(QSize(16777215, 80))
        self.label_10.setFont(font)
        self.label_10.setStyleSheet(u"background-color: rgb(170, 255, 255);")
        self.splitter_5.addWidget(self.label_10)
        self.splitter_7.addWidget(self.splitter_5)
        self.splitter_8.addWidget(self.splitter_7)
        self.label_5 = QLabel(self.splitter_8)
        self.label_5.setObjectName(u"label_5")
        self.label_5.setMaximumSize(QSize(16777215, 150))
        font1 = QFont()
        font1.setPointSize(30)
        self.label_5.setFont(font1)
        self.label_5.setStyleSheet(u"background-color: rgb(255, 0, 0);")
        self.label_5.setAlignment(Qt.AlignCenter)
        self.splitter_8.addWidget(self.label_5)
        self.splitter_9.addWidget(self.splitter_8)

        self.horizontalLayout.addWidget(self.splitter_9)

        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate(
            "MainWindow", u"\u57fa\u4e8e\u6811\u8393\u6d3e\u7684\u8003\u751f\u8eab\u4efd\u8f85\u52a9\u6838\u67e5\u7cfb\u7edf(\u5de1\u8003\u7aef\uff09", None))
        self.label_3.setText(QCoreApplication.translate(
            "MainWindow", u"\u4eba\u8138\u56fe\u7247", None))
        self.label_4.setText(QCoreApplication.translate(
            "MainWindow", u"\u8bc1\u4ef6\u56fe\u7247", None))
        self.label.setText(QCoreApplication.translate(
            "MainWindow", u"TextLabel", None))
        self.label_2.setText(QCoreApplication.translate(
            "MainWindow", u"TextLabel", None))
        self.label_11.setText(QCoreApplication.translate(
            "MainWindow", u"\u65f6\u95f4\uff1a", None))
        self.label_13.setText(QCoreApplication.translate(
            "MainWindow", u"2021-05-08 13:50:30", None))
        self.label_6.setText(QCoreApplication.translate(
            "MainWindow", u"\u6559\u5ba4\uff1a", None))
        self.label_7.setText(QCoreApplication.translate(
            "MainWindow", u"1J506", None))
        self.label_9.setText(QCoreApplication.translate(
            "MainWindow", u"\u76f8\u4f3c\u5ea6\uff1a", None))
        self.label_10.setText(
            QCoreApplication.translate("MainWindow", u"87%", None))
        self.label_5.setText(QCoreApplication.translate("MainWindow", u"\u4eba\u8bc1\u5bf9\u6bd4\u4e0d\u901a\u8fc7,\n"
                                                        "\u9700\u8981\u4eba\u5de5\u6838\u5b9e", None))
    # retranslateUi
