from tensorflow import keras
import pandas as pd
import numpy as np
import librosa
import os
import glob

# 建立类别标签，不同类别对应不同的数字。
label_dict = {0: "Dog bark", 1: "Rain", 2: "Sea waves", 3: "Baby cry", 4: "Clock tick",
              5: "Person sneeze", 6: "Helicopter", 7: "Chainsaw", 8: "Rooster", 9: "Fire crackling"}

with open("test.txt", "r") as f:
    f.writelines()

class model_predict:  # 建立一个模型预测类
    def __init__(self) -> None:
        self.model = keras.models.load_model("./Model")  # 加载模型
        self.data = pd.read_csv("./dataset.csv")  # 加载数据集

    def start_predict(self, filepath):  # 使用模型进行结果预测
        y, sr = librosa.load(filepath, sr=44100,
                             res_type='kaiser_fast')  # 读取音频数据

        # 统一音频时长为5s，多的裁剪、少的随机填充
        input_len = sr * 5  # 5秒长度
        if len(y) > input_len:  # 音频过长，裁剪
            max_offset = len(y) - input_len
            offset = np.random.randint(max_offset)
            y = y[offset: (input_len + offset)]
        elif input_len > len(y):  # 音频过短，填充
            max_offset = input_len - len(y)
            offset = np.random.randint(max_offset)
            y = np.pad(y, (offset, input_len - len(y) - offset), "constant")

        mels = np.mean(librosa.feature.melspectrogram(  # 计算梅尔频谱(mel spectrogram), 并把它作为特征
            y=y, sr=sr).T, axis=0)
        pred = self.model.predict(mels.reshape(-1, 16, 8, 1))  # 使用模型进行预测
        result = np.argmax(pred, axis=1)  # 将结果转换为正常编码
        return result  # 将预测结果返回

    def random_sample_test(self, n):  # 随机选择n个样本就行测试
        data_test = self.data.sample(n)  # 从数据集中随机选择n个样本
        correct = 0  # 用于统计正确的结果
        for i in range(len(data_test)):  # 遍历用于测试的样本
            result = self.start_predict(data_test.iloc[i]['文件路径'])  # 使用模型进行预测
            true_reslut = data_test.iloc[i]['类别']  # 真实结果
            print("实际类型{},预测类型{}".format(
                label_dict[true_reslut], label_dict[result[0]]))
            if true_reslut == result:  # 判断预测结果和实际结果是否相同
                correct = correct+1  # 正确结果++
        print("从数据集中随机选取{}个样本进行测试，得到的正确率为{:.2%}".format(n, correct/n))  # 打印准确率

    def user_defined_predict(self, filepath):  # 供用户自定义文件预测
        if os.path.isdir(filepath):  # 如果用户给的是包含多个音频文件的文件夹
            result = {"音频数据": [], "预测结果": []}  # 创建一个字典，用于包含结果
            for i in glob.glob(os.path.join(filepath, "*.ogg")):  # 查找用户所给路径下的所有ogg格式的文件
                result['音频数据'].append(i)  # 将音频文件路径添加result字典中
                # 将对音频文件的预测结果添加到result字典中
                result['预测结果'].append(label_dict[self.start_predict(i)[0]])
            print(pd.DataFrame(data=result))  # 打印结果的集合
        else:  # 如果用户给的是一个音频文件
            # 直接将预测结果返回
            print("该音频文件属于{}".format(
                label_dict[self.start_predict(filepath)[0]]))


if __name__ == "__main__":  # 主函数
    filepath = r"D:\MyFile\xj\Desktop\实验室\Code\AudioClassify\AudioClassify\data\001 - Dog bark"  # 用户自定义数据位置
    model = model_predict()  # 创建对象
    model.random_sample_test(39)  # 选取39个样本进行随机测试
    model.user_defined_predict(filepath)  # 指定声音文件判断类别
