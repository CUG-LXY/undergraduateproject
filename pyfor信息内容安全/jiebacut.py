# -*- coding: gbk -*-
import jieba
import sys


test_contents = [
    "我们都是小青蛙",
    "呱呱呱呱",
    "喜欢快乐的生活",
    "还会讲笑话"]
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
print("提取关键词功能完成")

for content in test_contents:
    result = jieba.tokenize(content)
    result = list(result)
    for tk in result:
        print("word %s\t\t start: %d \t\t end:%d" % (tk[0],tk[1],tk[2]), file=sys.stderr)
        #print("testTokenize", file=sys.stderr)




seg_list = jieba.cut(str, cut_all=False)
print("\n精确模式: \n" + "/ ".join(seg_list))  # 精确模式

seg_list = jieba.cut(str, cut_all=True)
print("\n全模式: \n" + "/ ".join(seg_list))  # 全模式

seg_list = jieba.cut_for_search(str)  # 搜索引擎模式
print("\n搜索引擎模式：\n"+"/ ".join(seg_list))

seg_list = jieba.cut(str,use_paddle=True) # 使用paddle模式
print("Paddle模式: " + '/'.join(list(seg_list)))







