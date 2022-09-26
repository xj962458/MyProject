# -*- coding: utf-8 -*-

################################################################################
# Form generated from reading UI file 'mainWintaCquI.ui'
##
# Created by: Qt User Interface Compiler version 5.15.2
##
# WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(720, 432)
        icon = QIcon()
        icon.addFile(u"./UI/Logo/\u4eba\u8bc1\u5bf9\u6bd4.png",
                     QSize(), QIcon.Normal, QIcon.Off)
        MainWindow.setWindowIcon(icon)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.verticalLayout = QVBoxLayout(self.centralwidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.splitter = QSplitter(self.centralwidget)
        self.splitter.setObjectName(u"splitter")
        sizePolicy = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.splitter.sizePolicy().hasHeightForWidth())
        self.splitter.setSizePolicy(sizePolicy)
        self.splitter.setOrientation(Qt.Horizontal)
        self.label = QLabel(self.splitter)
        self.label.setObjectName(u"label")
        self.label.setAlignment(Qt.AlignCenter)
        self.splitter.addWidget(self.label)
        self.label_status = QLabel(self.splitter)
        self.label_status.setObjectName(u"label_status")
        self.label_status.setAlignment(Qt.AlignCenter)
        self.splitter.addWidget(self.label_status)
        self.label_1 = QLabel(self.splitter)
        self.label_1.setObjectName(u"label_1")
        self.label_1.setAlignment(Qt.AlignCenter)
        self.splitter.addWidget(self.label_1)

        self.verticalLayout.addWidget(self.splitter)

        self.splitter_2 = QSplitter(self.centralwidget)
        self.splitter_2.setObjectName(u"splitter_2")
        sizePolicy1 = QSizePolicy(
            QSizePolicy.Expanding, QSizePolicy.MinimumExpanding)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(
            self.splitter_2.sizePolicy().hasHeightForWidth())
        self.splitter_2.setSizePolicy(sizePolicy1)
        self.splitter_2.setOrientation(Qt.Horizontal)
        self.label_2 = QLabel(self.splitter_2)
        self.label_2.setObjectName(u"label_2")
        sizePolicy2 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(
            self.label_2.sizePolicy().hasHeightForWidth())
        self.label_2.setSizePolicy(sizePolicy2)
        self.label_2.setStyleSheet(u"background-color: rgb(0, 0, 0);")
        self.splitter_2.addWidget(self.label_2)
        self.label_5 = QLabel(self.splitter_2)
        self.label_5.setObjectName(u"label_5")
        sizePolicy2.setHeightForWidth(
            self.label_5.sizePolicy().hasHeightForWidth())
        self.label_5.setSizePolicy(sizePolicy2)
        self.label_5.setStyleSheet(u"background-color: rgb(0, 0, 0);")
        self.splitter_2.addWidget(self.label_5)

        self.verticalLayout.addWidget(self.splitter_2)

        self.splitter_4 = QSplitter(self.centralwidget)
        self.splitter_4.setObjectName(u"splitter_4")
        sizePolicy3 = QSizePolicy(
            QSizePolicy.MinimumExpanding, QSizePolicy.Preferred)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(
            self.splitter_4.sizePolicy().hasHeightForWidth())
        self.splitter_4.setSizePolicy(sizePolicy3)
        self.splitter_4.setMinimumSize(QSize(0, 100))
        self.splitter_4.setOrientation(Qt.Vertical)
        self.splitter_3 = QSplitter(self.splitter_4)
        self.splitter_3.setObjectName(u"splitter_3")
        sizePolicy4 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Preferred)
        sizePolicy4.setHorizontalStretch(0)
        sizePolicy4.setVerticalStretch(0)
        sizePolicy4.setHeightForWidth(
            self.splitter_3.sizePolicy().hasHeightForWidth())
        self.splitter_3.setSizePolicy(sizePolicy4)
        self.splitter_3.setOrientation(Qt.Horizontal)
        font = QFont()
        font.setFamily(u"\u6977\u4f53")
        font.setPointSize(18)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_face = QPushButton(self.splitter_3)
        self.pushButton_face.setObjectName(u"pushButton_face")
        sizePolicy3.setHeightForWidth(
            self.pushButton_face.sizePolicy().hasHeightForWidth())
        self.pushButton_face.setSizePolicy(sizePolicy3)
        self.pushButton_face.setMinimumSize(QSize(0, 48))
        self.pushButton_face.setFont(font)
        self.splitter_3.addWidget(self.pushButton_face)
        self.pushButton_cert = QPushButton(self.splitter_3)
        self.pushButton_cert.setObjectName(u"pushButton_cert")
        sizePolicy3.setHeightForWidth(
            self.pushButton_cert.sizePolicy().hasHeightForWidth())
        self.pushButton_cert.setSizePolicy(sizePolicy3)
        self.pushButton_cert.setMinimumSize(QSize(0, 48))
        self.pushButton_cert.setFont(font)
        self.splitter_3.addWidget(self.pushButton_cert)
        self.splitter_4.addWidget(self.splitter_3)
        self.pushButton_compa = QPushButton(self.splitter_4)
        self.pushButton_compa.setObjectName(u"pushButton_compa")
        sizePolicy3.setHeightForWidth(
            self.pushButton_compa.sizePolicy().hasHeightForWidth())
        self.pushButton_compa.setSizePolicy(sizePolicy3)
        self.pushButton_compa.setMinimumSize(QSize(0, 48))
        self.pushButton_compa.setFont(font)
        self.splitter_4.addWidget(self.pushButton_compa)

        self.verticalLayout.addWidget(self.splitter_4)

        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate(
            "MainWindow", u"基于树莓派的考生身份辅助核查系统", None))
        self.label.setText(QCoreApplication.translate(
            "MainWindow", u"\u4eba\u8138\u56fe\u7247", None))
        self.label_status.setText(QCoreApplication.translate(
            "MainWindow", u"\u6b22\u8fce\u4f7f\u7528", None))
        self.label_1.setText(QCoreApplication.translate(
            "MainWindow", u"\u8bc1\u4ef6\u7167\u7247", None))
        self.label_2.setText(QCoreApplication.translate(
            "MainWindow", u"TextLabel", None))
        self.label_5.setText(QCoreApplication.translate(
            "MainWindow", u"TextLabel", None))
        self.pushButton_face.setText(QCoreApplication.translate(
            "MainWindow", u"\u4eba\u8138\u91c7\u96c6", None))
        self.pushButton_cert.setText(QCoreApplication.translate(
            "MainWindow", u"\u8bc1\u4ef6\u91c7\u96c6", None))
        self.pushButton_compa.setText(QCoreApplication.translate(
            "MainWindow", u"\u5bf9\u6bd4", None))
    # retranslateUi


