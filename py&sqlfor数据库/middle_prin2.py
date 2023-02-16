#!/usr/bin/python3
# -*- coding: utf-8 -*-


from front_princheck import Ui_prinCheck
from back_prin_check import *


from PyQt5.QtWidgets import QApplication, QMainWindow, QMessageBox, QHeaderView,QTableWidgetItem,QWidget
from PyQt5.QtWidgets import *
#查询员工信息
class prin_check_person(QMainWindow, Ui_prinCheck):
    def __init__(self, parent=None):
        super(prin_check_person, self).__init__(parent)
        self.setupUi(self)
        self.showInfo()
        self.exit.clicked.connect(self.close)

    def showInfo(self):
        info = check_person()
        row = len(info)
        print(row)
        col = 7
        self.tableWidget.setRowCount(row)
        self.tableWidget.setColumnCount(col)
        self.tableWidget.setHorizontalHeaderLabels(['employee_id','employee_name','sex','birth_day','phone_number','family_address','position'])
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Fixed)
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        #self.tableWidget.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)#随内容分配列宽
        self.tableWidget.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.tableWidget.verticalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)
        self.tableWidget.horizontalHeader().setStretchLastSection(True)
        

        for r in range(row):
            employee_id = info[r][0]
            employee_name = info[r][1]
            sex = info[r][2]
            birth_day = info[r][3]
            phone_number = info[r][4]
            family_address = info[r][5]
            position = info[r][6]

            self.tableWidget.setItem(r,0,QTableWidgetItem(employee_id))
            self.tableWidget.setItem(r,1,QTableWidgetItem(employee_name))
            self.tableWidget.setItem(r,2,QTableWidgetItem(sex))
            self.tableWidget.setItem(r,3,QTableWidgetItem(str(birth_day)))
            self.tableWidget.setItem(r,4,QTableWidgetItem(phone_number))
            self.tableWidget.setItem(r,5,QTableWidgetItem(family_address))
            self.tableWidget.setItem(r,6,QTableWidgetItem(position))
        
        self.tableWidget.raise_()
        #self.tableWidget.show()

#查询工程信息
class prin_check_project(QMainWindow, Ui_prinCheck):
    def __init__(self, parent=None):
        super(prin_check_project, self).__init__(parent)
        self.setupUi(self)
        self.showInfo()
        self.exit.clicked.connect(self.close)

    def showInfo(self):
        info = check_project()
        row = len(info)
        col = 9
        self.tableWidget.setRowCount(row)
        self.tableWidget.setColumnCount(col)
        self.tableWidget.setHorizontalHeaderLabels(['project_id','phaseNo','project_name','scale_level','responsible_man','employee_num','city_name','start_time','end_time'])
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Fixed)
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        #self.tableWidget.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)#随内容分配列宽
        self.tableWidget.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.tableWidget.verticalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)
        self.tableWidget.horizontalHeader().setStretchLastSection(True)

        for r in range(row):
            project_id = info[r][0]
            phaseNo = str(info[r][1])
            project_name = info[r][2]
            scale_level = info[r][3]
            responsible_man = info[r][4]
            employee_num = str(info[r][5])
            city_name = info[r][6]
            start_time = info[r][7]
            end_time = info[r][8]
            self.tableWidget.setItem(r,0,QTableWidgetItem(project_id))
            self.tableWidget.setItem(r,1,QTableWidgetItem(phaseNo))
            self.tableWidget.setItem(r,2,QTableWidgetItem(project_name))
            self.tableWidget.setItem(r,3,QTableWidgetItem(scale_level))
            self.tableWidget.setItem(r,4,QTableWidgetItem(responsible_man))
            self.tableWidget.setItem(r,5,QTableWidgetItem(employee_num))
            self.tableWidget.setItem(r,6,QTableWidgetItem(city_name))
            self.tableWidget.setItem(r,7,QTableWidgetItem(str(start_time)))
            self.tableWidget.setItem(r,8,QTableWidgetItem(str(end_time)))
        
        self.tableWidget.raise_()

