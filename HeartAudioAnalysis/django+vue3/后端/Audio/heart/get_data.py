import base64
from io import BytesIO

import librosa
import librosa.display
import logmmse
import matplotlib.pyplot as plt
import numpy as np
from scipy.fft import fft
from scipy.io import wavfile

from heart.models import Audio

plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号


class AudioProce:
    def __init__(self, filepath, sr=16000):
        tmp = filepath.split("/")
        self.filepath = filepath  # 路径
        self.sr = sr  # 采样率
        self.filename = tmp[-1]  # 文件名
        self.illness = tmp[-2] if tmp[-2] != "audio_data" else "未知"  # 疾病类型
        self.position = tmp[-3] if tmp[-3] != "static" else "未知"  # 采集位置
        self.y = self.load_y()  # 原始数据
        self.times = len(self.y) / self.sr
        self.denoise_y = self.load_denoise_y(self.y)  # 降噪后数据

        # 定义全局变量,用于心率获取
        self.s_veD, self.s_veJiZhi = [], []  # 分别用于存储极值和均值
        self.nUINT = 32
        self.nBlock_2_s = 32000 / self.nUINT
        self.s_nSearchMaxIndex = 0  # 在2秒的数据内寻找极值，当前的这个下标
        self.s_nBeginBlock = 0  # 起始块
        self.s_nBeginKeeping = 1  # 起始块没有变动的次数

        plt.figure()  # 开始绘图

        self.p11 = self.waveform(self.y)  # 降噪前波形图
        self.p12 = self.freqspec(self.y)  # 降噪前频谱图
        self.p13 = self.speespec(self.y)  # 降噪前语谱图
        self.p14 = self.loudness_figure(self.y)  # 降噪前响度曲线

        self.p21 = self.waveform(self.denoise_y)  # 降噪后波形图
        self.p22 = self.freqspec(self.denoise_y)  # 降噪后频谱图
        self.p23 = self.speespec(self.denoise_y)  # 降噪后语谱图
        self.p24 = self.loudness_figure(self.denoise_y)  # 降噪后响度曲线

        self.p3 = self.get_xl_figure(self.filepath)  # 获取心率曲线

        plt.close("all")  # 结束绘图

        self.add_to_databases()  # 将数据添加到数据库中

    def add_to_databases(self):  # 将获取的数据添加到数据库
        Audio.objects.create(filename=self.filename, filepath=self.filepath, illness=self.illness,
                             position=self.position, sr=self.sr, times="{:.2f}s".format(self.times), p11=self.p11,
                             p12=self.p12,
                             p13=self.p13, p14=self.p14, p21=self.p21, p22=self.p22, p23=self.p23, p24=self.p24,
                             p3=self.p3)

    def load_y(self):  # 读取数据并进行降噪
        y, _ = librosa.load(self.filepath, sr=self.sr)
        return y

    def load_denoise_y(self, y):  # 获取降噪后数据
        return logmmse.logmmse(data=y, sampling_rate=self.sr)

    def waveform(self, y):  # 绘制波形图
        plt.clf()
        librosa.display.waveshow(y, sr=self.sr)
        plt.xlabel("时间(s)")
        plt.ylabel("振幅")
        figfile = BytesIO()
        plt.savefig(figfile, format='png', bbox_inches='tight', pad_inches=0.0)
        fig_str = str(base64.b64encode(figfile.getvalue()), "utf-8")  # 将图片转为base64字符串
        return fig_str

    def freqspec(self, y):  # 绘制频谱图
        ft = fft(y)
        magnitude = np.absolute(ft)  # 对fft的结果直接取模（取绝对值），得到幅度magnitude
        frequency = np.linspace(0, self.sr, len(magnitude))
        plt.clf()
        plt.plot(frequency[:30000], magnitude[:30000])
        plt.xlabel("频率(Hz)")
        plt.ylabel("幅度(dB)")
        # plt.title('语音信号频域谱线')
        figfile = BytesIO()
        plt.savefig(figfile, format='png', bbox_inches='tight', pad_inches=0.0)
        fig_str = str(base64.b64encode(figfile.getvalue()), "utf-8")  # 将图片转为base64字符串
        return fig_str

    def speespec(self, y):  # 绘制梅尔频率语谱图
        melspec = librosa.feature.melspectrogram(y=y, sr=self.sr)
        logmelspe = librosa.power_to_db(melspec)
        plt.clf()
        img = librosa.display.specshow(logmelspe, y_axis='mel', sr=self.sr, x_axis='time')
        plt.xlabel("时间(s)")
        plt.ylabel("频率(Hz)")
        plt.colorbar(img)
        figfile = BytesIO()
        plt.savefig(figfile, format='png', bbox_inches='tight', pad_inches=0.0)
        fig_str = str(base64.b64encode(figfile.getvalue()), "utf-8")  # 将图片转为base64字符串
        return fig_str

    def loudness_figure(self, y):  # 获取响度图
        S = np.abs(librosa.stft(y))  # 获取幅值
        db = np.mean(librosa.power_to_db(S ** 2), axis=0)  # 响度
        plt.clf()
        plt.plot(np.linspace(0, self.times, len(db)), db)  # 绘图
        plt.xlabel("时间(s)")
        plt.ylabel("响度(dB)")
        figfile = BytesIO()
        plt.savefig(figfile, format='png', bbox_inches='tight', pad_inches=0.0)
        fig_str = str(base64.b64encode(figfile.getvalue()), "utf-8")  # 将图片转为base64字符串
        return fig_str

    def get_xl_figure(self, filepath):  # 获取心率图
        xl = []
        sr, wave_data = wavfile.read(filepath)
        wave_data = self.load_denoise_y(wave_data)
        wave_data = np.abs(wave_data)
        for i in range(1, len(wave_data) // 640):
            xl.append(self.xl_calculate(wave_data[i * 640:(i + 1) * 640], i == 0))
        times = np.linspace(0, self.times, len(xl))
        plt.clf()
        plt.plot(times, xl, 'r-')
        plt.xlabel("时间(s)")
        plt.ylabel("心率(bpm)")
        figfile = BytesIO()
        plt.savefig(figfile, format='png', bbox_inches='tight', pad_inches=0.0)
        fig_str = str(base64.b64encode(figfile.getvalue()), "utf-8")  # 将图片转为base64字符串
        return fig_str

    def xl_calculate(self, data, bFirstData):
        if bFirstData:
            self.s_veD.clear()
            self.s_nBeginBlock = 0
            self.s_nBeginKeeping = 1
            self.s_veJiZhi.clear()
            self.s_nSearchMaxIndex = 0

        for j in range(len(data) // self.nUINT):  # 对每一块求均值，并存入self.s_veD中
            tmp = data[j * self.nUINT:(j + 1) * self.nUINT]  # 取32个，一块
            self.s_veD.append(np.mean(tmp))
        n32_Num = len(self.s_veD)

        # 2s内找极值
        if self.s_nSearchMaxIndex < self.nBlock_2_s - 1 and self.s_nSearchMaxIndex < n32_Num - 1:
            if 0 == self.s_nSearchMaxIndex:
                if self.s_veD[0] > self.s_veD[1]:
                    self.s_veJiZhi.append(0)
                self.s_nSearchMaxIndex = 1

            i = self.s_nSearchMaxIndex
            while i < n32_Num - 1 and i < self.nBlock_2_s - 1:
                if self.s_veD[i] > self.s_veD[i - 1] and self.s_veD[i] > self.s_veD[i + 1]:
                    self.s_veJiZhi.append(i)
                    self.s_nSearchMaxIndex += 2
                else:
                    self.s_nSearchMaxIndex += 1
                i = i + 1

        # 计算心率
        dXinLvValue = 0  # 计算出的心率精确到0.2
        dXinLvAverageMax = 0.0  # 最大的平均值
        dXinLvMinMaxRatio = 0.0  # 最大的平均值处的“最小值/最大值”这个用作一个参数，防止某一处突然的音量暴跳导致的误差

        bNotNeedComputeBegin = (self.s_nBeginKeeping >= 10 and 0 != self.s_nBeginBlock)
        if bNotNeedComputeBegin:  # 根本不需要重新计算起始block，音频基本保证稳定了
            nBegin = self.s_nBeginBlock
            for x in np.arange(60.0, 120.0, 0.2):
                dCaiYang_1 = 60.0 * 16000.0 / (round(x, 1) * self.nUINT)
                dTotalVolume = 0.0
                nTotalNum = 0

                i = 0
                while True:
                    dCaiYang_i = dCaiYang_1 * i
                    nIndex = nBegin + int(dCaiYang_i)
                    if nIndex >= n32_Num:
                        break
                    dTotalVolume += self.s_veD[nIndex]
                    nTotalNum += 1
                    i = i + 1

                dTotalVolume /= nTotalNum

                if dXinLvAverageMax < dTotalVolume:
                    dXinLvAverageMax = dTotalVolume
                    dXinLvValue = x

        else:
            nBeginBlockThis = 0
            for b in range(0, len(self.s_veJiZhi)):
                nBegin = self.s_veJiZhi[b]
                for x in np.arange(60, 120.0, 0.2):
                    dThisMax = 0.0
                    dThisMin = 99999.999

                    dCaiYang_1 = 60.0 * 16000.0 / (round(x, 1) * self.nUINT)
                    dThisAverage = 0.0
                    nThisNum = 0

                    i = 0
                    while True:
                        dCaiYang_i = dCaiYang_1 * i
                        nIndex = nBegin + int(dCaiYang_i)
                        if nIndex >= n32_Num:
                            break
                        dValue = self.s_veD[nIndex]
                        if dThisMax < dValue:
                            dThisMax = dValue
                        if dThisMin > dValue:
                            dThisMin = dValue
                        dThisAverage += dValue
                        nThisNum += 1
                        i += 1

                    dThisAverage /= nThisNum

                    dThisMinMaxRatio = dThisMin / dThisMax
                    bReplace = False
                    if dXinLvAverageMax < 0.1:
                        bReplace = True
                    elif nThisNum > 0:
                        dRatioAverage = dXinLvAverageMax / dThisAverage
                        if dRatioAverage < 0.8:
                            bReplace = True
                        elif dRatioAverage > 1.1:
                            bReplace = False
                        elif dRatioAverage < 1.0:
                            if dThisMinMaxRatio >= 0.3 * dXinLvMinMaxRatio:
                                bReplace = True
                        else:
                            if dThisMinMaxRatio > 4 * dXinLvMinMaxRatio:
                                bReplace = True
                    if bReplace:
                        dXinLvAverageMax = dThisAverage
                        dXinLvValue = x
                        if nBeginBlockThis != nBegin:
                            nBeginBlockThis = nBegin
                        dXinLvMinMaxRatio = dThisMinMaxRatio

            if nBeginBlockThis != self.s_nBeginBlock:
                self.s_nBeginBlock = nBeginBlockThis
                self.s_nBeginKeeping = 1
            else:
                self.s_nBeginKeeping += 1
            # print("第一个波峰:{}".format(self.s_nBeginBlock))

        # dTime = len(self.s_veD)*self.nUINT/16000
        # print("音频时长{:.2f}s,计算心率={:.2f}".format(dTime, dXinLvValue))
        return dXinLvValue