class Ui_widget_Face(object):
    def setupUi(self, widget):
        if not widget.objectName():
            widget.setObjectName(u"widget")
        widget.resize(640, 480)
        icon = QIcon()
        icon.addFile(u"./UI/Logo/\u4eba\u8138.png",
                     QSize(), QIcon.Normal, QIcon.Off)
        widget.setWindowIcon(icon)
        self.verticalLayout = QVBoxLayout(widget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.splitter = QSplitter(widget)
        self.splitter.setObjectName(u"splitter")
        self.splitter.setOrientation(Qt.Vertical)
        self.label = QLabel(self.splitter)
        self.label.setObjectName(u"label")
        self.label.setStyleSheet(u"background-color: rgb(0, 0, 0);")
        self.splitter.addWidget(self.label)
        self.pushButton = QPushButton(self.splitter)
        self.pushButton.setObjectName(u"pushButton")
        self.pushButton.setMaximumSize(QSize(16777215, 50))
        font = QFont()
        font.setFamily(u"\u6977\u4f53")
        font.setPointSize(20)
        self.pushButton.setFont(font)
        self.splitter.addWidget(self.pushButton)

        self.verticalLayout.addWidget(self.splitter)

        self.retranslateUi(widget)

        QMetaObject.connectSlotsByName(widget)
    # setupUi

    def retranslateUi(self, widget):
        widget.setWindowTitle(QCoreApplication.translate(
            "widget", u"\u4eba\u8138\u91c7\u96c6", None))
        self.label.setText("")
        self.pushButton.setText(QCoreApplication.translate(
            "widget", u"\u62cd\u7167", None))
    # retranslateUi


class Ui_widget_Cert(object):
    def setupUi(self, widget):
        if not widget.objectName():
            widget.setObjectName(u"widget")
        widget.resize(640, 480)
        icon = QIcon()
        icon.addFile(u"./UI/Logo/\u8bc1\u4ef6.png",
                     QSize(), QIcon.Normal, QIcon.Off)
        widget.setWindowIcon(icon)
        self.verticalLayout = QVBoxLayout(widget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.splitter = QSplitter(widget)
        self.splitter.setObjectName(u"splitter")
        self.splitter.setOrientation(Qt.Vertical)
        self.label = QLabel(self.splitter)
        self.label.setObjectName(u"label")
        self.label.setStyleSheet(u"background-color: rgb(0, 0, 0);")
        self.splitter.addWidget(self.label)
        self.pushButton = QPushButton(self.splitter)
        self.pushButton.setObjectName(u"pushButton")
        self.pushButton.setMaximumSize(QSize(16777215, 50))
        font = QFont()
        font.setFamily(u"\u6977\u4f53")
        font.setPointSize(20)
        self.pushButton.setFont(font)
        self.splitter.addWidget(self.pushButton)

        self.verticalLayout.addWidget(self.splitter)

        self.retranslateUi(widget)

        QMetaObject.connectSlotsByName(widget)
    # setupUi

    def retranslateUi(self, widget):
        widget.setWindowTitle(QCoreApplication.translate(
            "widget", u"\u8bc1\u4ef6\u91c7\u96c6", None))
        self.label.setText("")
        self.pushButton.setText(QCoreApplication.translate(
            "widget", u"\u62cd\u7167", None))
    # retranslateUi
