#!/usr/bin/env python
# -*- coding: utf-8 -*-
import pymssql


def conn():
    connection=pymssql.connect('LAPTOP-KN6LRT09', 'sa', '20001026', 'proj',charset = 'GB18030') #服务器名,账户,密码,数据库名
    '''if connection:
        print("连接成功")'''
    cursor=connection.cursor()
    return connection,cursor



