# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'qt2RnVhEe.ui'
##
## Created by: Qt User Interface Compiler version 6.2.3
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QMetaObject, QSize, Qt)
from PySide6.QtGui import (QFont, QIcon)
from PySide6.QtWidgets import (QFormLayout, QFrame, QGridLayout,
                               QGroupBox, QLabel, QPushButton,
                               QRadioButton, QSizePolicy, QWidget)


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(750, 600)
        sizePolicy = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(MainWindow.sizePolicy().hasHeightForWidth())
        MainWindow.setSizePolicy(sizePolicy)
        icon = QIcon()
        icon.addFile(u"./ui/heart_audio.png", QSize(), QIcon.Normal, QIcon.Off)
        MainWindow.setWindowIcon(icon)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.gridLayout_7 = QGridLayout(self.centralwidget)
        self.gridLayout_7.setObjectName(u"gridLayout_7")
        self.label_14 = QLabel(self.centralwidget)
        self.label_14.setObjectName(u"label_14")
        font = QFont()
        font.setPointSize(10)
        font.setBold(True)
        self.label_14.setFont(font)
        self.label_14.setAlignment(Qt.AlignCenter)

        self.gridLayout_7.addWidget(self.label_14, 0, 0, 1, 1)

        self.gridLayout_6 = QGridLayout()
        self.gridLayout_6.setObjectName(u"gridLayout_6")
        self.label_15 = QLabel(self.centralwidget)
        self.label_15.setObjectName(u"label_15")
        self.label_15.setFont(font)
        self.label_15.setAlignment(Qt.AlignCenter)

        self.gridLayout_6.addWidget(self.label_15, 0, 0, 1, 1)

        self.label_16 = QLabel(self.centralwidget)
        self.label_16.setObjectName(u"label_16")
        self.label_16.setFont(font)
        self.label_16.setAlignment(Qt.AlignCenter)

        self.gridLayout_6.addWidget(self.label_16, 0, 1, 1, 1)

        self.gridLayout_7.addLayout(self.gridLayout_6, 0, 1, 1, 1)

        self.formLayout = QFormLayout()
        self.formLayout.setObjectName(u"formLayout")
        self.pushButton = QPushButton(self.centralwidget)
        self.pushButton.setObjectName(u"pushButton")
        sizePolicy1 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.MinimumExpanding)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.pushButton.sizePolicy().hasHeightForWidth())
        self.pushButton.setSizePolicy(sizePolicy1)

        self.formLayout.setWidget(0, QFormLayout.LabelRole, self.pushButton)

        self.gridLayout = QGridLayout()
        self.gridLayout.setObjectName(u"gridLayout")
        self.label = QLabel(self.centralwidget)
        self.label.setObjectName(u"label")
        font1 = QFont()
        font1.setPointSize(12)
        font1.setBold(True)
        self.label.setFont(font1)
        self.label.setFrameShape(QFrame.StyledPanel)
        self.label.setFrameShadow(QFrame.Plain)

        self.gridLayout.addWidget(self.label, 0, 0, 1, 1)

        self.label_3 = QLabel(self.centralwidget)
        self.label_3.setObjectName(u"label_3")
        self.label_3.setFont(font1)
        self.label_3.setFrameShape(QFrame.StyledPanel)
        self.label_3.setFrameShadow(QFrame.Plain)

        self.gridLayout.addWidget(self.label_3, 1, 0, 1, 1)

        self.label_4 = QLabel(self.centralwidget)
        self.label_4.setObjectName(u"label_4")
        sizePolicy2 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Preferred)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.label_4.sizePolicy().hasHeightForWidth())
        self.label_4.setSizePolicy(sizePolicy2)
        font2 = QFont()
        font2.setPointSize(11)
        self.label_4.setFont(font2)
        self.label_4.setTabletTracking(True)
        self.label_4.setFrameShape(QFrame.Panel)
        self.label_4.setFrameShadow(QFrame.Sunken)
        self.label_4.setScaledContents(False)
        self.label_4.setAlignment(Qt.AlignLeading | Qt.AlignLeft | Qt.AlignVCenter)
        self.label_4.setWordWrap(True)

        self.gridLayout.addWidget(self.label_4, 1, 1, 1, 1)

        self.label_2 = QLabel(self.centralwidget)
        self.label_2.setObjectName(u"label_2")
        sizePolicy2.setHeightForWidth(self.label_2.sizePolicy().hasHeightForWidth())
        self.label_2.setSizePolicy(sizePolicy2)
        self.label_2.setFont(font2)
        self.label_2.setTabletTracking(True)
        self.label_2.setFrameShape(QFrame.Panel)
        self.label_2.setFrameShadow(QFrame.Sunken)
        self.label_2.setScaledContents(False)
        self.label_2.setAlignment(Qt.AlignLeading | Qt.AlignLeft | Qt.AlignVCenter)
        self.label_2.setWordWrap(True)

        self.gridLayout.addWidget(self.label_2, 0, 1, 1, 1)

        self.formLayout.setLayout(0, QFormLayout.FieldRole, self.gridLayout)

        self.pushButton_2 = QPushButton(self.centralwidget)
        self.pushButton_2.setObjectName(u"pushButton_2")
        sizePolicy1.setHeightForWidth(self.pushButton_2.sizePolicy().hasHeightForWidth())
        self.pushButton_2.setSizePolicy(sizePolicy1)

        self.formLayout.setWidget(1, QFormLayout.LabelRole, self.pushButton_2)

        self.gridLayout_2 = QGridLayout()
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.label_5 = QLabel(self.centralwidget)
        self.label_5.setObjectName(u"label_5")
        self.label_5.setFont(font1)
        self.label_5.setFrameShape(QFrame.StyledPanel)
        self.label_5.setFrameShadow(QFrame.Plain)

        self.gridLayout_2.addWidget(self.label_5, 0, 0, 1, 1)

        self.label_6 = QLabel(self.centralwidget)
        self.label_6.setObjectName(u"label_6")
        sizePolicy2.setHeightForWidth(self.label_6.sizePolicy().hasHeightForWidth())
        self.label_6.setSizePolicy(sizePolicy2)
        self.label_6.setFont(font2)
        self.label_6.setTabletTracking(True)
        self.label_6.setFrameShape(QFrame.Panel)
        self.label_6.setFrameShadow(QFrame.Sunken)
        self.label_6.setScaledContents(False)
        self.label_6.setAlignment(Qt.AlignLeading | Qt.AlignLeft | Qt.AlignVCenter)
        self.label_6.setWordWrap(True)

        self.gridLayout_2.addWidget(self.label_6, 0, 1, 1, 1)

        self.label_7 = QLabel(self.centralwidget)
        self.label_7.setObjectName(u"label_7")
        self.label_7.setFont(font1)
        self.label_7.setFrameShape(QFrame.StyledPanel)
        self.label_7.setFrameShadow(QFrame.Plain)

        self.gridLayout_2.addWidget(self.label_7, 1, 0, 1, 1)

        self.label_8 = QLabel(self.centralwidget)
        self.label_8.setObjectName(u"label_8")
        sizePolicy2.setHeightForWidth(self.label_8.sizePolicy().hasHeightForWidth())
        self.label_8.setSizePolicy(sizePolicy2)
        self.label_8.setFont(font2)
        self.label_8.setTabletTracking(True)
        self.label_8.setFrameShape(QFrame.Panel)
        self.label_8.setFrameShadow(QFrame.Sunken)
        self.label_8.setScaledContents(False)
        self.label_8.setAlignment(Qt.AlignLeading | Qt.AlignLeft | Qt.AlignVCenter)
        self.label_8.setWordWrap(True)

        self.gridLayout_2.addWidget(self.label_8, 1, 1, 1, 1)

        self.formLayout.setLayout(1, QFormLayout.FieldRole, self.gridLayout_2)

        self.pushButton_3 = QPushButton(self.centralwidget)
        self.pushButton_3.setObjectName(u"pushButton_3")
        sizePolicy1.setHeightForWidth(self.pushButton_3.sizePolicy().hasHeightForWidth())
        self.pushButton_3.setSizePolicy(sizePolicy1)

        self.formLayout.setWidget(2, QFormLayout.LabelRole, self.pushButton_3)

        self.gridLayout_3 = QGridLayout()
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.label_9 = QLabel(self.centralwidget)
        self.label_9.setObjectName(u"label_9")
        self.label_9.setFont(font1)
        self.label_9.setFrameShape(QFrame.StyledPanel)
        self.label_9.setFrameShadow(QFrame.Plain)

        self.gridLayout_3.addWidget(self.label_9, 0, 0, 1, 1)

        self.label_10 = QLabel(self.centralwidget)
        self.label_10.setObjectName(u"label_10")
        sizePolicy2.setHeightForWidth(self.label_10.sizePolicy().hasHeightForWidth())
        self.label_10.setSizePolicy(sizePolicy2)
        self.label_10.setFont(font2)
        self.label_10.setTabletTracking(True)
        self.label_10.setFrameShape(QFrame.Panel)
        self.label_10.setFrameShadow(QFrame.Sunken)
        self.label_10.setScaledContents(False)
        self.label_10.setAlignment(Qt.AlignLeading | Qt.AlignLeft | Qt.AlignVCenter)
        self.label_10.setWordWrap(True)

        self.gridLayout_3.addWidget(self.label_10, 0, 1, 1, 1)

        self.label_11 = QLabel(self.centralwidget)
        self.label_11.setObjectName(u"label_11")
        self.label_11.setFont(font1)
        self.label_11.setFrameShape(QFrame.StyledPanel)
        self.label_11.setFrameShadow(QFrame.Plain)

        self.gridLayout_3.addWidget(self.label_11, 1, 0, 1, 1)

        self.label_12 = QLabel(self.centralwidget)
        self.label_12.setObjectName(u"label_12")
        sizePolicy2.setHeightForWidth(self.label_12.sizePolicy().hasHeightForWidth())
        self.label_12.setSizePolicy(sizePolicy2)
        self.label_12.setFont(font2)
        self.label_12.setTabletTracking(True)
        self.label_12.setFrameShape(QFrame.Panel)
        self.label_12.setFrameShadow(QFrame.Sunken)
        self.label_12.setScaledContents(False)
        self.label_12.setAlignment(Qt.AlignLeading | Qt.AlignLeft | Qt.AlignVCenter)
        self.label_12.setWordWrap(True)

        self.gridLayout_3.addWidget(self.label_12, 1, 1, 1, 1)

        self.formLayout.setLayout(2, QFormLayout.FieldRole, self.gridLayout_3)

        self.gridLayout_7.addLayout(self.formLayout, 1, 0, 1, 1)

        self.gridLayout_4 = QGridLayout()
        self.gridLayout_4.setObjectName(u"gridLayout_4")
        self.groupBox = QGroupBox(self.centralwidget)
        self.groupBox.setObjectName(u"groupBox")
        sizePolicy3 = QSizePolicy(QSizePolicy.MinimumExpanding, QSizePolicy.Preferred)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(self.groupBox.sizePolicy().hasHeightForWidth())
        self.groupBox.setSizePolicy(sizePolicy3)
        self.groupBox.setFlat(False)
        self.groupBox.setCheckable(False)
        self.groupBox.setChecked(False)

        self.gridLayout_4.addWidget(self.groupBox, 0, 0, 1, 1)

        self.groupBox_2 = QGroupBox(self.centralwidget)
        self.groupBox_2.setObjectName(u"groupBox_2")
        sizePolicy3.setHeightForWidth(self.groupBox_2.sizePolicy().hasHeightForWidth())
        self.groupBox_2.setSizePolicy(sizePolicy3)
        self.groupBox_2.setFlat(False)
        self.groupBox_2.setCheckable(False)
        self.groupBox_2.setChecked(False)

        self.gridLayout_4.addWidget(self.groupBox_2, 1, 0, 1, 1)

        self.groupBox_3 = QGroupBox(self.centralwidget)
        self.groupBox_3.setObjectName(u"groupBox_3")
        sizePolicy3.setHeightForWidth(self.groupBox_3.sizePolicy().hasHeightForWidth())
        self.groupBox_3.setSizePolicy(sizePolicy3)
        self.groupBox_3.setFlat(False)
        self.groupBox_3.setCheckable(False)
        self.groupBox_3.setChecked(False)

        self.gridLayout_4.addWidget(self.groupBox_3, 2, 0, 1, 1)

        self.gridLayout_7.addLayout(self.gridLayout_4, 1, 1, 1, 1)

        self.label_13 = QLabel(self.centralwidget)
        self.label_13.setObjectName(u"label_13")
        font3 = QFont()
        font3.setPointSize(18)
        self.label_13.setFont(font3)
        self.label_13.setAlignment(Qt.AlignCenter)

        self.gridLayout_7.addWidget(self.label_13, 2, 0, 1, 1)

        self.gridLayout_5 = QGridLayout()
        self.gridLayout_5.setObjectName(u"gridLayout_5")
        self.radioButton = QRadioButton(self.centralwidget)
        self.radioButton.setObjectName(u"radioButton")
        font4 = QFont()
        font4.setPointSize(14)
        font4.setBold(False)
        self.radioButton.setFont(font4)

        self.gridLayout_5.addWidget(self.radioButton, 0, 0, 1, 1)

        self.radioButton_3 = QRadioButton(self.centralwidget)
        self.radioButton_3.setObjectName(u"radioButton_3")
        self.radioButton_3.setFont(font4)

        self.gridLayout_5.addWidget(self.radioButton_3, 0, 1, 1, 1)

        self.radioButton_2 = QRadioButton(self.centralwidget)
        self.radioButton_2.setObjectName(u"radioButton_2")
        self.radioButton_2.setFont(font4)

        self.gridLayout_5.addWidget(self.radioButton_2, 1, 0, 1, 1)

        self.radioButton_4 = QRadioButton(self.centralwidget)
        self.radioButton_4.setObjectName(u"radioButton_4")
        self.radioButton_4.setFont(font4)

        self.gridLayout_5.addWidget(self.radioButton_4, 1, 1, 1, 1)

        self.gridLayout_7.addLayout(self.gridLayout_5, 2, 1, 1, 1)

        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)

    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"\u5fc3\u97f3\u5206\u6790", None))
        self.label_14.setText(QCoreApplication.translate("MainWindow", u"\u6587\u4ef6\u4fe1\u606f", None))
        self.label_15.setText(QCoreApplication.translate("MainWindow", u"\u964d\u566a\u524d", None))
        self.label_16.setText(QCoreApplication.translate("MainWindow", u"\u964d\u566a\u540e", None))
        self.pushButton.setText(QCoreApplication.translate("MainWindow", u"\u6587\u4ef6\u4e00", None))
        self.label.setText(QCoreApplication.translate("MainWindow", u"\u4f4d\u7f6e\uff1a", None))
        self.label_3.setText(QCoreApplication.translate("MainWindow", u"\u75be\u75c5\uff1a", None))
        self.label_4.setText(
            QCoreApplication.translate("MainWindow", u"\u4e8c\u5c16\u74e3\u5173\u95ed\u4e0d\u5168", None))
        self.label_2.setText(QCoreApplication.translate("MainWindow", u"\u5fc3\u5c16\u90e8", None))
        self.pushButton_2.setText(QCoreApplication.translate("MainWindow", u"\u6587\u4ef6\u4e8c", None))
        self.label_5.setText(QCoreApplication.translate("MainWindow", u"\u4f4d\u7f6e\uff1a", None))
        self.label_6.setText(QCoreApplication.translate("MainWindow", u"\u5fc3\u5c16\u90e8", None))
        self.label_7.setText(QCoreApplication.translate("MainWindow", u"\u75be\u75c5\uff1a", None))
        self.label_8.setText(
            QCoreApplication.translate("MainWindow", u"\u4e8c\u5c16\u74e3\u5173\u95ed\u4e0d\u5168", None))
        self.pushButton_3.setText(QCoreApplication.translate("MainWindow", u"\u6587\u4ef6\u4e09", None))
        self.label_9.setText(QCoreApplication.translate("MainWindow", u"\u4f4d\u7f6e\uff1a", None))
        self.label_10.setText(QCoreApplication.translate("MainWindow", u"\u5fc3\u5c16\u90e8", None))
        self.label_11.setText(QCoreApplication.translate("MainWindow", u"\u75be\u75c5\uff1a", None))
        self.label_12.setText(
            QCoreApplication.translate("MainWindow", u"\u4e8c\u5c16\u74e3\u5173\u95ed\u4e0d\u5168", None))
        self.groupBox.setTitle("")
        self.groupBox_2.setTitle("")
        self.groupBox_3.setTitle("")
        self.label_13.setText(QCoreApplication.translate("MainWindow", u"\u56fe\u50cf\u9009\u62e9\uff1a", None))
        self.radioButton.setText(QCoreApplication.translate("MainWindow", u"\u9759\u6001\u6ce2\u5f62\u56fe", None))
        self.radioButton_3.setText(QCoreApplication.translate("MainWindow", u"\u9891\u8c31\u56fe", None))
        self.radioButton_2.setText(QCoreApplication.translate("MainWindow", u"\u52a8\u6001\u6ce2\u5f62\u56fe", None))
        self.radioButton_4.setText(QCoreApplication.translate("MainWindow", u"\u8bed\u8c31\u56fe", None))
    # retranslateUi
