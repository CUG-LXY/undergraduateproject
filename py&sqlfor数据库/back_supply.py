#!/usr/bin/env python
# -*- coding: utf-8 -*-
import back_link as link




#查询供应商信息
def query_suppliers(project_id,part_id):
    db,cursor=link.conn()
    sql1="select supplier.supplier_id,price,num,supplier.city_name,city.posx ,city.posy from (supplier join supplier_parts on supplier.supplier_id=supplier_parts.supplier_id) join city on supplier.city_name=city.city_name where part_id = '"+part_id+"';"
    cursor.execute(sql1)
    li_s=[]
    row=cursor.fetchone()
    for row in cursor:
        li_s.append(row)
    sql2="select project.project_id,city.city_name,city.posx,city.posy from project,city where project.city_name=city.city_name and project.project_id='"+project_id+"';"
    cursor.execute(sql2)
    li_p=[]
    row1=cursor.fetchone()
    li_p.append(row1)
    db.close()
    return li_s,li_p




#零件购买
def buy_comp(deal_id,project_id,supplier_id,part_id,num,phase):
    db,cursor=link.conn() 
    sql1='insert into make_deal values(%s,%s,%s,%s,%d,%d)'
    param = (deal_id,project_id,supplier_id,part_id,num,phase)
    for p in param:
        print(p)
    cursor.execute(sql1,param)
    db.commit()
    #sql2="update supplier_parts set num=num- "+num+" where supplier_id="+supplier_id+" and part_id="+part_id
    sql2="update supplier_parts set num=num- %d"%int(num)+" where supplier_id= '"+supplier_id+"' and part_id= '"+part_id+" ' "
    print(sql2)
    cursor.execute(sql2)
    db.commit()
    sql3="update project_parts set num = num + %d"%int(num)+" where project_id= '"+project_id+"' and part_id= '"+part_id+"'"
    cursor.execute(sql3)
    db.commit()
    sql4="update parts_list set effective = 0 where part_id= '"+part_id+" ' "
    cursor.execute(sql4)
    db.commit()
    db.close()
    return True



#确认清单状态
def cof_list(project_id):
    db,cursor=link.conn()
    sql="select project_id,part_list_id,parts_list.part_id,require_num,had_bought_num from parts_list join make_list on part_list_id=parts_list_id where project_id='"+project_id+"';"
    cursor.execute(sql)
    li=[]
    row=cursor.fetchone()
    for row in cursor:
        li.append(row)
    db.close()
    return li