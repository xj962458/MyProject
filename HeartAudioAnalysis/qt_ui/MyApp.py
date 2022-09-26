import gc
import re

from PySide6.QtCore import QTimer
from PySide6.QtWidgets import QMainWindow, QFileDialog, QGridLayout
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure

from data_proce import DataProce
from ui.ui import Ui_MainWindow


class MyApp(QMainWindow, Ui_MainWindow):
    def __init__(self) -> None:
        super(MyApp, self).__init__()
        self.setupUi(self)
        self.init_var()  # 初始化变量
        self.slot()  # 映射按钮
        self.activateWindow()

    def init_var(self):
        '''初始化文件信息'''
        self.file = [[r"./心音数据/g胸骨左缘三四肋间/室间隔缺损/g0080.wav", "a0073.wav", "胸骨左缘三四肋间", "室间隔缺损"],
                     [r"./心音数据/b胸骨右缘第二肋间/二尖瓣三尖瓣主动脉瓣联合瓣膜病/b0021.wav",
                      "b0021.wav", "胸骨右缘第二肋间", "二尖瓣三尖瓣主动脉瓣联合瓣膜病"],
                     [r"./心音数据/g胸骨左缘三四肋间/二尖瓣三尖瓣主动脉瓣联合瓣膜病/g0021.wav", "g0021.wav", "胸骨左缘三四肋间",
                      "二尖瓣三尖瓣主动脉瓣联合瓣膜病"]]  # 文件信息，包含文件路径、测量位置和疾病种类
        ''''''''''''''''''

        '''初始化绘图设置'''
        self.F = [Figure() for i in range(3)]  # 创建画图面板
        for f in self.F:
            f.subplots_adjust(left=0.05, right=0.98,
                              bottom=0.2, top=0.9,
                              hspace=0.2, wspace=0.2)
        self.F_Qt = [FigureCanvas(f) for f in self.F]  # 转化为qt对象
        self.ax1 = [ax1.add_subplot(121) for ax1 in self.F]  # 添加一子图
        self.ax2 = [ax2.add_subplot(122) for ax2 in self.F]  # 添加二子图
        self.gridlayout = []
        gl = [QGridLayout(gb)
              for gb in [self.groupBox, self.groupBox_2, self.groupBox_3]]
        self.gridlayout.extend(gl)  # 创建布局，继承于QGroupBox
        for i, g in enumerate(self.gridlayout):
            g.addWidget(self.F_Qt[i], 0, 0)  # 将图像添加到布局中
            self.ax1[i].spines['top'].set_visible(False)
            self.ax2[i].spines['top'].set_visible(False)
            self.ax1[i].spines['right'].set_visible(False)
            self.ax2[i].spines['right'].set_visible(False)
        ''''''''''''''''''

        '''初始化文件处理和画图的变量'''
        self.file_d = [
            DataProce(self.file[i][0], self.ax1[i], self.ax2[i]) for i in range(3)]  # 文件处理和画图类
        self.timer = QTimer()
        self.timer.timeout.connect(self.update_figure)
        ''''''''''''''''''

        '''其他设置'''
        self.update_figure1()
        self.update_label_data()  # 更新界面标签
        ''''''''''''

    def load_file(self, i):  # 当重新选择文件时，用于更新文件处理类
        self.file_d[i] = DataProce(
            self.file[i][0], self.ax1[i], self.ax2[i])  # 根据要求创建文件处理类
        gc.collect()  # 自动回收内存

    def add_br(self, s):  # 是在label上显示的文字换行
        return re.sub(r"(.{5})", "\\1\r\n", s)  # 利用正则表达式对字符串每隔5个字符即添加一个换行符

    def update_label_data(self):  # 更新界面中label控件的文字，将其更新为对应的文件信息
        # 设置文件一的label文字
        self.label_2.setText(self.add_br(self.file[0][2]))
        self.label_4.setText(self.add_br(self.file[0][3]))
        # 设置文件二的label文字
        self.label_6.setText(self.add_br(self.file[1][2]))
        self.label_8.setText(self.add_br(self.file[1][3]))
        # 设置文件三的label文字
        self.label_10.setText(self.add_br(self.file[2][2]))
        self.label_12.setText(self.add_br(self.file[2][3]))

    def slot(self):  # 定义button对应的槽函数
        self.pushButton.clicked.connect(self.open_file1)
        self.pushButton_2.clicked.connect(self.open_file2)
        self.pushButton_3.clicked.connect(self.open_file3)
        self.radioButton.setChecked(True)  # 设置默认选择未静态频谱图
        self.radioButton.toggled.connect(self.update_figure1)
        self.radioButton_2.toggled.connect(self.update_figure2)
        self.radioButton_3.toggled.connect(self.update_figure3)
        self.radioButton_4.toggled.connect(self.update_figure4)

    '''选择图象时触发的函数'''

    def update_figure1(self):  # 静态波形图
        self.update_figure(0)

    def update_figure2(self):  # 动态波形图
        if not self.timer.isActive():
            self.timer.start(100)

    def update_figure3(self):  # 频谱图
        self.update_figure(2)

    def update_figure4(self):  # 语谱图
        self.update_figure(3)

    ''''''''''''''''''''''''

    '''文件打开按钮触发的函数'''

    def open_file1(self):  # 打开文件一设置
        self.update_info(0)

    def open_file2(self):  # 打开文件二设置
        self.update_info(1)

    def open_file3(self):  # 打开文件三设置
        self.update_info(2)

    ''''''''''''''''''''''''''''''

    def update_info(self, i):  # 更新文件信息的底层函数
        file_tmp = self.open_file()
        if file_tmp:
            self.file[i] = file_tmp  # 更新文件信息
            self.update_label_data()  # 更新标签文字
            self.load_file(i)
            self.ax1[i].cla()
            self.ax2[i].cla()
            self.update_single_file_figure(i)  # 更新图像
            self.F[i].canvas.draw()
            self.F[i].canvas.flush_events()

    def update_figure(self, i=1):  # 更新图像信息的底层函数
        if self.timer.isActive() and i != 1:
            self.timer.stop()
        for k in range(3):
            self.ax1[k].cla()
            self.ax2[k].cla()
            self.file_d[k].figure[i]()
            self.F[k].canvas.draw()

    def update_single_file_figure(self, i):  # 更新单个文件图像
        figure_state = self.judge_radio_button()
        self.file_d[i].figure[figure_state]()

    def judge_radio_button(self):  # 用于判断用户当前想要花的是哪个图像
        for i, rb in enumerate([self.radioButton, self.radioButton_2, self.radioButton_3, self.radioButton_4]):
            if rb.isChecked():
                return i

    def open_file(self):  # 调用打开文件窗口，用于选择文件
        filepath = QFileDialog.getOpenFileName(
            self, filter="*.wav;;*.ogg;;*.mp3")[0]
        if filepath:  # 若用户正常选择文件，若不正常选择文件，则返回None
            p = filepath.split("/")  # 分割路径，获取文件信息
            filename = p[-1]  # 文件名称
            illness = p[-2]  # 疾病类型
            position = p[-3][1:]  # 心音检测位置
            return filepath, filename, position, illness
