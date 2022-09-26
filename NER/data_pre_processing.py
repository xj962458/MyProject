import paddle
from paddlenlp.data import Stack, Tuple, Pad
from paddlenlp.datasets import MapDataset


def read(path):  # 从文件读取数据，返回一个包含数据的列表
    """
    原始数据格式:
        我 O
        是 O
        张 B-NAME
        三 E_NAME
        。
    返回数据格式: [[['我','是','张','三','。'],['O','O','B-NAME','E-NAME','O'],[...],...]
    """
    with open(path, "r", encoding="utf8") as f:  # 以utf-8编码打开文件
        lines = f.readlines()  # 读取所有的行
    data = []  # 用于存储所有数据
    words, labels = [], []  # 用于临时存储字符和标签
    for line in lines:  # 遍历所有的行
        if line == "\n":  # "\n"是每一句话的分割
            data.append([words, labels])  # 将读取的句子和标签添加进data
            words, labels = [], []  # 清空
        else:
            w, l = line.strip("\n").split(" ")  # 去除换行符后使用空格将字符和标签分割
            words.append(w)  # 添加到词中
            labels.append(l)  # 添加到标签中
    return data  # 返回读取的数据


def load_dataset(datafiles):  # 读取数据集，封装成MapDataset
    """
    :param datafiles:["train.txt","dev.txt","test.txt",...]
    :return: 调用read函数读取数据后，获取包含数据的列表，将其封装成MapDataset格式以返回
    """
    return [MapDataset(read(datafile)) for datafile in datafiles]  # 编译要读取的目录路径，使用read函数读取后包装成MapDataset类型的数据


def convert_tokens_to_ids(tokens, vocab, oov_token=None):  # 将文字转化为id
    token_ids = []  # 用于存储要转化的ip
    oov_id = vocab.get(oov_token) if oov_token else None  # 获取'OOV'的id
    for token in tokens:  # 遍历词
        token_id = vocab.get(token, oov_id)  # 转化，若是非OOV返回对于的id，否则返回OOV的id
        token_ids.append(token_id)  # 将转化的结果保存到token_ids中
    return token_ids  # 返回转化后的ip


def convert_example(example):  # 应用样本转换
    """
    :param example: [['我','是','张','三','。'],['O','O','B-NAME','E-NAME','O']]
    :return: [['34','23','433','22','1'],['2','2','5','6','2']]
    """
    tokens, labels = example  # 分离句子和标签
    token_ids = convert_tokens_to_ids(
        tokens, word_vocab, 'OOV')  # 将句子中的字/词转化为id
    label_ids = convert_tokens_to_ids(labels, label_vocab, 'O')  # 将标签转化为id
    return token_ids, len(token_ids), label_ids  # 返回转化后句子的id,以及句子的长度和转化后的标签id


def load_dict(dict_path):  # 加载词典
    """
    return: {"我":0,"是":1,"张":2,"三":3,"。":4,...}
         或 {"O":0,"O":1,"B-NAME":2,"E-NAME":3,"O":4,...}
    """
    vocab, i = {}, 0
    for line in open(dict_path, 'r', encoding='utf-8'):
        key = line.strip('\n')  # 去除换行符
        vocab[key] = i
        i += 1
    return vocab  # 返回字典


def build_dataloader(data):  # 构造dataloader
    train, dev, test = data  # 接受数据
    batchify_fn = lambda samples, fn=Tuple(Pad(dtype="int64", axis=0, pad_val=word_vocab.get('OOV')),  # token_ids
                                           Stack(dtype="int64"),  # seq_len
                                           # label_ids
                                           Pad(dtype="int64", axis=0,
                                               pad_val=label_vocab.get('O'))
                                           ): fn(samples)

    train_l = paddle.io.DataLoader(dataset=train, batch_size=32, shuffle=True, drop_last=True, return_list=True,
                                   collate_fn=batchify_fn)
    dev_l = paddle.io.DataLoader(
        dataset=dev, batch_size=32, drop_last=True, return_list=True, collate_fn=batchify_fn)
    test_l = paddle.io.DataLoader(
        dataset=test, batch_size=32, drop_last=True, return_list=True, collate_fn=batchify_fn)
    return train_l, dev_l, test_l  # 返回训练集、开发集和测试集


def get_dataloader():
    ds = load_dataset(datafiles=('./data/train.char',
                      './data/dev.char', './data/test.char'))  # 获取构造的MapDataset数据
    ds = [d.map(convert_example) for d in ds]  # 将字符和标签转化为id
    return build_dataloader(ds)  # 返回构造的DataLoader


label_vocab = load_dict('./data/labels.char')  # 标签词表
word_vocab = load_dict('./data/words.char')  # 词表