#查询工程进度
class prin_check_pace(QMainWindow, Ui_prinCheck):
    def __init__(self, parent=None):
        super(prin_check_pace, self).__init__(parent)
        self.setupUi(self)
        self.showInfo()
        self.exit.clicked.connect(self.close)

    def showInfo(self):
        info = check_pace()
        row = len(info)
        col = 3
        self.tableWidget.setRowCount(row)
        self.tableWidget.setColumnCount(col)
        self.tableWidget.setHorizontalHeaderLabels(['project_id','project_name','project_pace'])
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Fixed)
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.tableWidget.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)#随内容分配列宽
        self.tableWidget.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.tableWidget.verticalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)
        self.tableWidget.horizontalHeader().setStretchLastSection(True)

        for r in range(row):
            project_id = info[r][0]
            project_name = info[r][1]
            project_pace = str(info[r][2])
            

            self.tableWidget.setItem(r,0,QTableWidgetItem(project_id))
            self.tableWidget.setItem(r,1,QTableWidgetItem(project_name))
            self.tableWidget.setItem(r,2,QTableWidgetItem(project_pace))
        self.tableWidget.raise_()

#查看零件情况
class prin_check_component(QMainWindow, Ui_prinCheck):
    def __init__(self, parent=None):
        super(prin_check_component, self).__init__(parent)
        self.setupUi(self)
        self.showInfo()
        self.exit.clicked.connect(self.close)

    def showInfo(self):
        info = check_component()
        row = len(info)
        col = 4
        self.tableWidget.setRowCount(row)
        self.tableWidget.setColumnCount(col)
        self.tableWidget.setHorizontalHeaderLabels(['part_id','part_name','color','type'])
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Fixed)
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.tableWidget.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)#随内容分配列宽
        self.tableWidget.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.tableWidget.verticalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)
        self.tableWidget.horizontalHeader().setStretchLastSection(True)

        for r in range(row):
            part_id = info[r][0]
            part_name = info[r][1]
            color = info[r][2]
            type = info[r][3]

            self.tableWidget.setItem(r,0,QTableWidgetItem(part_id))
            self.tableWidget.setItem(r,1,QTableWidgetItem(part_name))
            self.tableWidget.setItem(r,2,QTableWidgetItem(color))
            self.tableWidget.setItem(r,3,QTableWidgetItem(type))
        self.tableWidget.raise_()

#查看供应商信息
class prin_check_supplier(QMainWindow, Ui_prinCheck):
    def __init__(self, parent=None):
        super(prin_check_supplier, self).__init__(parent)
        self.setupUi(self)
        self.showInfo()
        self.exit.clicked.connect(self.close)

    def showInfo(self):
        info = check_suppliers()
        row = len(info)
        col = 3
        self.tableWidget.setRowCount(row)
        self.tableWidget.setColumnCount(col)
        self.tableWidget.setHorizontalHeaderLabels(['supplier_id','supplier_name','city_name'])
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Fixed)
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.tableWidget.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)#随内容分配列宽
        self.tableWidget.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.tableWidget.verticalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)
        self.tableWidget.horizontalHeader().setStretchLastSection(True)

        for r in range(row):
            supplier_id = info[r][0]
            supplier_name = info[r][1]
            city_name = info[r][2]

            self.tableWidget.setItem(r,0,QTableWidgetItem(supplier_id))
            self.tableWidget.setItem(r,1,QTableWidgetItem(supplier_name))
            self.tableWidget.setItem(r,2,QTableWidgetItem(city_name))
        self.tableWidget.raise_()  

#查看交易信息
class prin_check_trade(QMainWindow, Ui_prinCheck):
    def __init__(self, parent=None):
        super(prin_check_trade, self).__init__(parent)
        self.setupUi(self)
        self.showInfo()
        self.exit.clicked.connect(self.close)

    def showInfo(self):
        info = check_trade()
        row = len(info)
        col = 6
        self.tableWidget.setRowCount(row)
        self.tableWidget.setColumnCount(col)
        self.tableWidget.setHorizontalHeaderLabels(['deal_id','project_id','supplier_id','part_id','num','phase'])
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Fixed)
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.tableWidget.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)#随内容分配列宽
        self.tableWidget.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.tableWidget.verticalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)
        self.tableWidget.horizontalHeader().setStretchLastSection(True)

        for r in range(row):
            deal_id = info[r][0]
            project_id = info[r][1]
            supplier_id = info[r][2]
            part_id = info[r][3]
            num = str(info[r][4])
            phase = str(info[r][5])

            self.tableWidget.setItem(r,0,QTableWidgetItem(deal_id))
            self.tableWidget.setItem(r,1,QTableWidgetItem(project_id))
            self.tableWidget.setItem(r,2,QTableWidgetItem(supplier_id))
            self.tableWidget.setItem(r,3,QTableWidgetItem(part_id))
            self.tableWidget.setItem(r,4,QTableWidgetItem(num))
            self.tableWidget.setItem(r,5,QTableWidgetItem(phase))
        self.tableWidget.raise_()
