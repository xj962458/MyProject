import sys
import paddle
import paddle.nn.functional as F
from GUI.ui import Ui_MainWindow
from PySide6.QtGui import QPixmap
from PySide6.QtCore import QItemSelectionModel, Qt
from PySide6.QtSql import QSqlDatabase, QSqlTableModel
from PySide6.QtWidgets import (QApplication, QMainWindow, QHeaderView)
from paddlenlp.transformers import AutoModelForSequenceClassification, AutoTokenizer


class MyModel:  # 用于加载模型和执行预测任务
    def __init__(self, model_name, pdparams_path):  # 指定模型名称和模型参数路径
        self.model = AutoModelForSequenceClassification.from_pretrained(
            model_name, num_classes=2)  # 加载模型
        model_pdparams = paddle.load(pdparams_path)  # 加载训练的模型参数
        self.model.load_dict(model_pdparams)  # 将加载的模型和模型参数合二为一
        self.tokenizer = AutoTokenizer.from_pretrained(model_name)  # 加载分词器
        self.label_map = {0: '差评', 1: '好评'}  # 评论映射。模型输出的结果为0或1，将其映射到好、差评中

    def predict(self, text):  # 定义预测函数
        input_ids, token_type_ids = self.tokenizer(
            text, max_seq_len=256).values()  # 调用分词器，将输入的文本分词并转化为id,即word2id
        self.model.eval()  # 进入模型评估模式
        with paddle.no_grad():  # 自动梯度计算
            input_ids = paddle.to_tensor([input_ids])  # 将word2id转化为张量
            token_type_ids = paddle.to_tensor(
                [token_type_ids])  # 将token_type_ids转化为张量
            logits = self.model(input_ids=input_ids,
                                token_type_ids=token_type_ids)  # 调用模型，将数据输入到模型中，得到预测结果
            # 模型输出的是属于每一类的概率，利用softmax函数去概率的大的
            probs = F.softmax(logits, axis=-1)
            preds = paddle.argmax(probs, axis=1).numpy()[
                0]  # 对结果进一步处理，得到类别属于0，还是1
            return self.label_map[preds]  # 返回解析后的结果，好评/差评


class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setupUi(self)  # 加载图形界面
        self.init_ui()  # 初始化图形界面上现实的数据
        self.slot()  # 设置槽映射
        self.yp_model = MyModel(
            "ernie-3.0-medium-zh", r"./Model/model_state.pdparams")

    def init_ui(self):  # 初始化UI上显示的内容
        self.load_reviews()  # 从数据库加载评论
        self.plainTextEdit.setPlainText(
            "虽然无厘头，但是搞笑+感动，袋鼠演技加分，喜欢沈腾马丽的组合，贱萌贱萌的，值得一看。")
        self.label_4.setPixmap(QPixmap("./data/pictures/好评.png"))
        self.label_4.setScaledContents(True)
        self.label_5.setText("好评")

    def load_reviews(self):
        self.db = QSqlDatabase.addDatabase(
            'QSQLITE')  # 初始化一个QtSQL对象，使用SQLite数据库
        self.db.setDatabaseName(
            "./data/databases/reviews.sqlite3")  # 指定要连接到数据库文件
        self.db.open()  # 打开数据库
        self.model = QSqlTableModel()  # 创建一个SQL模型对象
        self.model.setTable('reviews')  # 设置要查询的表
        self.model.select()  # 选择所有数据
        self.model.setHeaderData(0, Qt.Horizontal, "独行月球影评")
        self.selModel = QItemSelectionModel(self.model)  # 选择模型
        self.tableView.setModel(self.model)  # 将模型对象传入tableView控件中
        self.tableView.horizontalHeader().setSectionResizeMode(
            QHeaderView.Stretch)  # 设置列自适应宽度
        self.tableView.setSelectionModel(self.selModel)  # 设置tableView选择的行
        self.db.close()  # 关闭数据库

    def slot(self):  # 设置信号与槽的绑定
        self.selModel.currentRowChanged.connect(
            self.do_currentRowChanged)  # 选择行变化时
        self.pushButton.clicked.connect(self.start_analyze)

    def do_currentRowChanged(self, current, previous):  # 处理选中tableView某一行的操作
        curRec = self.model.record(current.row())  # 获取当前记录,QSqlRecord类型
        self.plainTextEdit.setPlainText(
            curRec.value("review"))  # 将文本输入框中的文本设置为当前选中行的文本
        self.start_analyze()

    def start_analyze(self):  # 进行分析
        comment_context = self.plainTextEdit.toPlainText()  # 从输入框分析的文本
        if comment_context:  # 如果获取的文本内容不为空
            result = self.yp_model.predict(comment_context)
            self.label_4.setPixmap(
                QPixmap(f"./data/pictures/{result}.png"))  # 将评论的图标设置为相应的图标
            self.label_5.setText(result)  # 设置显示好评、差评


if __name__ == "__main__":
    app = QApplication(sys.argv)  # 开始一个QT应用
    app.setStyle('Fusion')  # 设置界面为Fusion风格
    win = MainWindow()  # 创建主窗口类
    win.show()  # 显示窗口
    sys.exit(app.exec())  # 进入消息循环
