import librosa
import librosa.display
import matplotlib.pyplot as plt
import numpy as np
from scipy import signal
from scipy.fft import fft

plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号


class DataProce:
    def __init__(self, path, ax1, ax2) -> None:
        self.ax1, self.ax2 = ax1, ax2  # 获取画图句柄
        self.y, self.sr = librosa.load(path)  # 加载语音数据
        self.no_noise_y = self.denoise()  # 获取降噪后的数据
        self.i = 0
        self.length = len(self.y)
        self.figure = [self.figure1, self.figure2,
                       self.figure3, self.figure4]

    def denoise(self, order=2, fc1=5, fc2=400):  # 语音文件降噪
        b, a = signal.butter(
            N=order, Wn=[2 * fc1 / self.sr, 2 * fc2 / self.sr], btype='bandpass')
        return signal.lfilter(b, a, self.y)  # 降噪后的数据

    def figure1(self):  # 绘制降噪前后的静态波形图
        self.plot1(self.y, self.ax1)
        self.plot1(self.no_noise_y, self.ax2)
        self.ax1.set_xlabel("时间(s)")
        self.ax2.set_xlabel("时间(s)")
        self.ax1.set_ylabel("振幅")
        self.ax2.set_ylabel("振幅")

    def figure2(self):  # 绘制降噪前后的动态波形图
        self.plot2()
        self.ax1.set_xlabel("时长")
        self.ax2.set_xlabel("时长")
        self.ax1.set_ylabel("振幅")
        self.ax2.set_ylabel("振幅")

    def figure3(self):  # 绘制降噪前后的频谱图
        self.plot3(self.y, self.ax1)
        self.plot3(self.no_noise_y, self.ax2)
        self.ax1.set_xlabel("频率(Hz)")
        self.ax2.set_xlabel("频率(Hz)")
        self.ax1.set_ylabel("幅度(dB)")
        self.ax2.set_ylabel("幅度(dB)")

    def figure4(self):  # 绘制降噪前后的语谱图
        self.plot4(self.y, self.ax1)
        self.plot4(self.no_noise_y, self.ax2)
        self.ax1.set_xlabel("时间(s)")
        self.ax2.set_xlabel("时间(s)")
        self.ax1.set_ylabel("频率(Hz)")
        self.ax2.set_ylabel("频率(Hz)")

    def plot1(self, y, ax):  # 静态波形图
        librosa.display.waveshow(y, sr=self.sr, ax=ax)

    def plot2(self):
        self.i += 100
        self.ax1.plot(self.y[self.i %
                             self.length:(self.i + 3000) % self.length])
        self.ax2.plot(self.no_noise_y[self.i %
                                      self.length:(self.i + 3000) % self.length])

    def plot3(self, y, ax):  # 频谱图
        ft = fft(y)
        magnitude = np.absolute(ft)
        frequency = np.linspace(0, self.sr, len(magnitude))
        ax.plot(frequency, magnitude)

    def plot4(self, y, ax):  # 语谱图
        melspec = librosa.feature.melspectrogram(y=y, sr=self.sr)
        logmelspe = librosa.power_to_db(melspec)
        librosa.display.specshow(logmelspe, y_axis='mel',
                                 sr=self.sr, x_axis='time', ax=ax)
        # self.cb = plt.colorbar(img, ax=ax, format="%+2.f dB")
