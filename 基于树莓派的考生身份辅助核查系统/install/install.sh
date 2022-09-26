#换源并更新源和软件
rm -rf /etc/apt/sources.list
mv ./sources.list /etc/apt/sources.list
rm -rf /etc/apt/sources.list.d/raspi.list
mv ./raspi.list /etc/apt/sources.list.d/raspi.list
apt update -y
apt upgrade -y
apt autoremove -y
#安装和配置pip3
apt install python3-pip -y
pip3 install -i https://pypi.tuna.tsinghua.edu.cn/simple pip -U
pip3 config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple
update-alternatives --install /usr/bin/python python /usr/bin/python3 150

#安装opencv和opencv-contrib-python的依赖
apt-get install libhdf5-dev -y
apt-get install libatlas-base-dev -y
apt-get install libjasper-dev -y
apt-get install libqt4-test -y
apt-get install libqtgui4 -y
apt-get install libhdf5-serial-dev -y
apt install libqtgui4 -y
apt install libqt4-test -y

#安装opencv和opencv-contrib-python
pip3 install opencv-python
pip3 install -i http://pypi.douban.com/simple/ opencv-contrib-python

# 安装PyQt5
apt install -y python3-pyqt5

#安装其他python库
pip3 install pymysql
pip3 install paramiko
pip3 install dlib
pip3 install face_recognition
pip3 install requests

#拷贝项目文件
cp -r ./qt /home/pi/Desktop/qt
chmod -R 777 /home/pi/Desktop/qt
#创建开机自启文件
mkdir /home/pi/.config/autostart
mv ./qt.desktop /home/pi/.config/autostart/qt.desktop

#安装屏幕驱动
git clone https://github.com/waveshare/LCD-show.git
cd LCD-show/
./LCD35B-show 180