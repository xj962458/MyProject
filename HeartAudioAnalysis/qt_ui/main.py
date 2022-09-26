from PySide6.QtWidgets import QApplication

from MyApp import MyApp

if __name__ == "__main__":
    app = QApplication()
    win = MyApp()
    win.show()
    app.exec()
