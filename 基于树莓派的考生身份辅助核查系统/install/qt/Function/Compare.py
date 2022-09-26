import base64
import datetime
import json
import os

import face_recognition
import requests

from Function.Upload import Upload


class Compare:
    def __init__(self, label_status, config):
        self.config = config
        self.label_status = label_status

    def upload_image(self, score):  # 上传图片的函数
        upload = Upload(datetime.datetime.now().strftime(
            "%Y-%m-%d %H:%M:%S"), self.config['local']['path'] + "1.upload.jpg",
                                  self.config['local']['path'] + "2.upload.jpg", score, self.config)
        if not upload.launch():
            print("fail")
        else:
            print("ok")
        os.remove(self.config['local']['path'] + "1.upload.jpg")
        os.remove(self.config['local']['path'] + "2.upload.jpg")

    def compare_face_baidu(self):  # 人脸对比
        access_token = self.get_access_token(
            '7EHtQb4CfhOQqsZd3iYVqBVm', '3yDihiuszBIH6oDoDpTvtPHseemCcvKG')
        score = self.face_compare(
            access_token, os.path.join(self.config['local']['path'], "1.jpg"), self.config['local']['path'] + "2.jpg")
        if score >= 80:
            print(score)
            self.label_status.setText(u"对比通过 相似度{:.2f}%".format(score))
        else:
            self.label_status.setText(u"对比不通过 相似度{:.2f}%".format(score))
        os.remove(self.config['local']['path'] + "1.jpg")
        os.remove(self.config['local']['path'] + "2.jpg")
        self.upload_image(score)

    def submit(self, url, submit_data):
        response = requests.post(url, data=submit_data)
        req_con = response.content.decode('utf-8')
        req_dict = json.JSONDecoder().decode(req_con)
        return req_dict

    def get_access_token(self, client_id, client_secret):
        url = "https://aip.baidubce.com/oauth/2.0/token"
        data = {"grant_type": "client_credentials",
                "client_id": client_id, "client_secret": client_secret}
        response = self.submit(url, data)
        access_token = response['access_token']
        return access_token

    def face_compare(self, access_token, locate1, locate2):
        url = "https://aip.baidubce.com/rest/2.0/face/v3/match" + \
              "?access_token=" + access_token
        file1 = open(locate1, 'rb')
        file2 = open(locate2, 'rb')
        image1 = base64.b64encode(file1.read())
        image2 = base64.b64encode(file2.read())
        data = json.dumps(
            [{"image": str(image1, 'utf-8'), "image_type": "BASE64", "face_type": "CERT", "quality_control": "NONE"},
             {"image": str(image2, 'utf-8'), "image_type": "BASE64", "face_type": "LIVE", "quality_control": "NORMAL"}])
        response = self.submit(url, data)
        print(response)
        if response['error_code'] != 0:
            return 0
        score = response['result']['score']
        return score

    def compare_face_recognition(self, locate1, locate2):
        first_image = face_recognition.load_image_file(locate1)
        second_image = face_recognition.load_image_file(locate2)
        first_encoding = face_recognition.face_encodings(first_image)
        second_encoding = face_recognition.face_encodings(second_image)
        if len(first_encoding) == 0:
            return 2
        if len(second_encoding) == 0:
            return 3
        results = face_recognition.compare_faces(
            [first_encoding][0], second_encoding[0])
        if results != "True":
            results = face_recognition.face_distance(
                [first_encoding][0], second_encoding[0])
        return results

    def local_compare(self):
        score = self.compare_face_recognition(
            self.config['local']['path'] + "1.jpg", self.config['local']['path'] + "2.jpg")
        if type(score) == int:
            if score == 3:
                self.label_status.setText(u"未采集到证件人脸")
            else:
                self.label_status.setText(u"未采集到人像人脸")
        else:
            if score[0] >= 0.60:
                self.label_status.setText(u"对比通过 相似度{:.2%}".format(score[0]))
            else:
                self.label_status.setText(u"对比不通过 相似度{:.2%}".format(score[0]))
            self.upload_image(score[0] * 100)
        os.remove(self.config['local']['path'] + "1.jpg")
        os.remove(self.config['local']['path'] + "2.jpg")
