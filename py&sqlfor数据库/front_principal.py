# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'principal.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Prin(object):
    def setupUi(self, Prin):
        Prin.setObjectName("Prin")
        Prin.resize(638, 424)
        self.listView = QtWidgets.QListView(Prin)
        self.listView.setGeometry(QtCore.QRect(-20, 0, 831, 511))
        self.listView.setStyleSheet("background-image: url(\"D:/managerment/image/view5.jpg\")")
        self.listView.setObjectName("listView")
        self.label = QtWidgets.QLabel(Prin)
        self.label.setGeometry(QtCore.QRect(250, 40, 71, 21))
        self.label.setObjectName("label")
        self.check_person = QtWidgets.QPushButton(Prin)
        self.check_person.setGeometry(QtCore.QRect(230, 80, 121, 31))
        self.check_person.setObjectName("check_person")
        self.check_project = QtWidgets.QPushButton(Prin)
        self.check_project.setGeometry(QtCore.QRect(230, 130, 121, 31))
        self.check_project.setObjectName("check_project")
        self.check_pace = QtWidgets.QPushButton(Prin)
        self.check_pace.setGeometry(QtCore.QRect(230, 180, 121, 31))
        self.check_pace.setObjectName("check_pace")
        self.check_component = QtWidgets.QPushButton(Prin)
        self.check_component.setGeometry(QtCore.QRect(230, 230, 121, 31))
        self.check_component.setObjectName("check_component")
        self.check_suppliers = QtWidgets.QPushButton(Prin)
        self.check_suppliers.setGeometry(QtCore.QRect(230, 280, 121, 31))
        self.check_suppliers.setObjectName("check_suppliers")
        self.check_trade = QtWidgets.QPushButton(Prin)
        self.check_trade.setGeometry(QtCore.QRect(230, 330, 121, 31))
        self.check_trade.setObjectName("check_trade")
        self.exit = QtWidgets.QPushButton(Prin)
        self.exit.setGeometry(QtCore.QRect(230, 380, 121, 31))
        self.exit.setObjectName("exit")

        self.retranslateUi(Prin)
        QtCore.QMetaObject.connectSlotsByName(Prin)

    def retranslateUi(self, Prin):
        _translate = QtCore.QCoreApplication.translate
        Prin.setWindowTitle(_translate("Prin", "Prin"))
        self.label.setText(_translate("Prin", "项目负责人"))
        self.check_person.setText(_translate("Prin", "查看员工信息"))
        self.check_project.setText(_translate("Prin", "查看工程信息"))
        self.check_pace.setText(_translate("Prin", "查看工程进度"))
        self.check_component.setText(_translate("Prin", "查看零件情况"))
        self.check_suppliers.setText(_translate("Prin", "查看供应商信息"))
        self.check_trade.setText(_translate("Prin", "查看交易信息"))
        self.exit.setText(_translate("Prin", "退出"))
