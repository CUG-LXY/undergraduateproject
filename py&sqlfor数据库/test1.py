plain='a1'
def get_int(plain):
    num=0
    for p in plain:
        num = num+ord(p)-47
    print(num)
    return num

import paillier
pwd = '123'
pwd=get_int(pwd)

'''priv, pub = paillier.generate_keypair(128)
print(type(pub))
print(pub.n)
print(pub.n_sq)
print(pub.g)'''
pub1=p_key = 2064812439292798824322
s_pwd=paillier.encrypt(pub1,int(pwd))
print(s_pwd)

'''import pymssql #引入pymssql模块
#'LAPTOP-KN6LRT09', 'sa', '20001026', 'proj',charset = 'GB18030'
def conn():
    server = 'LAPTOP-KN6LRT09'
    user = 'sa'
    password = '20001026'
    table = 'proj'
    connect = pymssql.connect(server, user, password, table) #服务器名,账户,密码,数据库名
    if connect:
        print("连接成功!")
    return connect

def Project_Check():
    db = conn()
    cursor = db.cursor()
    sql = 'select project.project_id,project.phaseNo,ini_plan.phase_sum from project,make_plan,ini_plan where project.project_id = make_plan.project_id and make_plan.ini_plan_id = ini_plan.ini_plan_id'
    #print(sql)
    try:
        cursor.execute(sql)
        li=[]
        result = cursor.fetchall()
        print(result)
        for r in result:
            li.append(r)
        print(result)
        print(li)
        cursor.close()
        db.close()
        print("项目查询成功")
    except Exception as e:
        print(e)
        db.rollback()
        cursor.close()
        db.close()


if __name__ == '__main__':
    Project_Check()'''

 
'''select project.project_id,project.phaseNo,ini_plan.phase_sum
from project,make_plan,ini_plan 
where project.project_id = make_plan.project_id and make_plan.ini_plan_id = ini_plan.ini_plan_id'''

