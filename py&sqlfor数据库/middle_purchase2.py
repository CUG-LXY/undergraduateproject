#!/usr/bin/python3
# -*- coding: utf-8 -*-

import numpy as np
from PyQt5.QtCore import reset
from front_supcheck import Ui_supCheck
from front_supcheck_suply import Ui_supCheck_sup
from front_supcheck_list import Ui_supCheck_list
from front_pur_part import Ui_pur_comp
from back_supply import *


from PyQt5.QtWidgets import QApplication, QMainWindow, QMessageBox, QHeaderView,QTableWidgetItem

#查询供应商信息
class sup_check_suply(QMainWindow, Ui_supCheck_sup):
    def __init__(self, parent=None):
        super(sup_check_suply, self).__init__(parent)
        self.setupUi(self)
        self.pushButton_query.clicked.connect(self.showInfo)
        #self.showInfo()
        self.exit.clicked.connect(self.close)
    
    def get_d(self,s_x,s_y,p_x,p_y):
        v1=np.array([s_x,s_y])
        v2=np.array([p_x,p_y])
        d=np.sqrt(np.sum(np.square(v1-v2)))
        #d=np.linalg.norm(v1-v2)
        return d
    
    def sele(self,li_s,li_p):
        #print(li_p)
        #print(li_s)
        if len(li_s)==1:
            return li_s
        price=[]
        for s in li_s:
            price.append(s[1])
        min_price=min(price)
        min_p=[]
        for s in li_s:
            if s[1]==min_price:
                min_p.append(s)
        li_s.clear()
        if len(min_p)==1:
            return min_p
        distance=[]
        for s in min_p:
            print(s)
            
            d=self.get_d(s[4],s[5],li_p[0][2],li_p[0][3])
            distance.append(d)
        info=[]
        min_d=min(distance)
        for i in range(len(distance)):
            if distance[i]==min_d:
                info.append(min_p[i])
        return info

        





    def showInfo(self):
        project_id = self.lineEdit_project.text()
        part_id = self.lineEdit_part.text()
        li_s,li_p = query_suppliers(project_id,part_id)
        info=self.sele(li_s,li_p)
        print(info)
        row = len(info)
        col = 4
        self.tableWidget.setRowCount(row)
        self.tableWidget.setColumnCount(col)
        self.tableWidget.setHorizontalHeaderLabels(['supplier_id','price','num','city_name'])
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Fixed)
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.tableWidget.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)#随内容分配列宽
        self.tableWidget.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.tableWidget.verticalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)
        self.tableWidget.horizontalHeader().setStretchLastSection(True)

        for r in range(row):
            supplier_id = info[r][0]
            price = str(info[r][1])
            num = str(info[r][2])
            city_name = str(info[r][3])
            print(city_name)

            self.tableWidget.setItem(r,0,QTableWidgetItem(supplier_id))
            self.tableWidget.setItem(r,1,QTableWidgetItem(price))
            self.tableWidget.setItem(r,2,QTableWidgetItem(num))
            self.tableWidget.setItem(r,3,QTableWidgetItem(city_name))
        self.tableWidget.raise_()


#确认清单信息
class sup_conf_list(QMainWindow, Ui_supCheck_list):
    def __init__(self, parent=None):
        super(sup_conf_list, self).__init__(parent)
        self.setupUi(self)
        self.pushButton_project.clicked.connect(self.showInfo)
        self.exit.clicked.connect(self.close)

    def showInfo(self):
        project_id = self.lineEdit_project.text()
        info = cof_list(project_id)
        row = len(info)
        col = 5
        self.tableWidget.setRowCount(row)
        self.tableWidget.setColumnCount(col)
        self.tableWidget.setHorizontalHeaderLabels(['project_id','part_list_id','part_id','require_num','had_bought_num'])
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Fixed)
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.tableWidget.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)#随内容分配列宽
        self.tableWidget.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.tableWidget.verticalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)
        self.tableWidget.horizontalHeader().setStretchLastSection(True)

        for r in range(row):
            project_id = info[r][0]
            part_list_id = str(info[r][1])
            part_id = info[r][2]
            require_num = str(info[r][3])
            had_bought_num = str(info[r][4])

            self.tableWidget.setItem(r,0,QTableWidgetItem(project_id))
            self.tableWidget.setItem(r,1,QTableWidgetItem(part_list_id))
            self.tableWidget.setItem(r,2,QTableWidgetItem(part_id))
            self.tableWidget.setItem(r,3,QTableWidgetItem(require_num))
            self.tableWidget.setItem(r,4,QTableWidgetItem(had_bought_num))
        self.tableWidget.raise_()








#零件购买
class sup_buy(QMainWindow, Ui_pur_comp):
    def __init__(self, parent=None):
        super(sup_buy, self).__init__(parent)
        self.setupUi(self)
        self.pushButton_continue.clicked.connect(self.buy)
        self.pushButton_finish.clicked.connect(self.close)

    def buy(self):
        deal_id = self.lineEdit_deal.text()
        self.lineEdit_deal.clear()
        project_id = self.lineEdit_project.text()
        self.lineEdit_project.clear()
        supplier_id = self.lineEdit_supplier.text()
        self.lineEdit_supplier.clear()
        part_id = self.lineEdit_part.text()
        self.lineEdit_part.clear()
        num = self.lineEdit_num.text()
        self.lineEdit_num.clear()
        phase = self.lineEdit_phase.text()
        self.lineEdit_phase.clear()

        info = buy_comp(deal_id,project_id,supplier_id,part_id,num,phase)
        if info==True:
            print("购买成功！")
        else:
            print("买入失败！")



    