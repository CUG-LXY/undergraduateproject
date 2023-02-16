#!/usr/bin/python3
# -*- coding: utf-8 -*-



import sys
from front_principal import Ui_Prin



from PyQt5.QtWidgets import QApplication, QMainWindow, QMessageBox
import middle_prin2 as prin2


class prin(QMainWindow, Ui_Prin):
    def __init__(self, parent=None):
        super(prin, self).__init__(parent)
        self.setupUi(self)
        self.check_person.clicked.connect(lambda: self.response(1))
        self.check_project.clicked.connect(lambda: self.response(2))
        self.check_pace.clicked.connect(lambda: self.response(3))
        self.check_component.clicked.connect(lambda: self.response(4))
        self.check_suppliers.clicked.connect(lambda: self.response(5))
        self.check_trade.clicked.connect(lambda: self.response(6))
        self.exit.clicked.connect(lambda: self.close())
    def response(self,event):
        self.win = None
        if event==1:
            self.win = prin2.prin_check_person()           
        elif event==2:
            self.win = prin2.prin_check_project()
        elif event==3:
            self.win = prin2.prin_check_pace()
        elif event==4:
            self.win = prin2.prin_check_component()
        elif event==5:
            self.win = prin2.prin_check_supplier()
        elif event==6:
            self.win = prin2.prin_check_trade()
        self.win.show()

'''if __name__ == "__main__":
    app = QApplication(sys.argv)
    main = prin()
    main.show()
    sys.exit(app.exec_())'''