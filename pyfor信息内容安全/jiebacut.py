# -*- coding: gbk -*-
import jieba
import sys


test_contents = [
    "���Ƕ���С����",
    "��������",
    "ϲ�����ֵ�����",
    "���ὲЦ��"]
for content in test_contents:
    result = jieba.tokenize(content)
    result = list(result)
    for tk in result:
        print("word %s\t\t start: %d \t\t end:%d" % (tk[0],tk[1],tk[2]), file=sys.stderr)
        
   
#for content in test_contents:

import jieba.analyse
topK = 20
content = open("1.txt", 'rb').read()
tags = jieba.analyse.extract_tags(content, topK=topK)
print(",".join(tags))
print("��ȡ�ؼ��ʹ������")

for content in test_contents:
    result = jieba.tokenize(content)
    result = list(result)
    for tk in result:
        print("word %s\t\t start: %d \t\t end:%d" % (tk[0],tk[1],tk[2]), file=sys.stderr)
        #print("testTokenize", file=sys.stderr)




seg_list = jieba.cut(str, cut_all=False)
print("\n��ȷģʽ: \n" + "/ ".join(seg_list))  # ��ȷģʽ

seg_list = jieba.cut(str, cut_all=True)
print("\nȫģʽ: \n" + "/ ".join(seg_list))  # ȫģʽ

seg_list = jieba.cut_for_search(str)  # ��������ģʽ
print("\n��������ģʽ��\n"+"/ ".join(seg_list))

seg_list = jieba.cut(str,use_paddle=True) # ʹ��paddleģʽ
print("Paddleģʽ: " + '/'.join(list(seg_list)))







