import paddle
import paddle.nn as nn
from paddlenlp.datasets import MapDataset
from paddlenlp.embeddings import TokenEmbedding
from paddlenlp.metrics import ChunkEvaluator
from paddlenlp.layers import LinearChainCrf, ViterbiDecoder, LinearChainCrfLoss
from data_pre_processing import read,label_vocab


class BiGRUWithCRF(nn.Layer):  # 构建BiGRU+CRF神经网络模型
    """
      emb_size:词向量维度
      hidden_size:隐藏层维度
      label_num:标签数量
      数据流向：
        数据->Embedding层（词向量层）->GRU层->CRF层
      此处使用了预训练的词向量模型将文字转化为词向量
    """

    def __init__(self, emb_size, hidden_size, label_num):
        super(BiGRUWithCRF, self).__init__()
        self.word_emb = TokenEmbedding(embedding_name="w2v.baidu_encyclopedia.target.word-word.dim300",
                                       # 加载由《百度百科》数据训练的词向量
                                       extended_vocab_path='./data/words.char',  # 扩展词语
                                       unknown_token='OOV'  # 未在此表中找到的字符以OOV表示
                                       )  # 定义用于加载预训练的词向量模型，将词或字转化为词向量
        self.gru = nn.GRU(emb_size, hidden_size, num_layers=2,
                          direction='bidirectional')  # 定义GRU层
        self.fc = nn.Linear(hidden_size * 2, label_num + 2)  # BOS EOS
        self.crf = LinearChainCrf(label_num)  # CRF层
        self.decoder = ViterbiDecoder(self.crf.transitions)  # 解码

    def forward(self, x, lens):  # 定义数据流向
        embs = self.word_emb(x)  # 将输入的id转化为词向量
        output, _ = self.gru(embs)  # 经过GRU层
        output = self.fc(output)
        _, pred = self.decoder(output, lens)
        return output, lens, pred  # return 句向量,句子长度,预测的标签值


class Ner:  # 创建一个类，用于对模型的二次封装，方便主函数调用
    def __init__(self, loader):
        # 接受训练集、开发集、和测试集数据，分别用于模型训练、参数调优和模型测试
        self.train_loader, self.dev_loader, self.test_loader = loader
        self.network = BiGRUWithCRF(
            300, 300, len(label_vocab))  # 实例化BiGRU+CRF模型
        self.model = paddle.Model(self.network)  # 创建模型
        self.optimizer()  # 创建优化器

    def optimizer(self):  # 定义模型优化策略
        optimizer = paddle.optimizer.Adam(
            learning_rate=0.001, parameters=self.model.parameters())
        crf_loss = LinearChainCrfLoss(self.network.crf)
        chunk_evaluator = ChunkEvaluator(
            label_list=label_vocab.keys(), suffix=True)
        self.model.prepare(optimizer, crf_loss, chunk_evaluator)

    def fit(self):  # 模型训练
        self.model.fit(train_data=self.train_loader, eval_data=self.dev_loader, epochs=1, save_dir='./Model',
                       log_freq=1)

    def evaluate(self):  # 模型评估
        self.model.evaluate(eval_data=self.test_loader, log_freq=1)

    def test(self):  # 模型测试
        test_ds = MapDataset(read("./data/test.char"))  # 读取测试集数据，用于预测数据的解码
        outputs, lens, decodes = self.model.predict(
            test_data=self.test_loader)  # 利用模型对测试集进行测试
        preds = self.parse_decodes(
            test_ds, decodes, lens, label_vocab)  # 解码测试结果，将测试结果以自然语言显示出来
        with open("./test_set_result.txt", "w", encoding="utf8") as f:
            for i in preds:
                f.write(i + "\n")
        return preds  # 返回预测结果

    def parse_decodes(self, ds, decodes, lens, l_v): #用于将预测结果转化为文字
        decodes = [x for batch in decodes for x in batch]
        lens = [x for batch in lens for x in batch]
        id_label = dict(zip(label_vocab.values(), l_v.keys()))

        outputs = []
        for idx, end in enumerate(lens):
            sent = ds.data[idx][0][:end]
            tags = [id_label[x] for x in decodes[idx][:end]]
            sent_out = []
            tags_out = []
            words = ""
            for s, t in zip(sent, tags):
                if t.startswith('B-') or t == 'O':
                    if len(words):
                        sent_out.append(words)
                    tags_out.append(t if t == 'O' else t.split('-')[1])
                    words = s
                else:
                    words += s
            if len(sent_out) < len(tags_out):
                sent_out.append(words)
            outputs.append(''.join(
                [str((s, t)) for s, t in zip(sent_out, tags_out)]))
        return outputs
