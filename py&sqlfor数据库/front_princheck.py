# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'prinCheck.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_prinCheck(object):
    def setupUi(self, prinCheck):
        prinCheck.setObjectName("prinCheck")
        prinCheck.resize(638, 424)
        self.listView = QtWidgets.QListView(prinCheck)
        self.listView.setGeometry(QtCore.QRect(-20, 0, 831, 511))
        self.listView.setStyleSheet("background-image: url(\"D:/managerment/image/view5.jpg\")")
        self.listView.setObjectName("listView")
        self.label = QtWidgets.QLabel(prinCheck)
        self.label.setGeometry(QtCore.QRect(280, 40, 72, 15))
        self.label.setObjectName("label")
        self.exit = QtWidgets.QPushButton(prinCheck)
        self.exit.setGeometry(QtCore.QRect(250, 370, 93, 28))
        self.exit.setObjectName("exit")
        self.tableWidget = QtWidgets.QTableWidget(prinCheck)
        self.tableWidget.setGeometry(QtCore.QRect(70, 80, 481, 251))
        self.tableWidget.setObjectName("tableWidget")
        self.tableWidget.setColumnCount(0)
        self.tableWidget.setRowCount(0)

        self.retranslateUi(prinCheck)
        QtCore.QMetaObject.connectSlotsByName(prinCheck)

    def retranslateUi(self, prinCheck):
        _translate = QtCore.QCoreApplication.translate
        prinCheck.setWindowTitle(_translate("prinCheck", "prinCheck"))
        self.label.setText(_translate("prinCheck", "查询结果"))
        self.exit.setText(_translate("prinCheck", "退出"))
