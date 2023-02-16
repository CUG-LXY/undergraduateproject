#!/usr/bin/env python
# -*- coding: utf-8 -*-
import back_link as link

#查看员工信息
def check_person():
    db,cursor=link.conn()
    cursor.execute("select * from employee where sex='m'")#需要修改
    li=[]
    row=cursor.fetchone()
    for row in cursor:
        li.append(row)
    db.close()
    return li

#check_person()

#查看工程信息
def check_project():
    db,cursor=link.conn()
    cursor.execute("select * from project where phaseNo='1'")#需要修改
    li=[]
    row=cursor.fetchone()
    print(row)
    for row in cursor:
        li.append(row)
    db.close()
    print(li)
    return li


#查看工程进度
def check_pace():
    db,cursor=link.conn()
    cursor.execute("select project_id,project_name,phaseNo from project")#需要修改
    li=[]
    row=cursor.fetchone()
    for row in cursor:
        li.append(row)
    db.close()
    return li


#查看零件情况
def check_component():
    db,cursor=link.conn()
    cursor.execute("select * from parts")
    #cursor.execute("select part_list_id,parts_list.part_id,require_num,had_bought_num from parts_list join make_list on parts_list.part_list_id=make_list.parts_list_id where project_id='000' group by effective")
    li=[]
    row=cursor.fetchone()
    for row in cursor:
        li.append(row)
    db.close()
    return li


#查看供应商信息
def check_suppliers():
    db,cursor=link.conn()
    cursor.execute('select * from supplier')
    li=[]
    row=cursor.fetchone()
    for row in cursor:
        li.append(row)
    db.close()
    return li


#查看交易信息
def check_trade():
    db,cursor=link.conn()
    cursor.execute("select * from make_deal")#需要修改
    li=[]
    row=cursor.fetchone()
    for row in cursor:
        li.append(row)
    db.close()
    return li