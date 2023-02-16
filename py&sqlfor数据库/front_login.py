# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '.\save.ui'
#
# Created by: PyQt5 UI code generator 5.13.0
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Admin(object):
    def setupUi(self, Admin):
        Admin.setObjectName("Admin")
        Admin.resize(628, 394)
        '''icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap("D:/managerment/image/view3.jpg"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        Admin.setWindowIcon(icon)'''
        self.frame_2 = QtWidgets.QFrame(Admin)
        self.frame_2.setGeometry(QtCore.QRect(0, 0, 681, 401))
        self.frame_2.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_2.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_2.setObjectName("frame_2")
        self.label_3 = QtWidgets.QLabel(self.frame_2)
        self.label_3.setGeometry(QtCore.QRect(0, 0, 628, 394))
        #self.label_3.setGeometry(QtCore.QRect(-50, 0, 231, 401))
        #self.label_3.setText("")
        self.label_3.setPixmap(QtGui.QPixmap("D:/managerment/image/view5.jpg"))
        self.label_3.setObjectName("label_3")
        self.label_5 = QtWidgets.QLabel(self.frame_2)
        self.label_5.setGeometry(QtCore.QRect(180, 40, 250, 61))
        self.label_5.setObjectName("label_5")
        '''self.graphicsView = QtWidgets.QGraphicsView(self.frame_2)
        self.graphicsView.setGeometry(QtCore.QRect(180, 0, 628, 394))
        self.graphicsView.setMinimumSize(QtCore.QSize(628, 394))
        self.graphicsView.setMaximumSize(QtCore.QSize(628, 394))
        self.graphicsView.setAutoFillBackground(True)
        self.graphicsView.setObjectName("graphicsView")'''
        self.label = QtWidgets.QLabel(self.frame_2)
        self.label.setGeometry(QtCore.QRect(180, 150, 91, 41))
        self.label.setObjectName("label")
        self.label_2 = QtWidgets.QLabel(self.frame_2)
        self.label_2.setGeometry(QtCore.QRect(180, 220, 81, 31))
        self.label_2.setObjectName("label_2")
        self.amountEdit1 = QtWidgets.QLineEdit(self.frame_2)
        self.amountEdit1.setGeometry(QtCore.QRect(260, 150, 191, 31))
        self.amountEdit1.setObjectName("amountEdit")
        self.amountEdit = QtWidgets.QLineEdit(self.frame_2)
        self.amountEdit.setGeometry(QtCore.QRect(260, 220, 191, 31))
        self.amountEdit.setObjectName("amountEdit")
        self.amountEdit.setEchoMode(QtWidgets.QLineEdit.Password)
        self.ConfirmButton = QtWidgets.QPushButton(self.frame_2)
        self.ConfirmButton.setGeometry(QtCore.QRect(240, 300, 61, 31))
        self.ConfirmButton.setObjectName("ConfirmButton")
        self.CancelButton = QtWidgets.QPushButton(self.frame_2)
        self.CancelButton.setGeometry(QtCore.QRect(340, 300, 61, 31))
        self.CancelButton.setObjectName("CancelButton")
        '''self.retEdit1 = QtWidgets.QLabel(self.frame_2)
        self.retEdit1.setGeometry(QtCore.QRect(360, 50, 151, 21))
        self.retEdit1.setText("")
        self.retEdit1.setObjectName("retEdit")'''
        self.retEdit = QtWidgets.QLabel(self.frame_2)
        self.retEdit.setGeometry(QtCore.QRect(360, 110, 151, 21))
        self.retEdit.setText("")
        self.retEdit.setObjectName("retEdit")
        self.ID_num = QtWidgets.QLabel(self.frame_2)
        self.ID_num.setGeometry(QtCore.QRect(360, 160, 181, 21))
        font = QtGui.QFont()
        font.setFamily("SimSun-ExtB")
        font.setPointSize(14)
        self.ID_num.setFont(font)
        self.ID_num.setTextFormat(QtCore.Qt.RichText)
        self.ID_num.setObjectName("ID_num")
        self.label_3.raise_()
        #self.graphicsView.raise_()
        self.label_5.raise_()
        self.label.raise_()
        self.label_2.raise_()
        self.amountEdit1.raise_()
        self.amountEdit.raise_()
        self.ConfirmButton.raise_()
        self.CancelButton.raise_()
        self.retEdit.raise_()
        self.ID_num.raise_()

        self.retranslateUi(Admin)
        QtCore.QMetaObject.connectSlotsByName(Admin)
        Admin.setTabOrder(self.amountEdit, self.ConfirmButton)
        Admin.setTabOrder(self.ConfirmButton, self.CancelButton)
        #Admin.setTabOrder(self.CancelButton, self.graphicsView)

    def retranslateUi(self, Admin):
        _translate = QtCore.QCoreApplication.translate
        Admin.setWindowTitle(_translate("Admin", "登录"))
        self.label_5.setText(_translate("Admin", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt;\">企业工程管理系统</span></p></body></html>"))
        self.label.setText(_translate("Admin", "<html><head/><body><p><span style=\" font-size:14pt;\">账号</span></p></body></html>"))
        self.label_2.setText(_translate("Admin", "<html><head/><body><p><span style=\" font-size:14pt;\">密码</span></p></body></html>"))
        self.ConfirmButton.setText(_translate("Admin", "登录"))
        self.CancelButton.setText(_translate("Admin", "退出"))
        self.ID_num.setText(_translate("Admin", "<html><head/><body><p><br/></p></body></html>"))
