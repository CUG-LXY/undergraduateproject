# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'decide.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_project(object):
    def setupUi(self, project):
        project.setObjectName("project")
        project.resize(638, 424)
        self.listView = QtWidgets.QListView(project)
        self.listView.setGeometry(QtCore.QRect(-20, 0, 831, 511))
        self.listView.setStyleSheet("background-image: url(\"D:/managerment/image/view5.jpg\")")
        self.listView.setObjectName("listView")
        self.label = QtWidgets.QLabel(project)
        self.label.setGeometry(QtCore.QRect(260, 70, 81, 21))
        self.label.setObjectName("label")
        self.make_proj = QtWidgets.QPushButton(project)
        self.make_proj.setGeometry(QtCore.QRect(230, 140, 121, 31))
        self.make_proj.setObjectName("make_proj")
        self.check_project = QtWidgets.QPushButton(project)
        self.check_project.setGeometry(QtCore.QRect(230, 210, 121, 31))
        self.check_project.setObjectName("check_project")
        self.exit = QtWidgets.QPushButton(project)
        self.exit.setGeometry(QtCore.QRect(230, 280, 121, 31))
        self.exit.setObjectName("exit")

        self.retranslateUi(project)
        QtCore.QMetaObject.connectSlotsByName(project)

    def retranslateUi(self, project):
        _translate = QtCore.QCoreApplication.translate
        project.setWindowTitle(_translate("project", "Project"))
        self.label.setText(_translate("project", "决策部门"))
        self.make_proj.setText(_translate("project", "创建工程"))
        self.check_project.setText(_translate("project", "工程验收"))
        self.exit.setText(_translate("project", "退出"))
