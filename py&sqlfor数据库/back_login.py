#!/usr/bin/env python
# -*- coding: utf-8 -*-
from typing import Counter
import back_link as link




def get_pwd(ID):
    db,cursor=link.conn()
    cursor.execute("select pwd from ID_pwd where ID= '"+ID+"'")
    li=''
    row=cursor.fetchone()
    li=str(row[0])
    db.close()
    return li




