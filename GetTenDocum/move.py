# -*- coding: utf-8 -*-
import os
import shutil

files = []


def CopyFile(filepath, newPath):
    for file in os.listdir(filepath):
        newDir = os.path.join(filepath, file)
        if os.path.isfile(newDir):  # 如果是文件
            if file not in files:
                newFile = os.path.join(newPath, file)
                shutil.copyfile(newDir, newFile)
                files.append(file)
        else:
            CopyFile(newDir, newPath)  # 如果不是文件，递归这个文件夹的路径


if __name__ == "__main__":
    oldpath, newpath = r"./AllFile/腾讯文档模板", r"./AllFile/腾讯文档模板/Document"
    os.makedirs(newpath)
    CopyFile(oldpath, newpath)
