import re
import urllib.request
def craw(url,page):
    kv={'user-agent':'Mozilla/5.0'}#模拟浏览器str(html1)
    req=urllib.request.Request(url,headers=kv)
    html1=urllib.request.urlopen(req).read()
    html1=str(html1)
    
    pat1='<div id="J_goodsList".+?<div class="page clearfix">'
    result1=re.compile(pat1).findall(html1)#获取拥有目标图片的代码段
    result1=result1[0]


    pat2='<img width="220" height="220" data-img="1" data-lazy-img="//(.+?\.jpg)"'
    imagelist=re.compile(pat2).findall(result1)#获取图片地址代码段
    

    x=1
    for imageurl in imagelist:
        imagename="./imag/"+str(page)+str(x)+".jpg"#图片名
        imageurl="http://"+imageurl#图片地址
        try:
            urllib.request.urlretrieve(imageurl,filename=imagename)#尝试下载图片
        except urllib.error.URLError as e:
            if hasattr(e,"code"):
                x+=1
            if hasattr(e,"reason"):
                x+=1
        x+=1
for i in range(1,10):#循环查找10页
    url="http://list.jd.com/list.html?cat=9987,653,655&page="+str(i)
    craw(url,i)



