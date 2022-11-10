# -*- coding: utf-8 -*-

################################################################################
# Form generated from reading UI file 'formiyeKyh.ui'
##
# Created by: Qt User Interface Compiler version 6.3.2
##
# WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QMetaObject, QSize, Qt)
from PySide6.QtGui import QIcon, QFont
from PySide6.QtWidgets import (QFrame, QHBoxLayout, QLabel,  QPlainTextEdit,
                               QPushButton, QSizePolicy, QSpacerItem, QTableView, QVBoxLayout, QWidget)

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(800, 600)
        icon = QIcon()
        icon.addFile(u"data/pictures/reviews.png",
                     QSize(), QIcon.Normal, QIcon.Off)
        MainWindow.setWindowIcon(icon)
        MainWindow.setAutoFillBackground(False)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.verticalLayout_4 = QVBoxLayout(self.centralwidget)
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.verticalSpacer = QSpacerItem(
            17, 218, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.horizontalLayout_2.addItem(self.verticalSpacer)

        self.verticalLayout = QVBoxLayout()
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.label = QLabel(self.centralwidget)
        self.label.setObjectName(u"label")
        sizePolicy = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Maximum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(
            self.label.sizePolicy().hasHeightForWidth())
        self.label.setSizePolicy(sizePolicy)
        font = QFont()
        font.setFamilies([u"\u7b49\u7ebf"])
        font.setPointSize(14)
        font.setBold(True)
        self.label.setFont(font)
        self.verticalLayout.addWidget(self.label)
        self.plainTextEdit = QPlainTextEdit(self.centralwidget)
        self.plainTextEdit.setObjectName(u"plainTextEdit")
        sizePolicy1 = QSizePolicy(
            QSizePolicy.MinimumExpanding, QSizePolicy.Minimum)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(
            self.plainTextEdit.sizePolicy().hasHeightForWidth())
        self.plainTextEdit.setSizePolicy(sizePolicy1)
        self.verticalLayout.addWidget(self.plainTextEdit)
        self.horizontalLayout_2.addLayout(self.verticalLayout)
        self.verticalSpacer_4 = QSpacerItem(
            17, 238, QSizePolicy.Minimum, QSizePolicy.Expanding)
        self.horizontalLayout_2.addItem(self.verticalSpacer_4)
        self.verticalLayout_4.addLayout(self.horizontalLayout_2)
        self.pushButton = QPushButton(self.centralwidget)
        self.pushButton.setObjectName(u"pushButton")
        self.pushButton.setFont(font)
        self.verticalLayout_4.addWidget(self.pushButton)
        self.horizontalSpacer_2 = QSpacerItem(
            779, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)
        self.verticalLayout_4.addItem(self.horizontalSpacer_2)
        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.verticalSpacer_2 = QSpacerItem(
            20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)
        self.horizontalLayout.addItem(self.verticalSpacer_2)
        self.verticalLayout_3 = QVBoxLayout()
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.label_2 = QLabel(self.centralwidget)
        self.label_2.setObjectName(u"label_2")
        font1 = QFont()
        font1.setFamilies([u"\u7b49\u7ebf"])
        font1.setPointSize(12)
        font1.setBold(True)
        self.label_2.setFont(font1)
        self.verticalLayout_3.addWidget(self.label_2)
        self.tableView = QTableView(self.centralwidget)
        self.tableView.setObjectName(u"tableView")
        sizePolicy2 = QSizePolicy(
            QSizePolicy.MinimumExpanding, QSizePolicy.Expanding)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(
            self.tableView.sizePolicy().hasHeightForWidth())
        self.tableView.setSizePolicy(sizePolicy2)
        self.tableView.setFrameShape(QFrame.WinPanel)
        self.tableView.setFrameShadow(QFrame.Raised)
        self.verticalLayout_3.addWidget(self.tableView)
        self.horizontalLayout.addLayout(self.verticalLayout_3)
        self.verticalSpacer_5 = QSpacerItem(
            20, 258, QSizePolicy.Minimum, QSizePolicy.Maximum)
        self.horizontalLayout.addItem(self.verticalSpacer_5)
        self.verticalLayout_2 = QVBoxLayout()
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.label_3 = QLabel(self.centralwidget)
        self.label_3.setObjectName(u"label_3")
        sizePolicy3 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Preferred)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(
            self.label_3.sizePolicy().hasHeightForWidth())
        self.label_3.setSizePolicy(sizePolicy3)
        self.label_3.setFont(font1)
        self.label_3.setAlignment(Qt.AlignCenter)
        self.verticalLayout_2.addWidget(self.label_3)
        self.widget = QWidget(self.centralwidget)
        self.widget.setObjectName(u"widget")
        sizePolicy4 = QSizePolicy(
            QSizePolicy.MinimumExpanding, QSizePolicy.MinimumExpanding)
        sizePolicy4.setHorizontalStretch(0)
        sizePolicy4.setVerticalStretch(0)
        sizePolicy4.setHeightForWidth(
            self.widget.sizePolicy().hasHeightForWidth())
        self.widget.setSizePolicy(sizePolicy4)
        self.verticalLayout_6 = QVBoxLayout(self.widget)
        self.verticalLayout_6.setObjectName(u"verticalLayout_6")
        self.verticalLayout_5 = QVBoxLayout()
        self.verticalLayout_5.setObjectName(u"verticalLayout_5")
        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.horizontalSpacer = QSpacerItem(
            40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)
        self.horizontalLayout_3.addItem(self.horizontalSpacer)
        self.label_4 = QLabel(self.widget)
        self.label_4.setObjectName(u"label_4")
        sizePolicy4.setHeightForWidth(
            self.label_4.sizePolicy().hasHeightForWidth())
        self.label_4.setSizePolicy(sizePolicy4)
        self.label_4.setAlignment(Qt.AlignCenter)
        self.horizontalLayout_3.addWidget(self.label_4)
        self.horizontalSpacer_3 = QSpacerItem(
            40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)
        self.horizontalLayout_3.addItem(self.horizontalSpacer_3)
        self.verticalLayout_5.addLayout(self.horizontalLayout_3)
        self.verticalLayout_6.addLayout(self.verticalLayout_5)
        self.horizontalLayout_4 = QHBoxLayout()
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.horizontalSpacer_4 = QSpacerItem(
            40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)
        self.horizontalLayout_4.addItem(self.horizontalSpacer_4)
        self.label_5 = QLabel(self.widget)
        self.label_5.setObjectName(u"label_5")
        sizePolicy5 = QSizePolicy(
            QSizePolicy.MinimumExpanding, QSizePolicy.Preferred)
        sizePolicy5.setHorizontalStretch(0)
        sizePolicy5.setVerticalStretch(0)
        sizePolicy5.setHeightForWidth(
            self.label_5.sizePolicy().hasHeightForWidth())
        self.label_5.setSizePolicy(sizePolicy5)
        font2 = QFont()
        font2.setPointSize(18)
        font2.setBold(True)
        self.label_5.setFont(font2)
        self.label_5.setAlignment(Qt.AlignCenter)
        self.horizontalLayout_4.addWidget(self.label_5)
        self.horizontalSpacer_5 = QSpacerItem(
            40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)
        self.horizontalLayout_4.addItem(self.horizontalSpacer_5)
        self.verticalLayout_6.addLayout(self.horizontalLayout_4)
        self.verticalSpacer_7 = QSpacerItem(
            20, 40, QSizePolicy.Minimum, QSizePolicy.Fixed)
        self.verticalLayout_6.addItem(self.verticalSpacer_7)
        self.verticalLayout_2.addWidget(self.widget)
        self.horizontalLayout.addLayout(self.verticalLayout_2)
        self.verticalLayout_4.addLayout(self.horizontalLayout)

        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate(
            "MainWindow", u"\u5f71\u8bc4\u5206\u6790", None))
        self.label.setText(QCoreApplication.translate(
            "MainWindow", u"\u8bf7\u8f93\u5165\u60a8\u8981\u5206\u6790\u7684\u6587\u672c\uff1a", None))
        self.pushButton.setText(QCoreApplication.translate(
            "MainWindow", u"\u5f00\u59cb\u5206\u6790", None))
        self.label_2.setText(QCoreApplication.translate(
            "MainWindow", u"\u8bf7\u9009\u62e9\u60a8\u8981\u5206\u6790\u7684\u5f71\u8bc4:", None))
        self.label_3.setText(QCoreApplication.translate(
            "MainWindow", u"\u5206\u6790\u7ed3\u679c\uff1a", None))
        self.label_4.setText(QCoreApplication.translate(
            "MainWindow", u"TextLabel", None))
        self.label_5.setText(QCoreApplication.translate(
            "MainWindow", u"\u597d\u8bc4", None))
    # retranslateUi
