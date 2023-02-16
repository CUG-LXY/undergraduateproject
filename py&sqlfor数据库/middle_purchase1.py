#!/usr/bin/python3
# -*- coding: utf-8 -*-


import sys

from front_purchase1 import Ui_purchase

#sys.path.append('D:\\managerment\\front_ui')

from PyQt5.QtWidgets import QApplication, QMainWindow
import middle_purchase2 as purchase2


class purchase(QMainWindow, Ui_purchase):
    def __init__(self, parent=None):
        super(purchase, self).__init__(parent)
        self.setupUi(self)
        self.check_suply.clicked.connect(lambda: self.response(1))
        self.buy.clicked.connect(lambda: self.response(2))
        self.conf_list.clicked.connect(lambda: self.response(3))
        self.exit.clicked.connect(lambda: self.close())

    def response(self,event):
        self.win = None
        if event==1:
            self.win = purchase2.sup_check_suply()        
        elif event==2:
            self.win = purchase2.sup_buy()
        elif event==3:
            self.win = purchase2.sup_conf_list()
        self.win.show()

'''if __name__ == "__main__":
    app = QApplication(sys.argv)
    main = purchase()
    main.show()
    sys.exit(app.exec_())'''