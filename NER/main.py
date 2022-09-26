from build_model import Ner
from data_pre_processing import get_dataloader

if __name__ == "__main__":
    train_loader, dev_loader, test_loader = get_dataloader()  # 加载数据
    ner_model = Ner([train_loader, dev_loader, test_loader])  # 加载NER模型
    ner_model.fit()  # 开始训练
    ner_model.evaluate()  # 利用测试集对模型进行评估
    pred_result = ner_model.test()  # 对模型进行测试
    for i in pred_result[:10]:
        print(i)  # 打印前十个预测结果
