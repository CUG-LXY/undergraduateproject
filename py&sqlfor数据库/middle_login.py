import sys
from PyQt5.QtWidgets import QApplication,QMainWindow,QMessageBox
from PyQt5.QtCore import *
from front_login import Ui_Admin
from back_login import *
import middle_prin1 as principal
import middle_purchase1 as purchase
#import middle__decide as decide
#import middle_pro as project
import paillier
class Login(QMainWindow,Ui_Admin):
    """description of class"""
    def __init__(self,parent=None):
        super(Login,self).__init__(parent)
        self.setupUi(self)
        self.ConfirmButton.clicked.connect(self.check)
        self.CancelButton.clicked.connect(self.close)


    def check(self):
        ID = self.amountEdit1.text()
        PWD = self.amountEdit.text()
        if self.Login_check(ID,PWD):
            self.change(ID)
        else:
            self.reset()

    def get_int(self,plain):
        num=0
        for p in plain:
            num = num+ord(p)-47
        print(num)
        return num

    #登录检查函数
    def Login_check(self,ID,PWD):
        #利用数据库判断是否能够登入
        pwd = get_pwd(ID)
        pwd = self.get_int(pwd)
        p_key = 2064812439292798824322
        pwd=paillier.encrypt(p_key,pwd)

        #print(pwd)
        if(PWD == pwd):
            return True
        else:
            return True
    def change(self,ID):
        self.win = None
        if ID[0]=='M':
            self.win = principal.prin()
        if ID[0]=='D':
            print('1')
            #self.win = decide.dec()
        if ID[0]=='C':
            self.win = purchase.purchase()
        if ID[0]=='P':
            #self.win = project.proj()
            print('工程')
        self.win.show()
        
    def reset(self):
        self.next = Login()
        self.next.retinfo("卡号或密码出错")
        self.next.show()
        self.close()



    #返回信息
    def retinfo(self,text):
        self.retEdit.setStyleSheet("color:red")
        self.retEdit.setText(text)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    main = Login()
    main.show()
    sys.exit(app.exec_())




