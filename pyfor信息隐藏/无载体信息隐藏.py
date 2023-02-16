import  cv2
import  numpy as np
import os
from Crypto.Cipher import AES
import base64

#the generation of hash sequences based on DCT
def get_block1(cover,M,N,l):
    sub_block1=[]
    for i in range(M):
        for j in range(N):
            block = cover[i*l:i*l + l, j*l:j*l + l]
            sub_block1.append(block)
    return sub_block1

def get_dc(cover):#l*l, will be blocked to 16 sub_blocks
    h,w=cover.shape[0],cover.shape[1]
    ll=h//4#64
    Ds=[]
    for i in range(4):
        for j in range(4):
            block=cover[i*ll:i*ll+ll,j*ll:j*ll+ll]
            sum=0
            for m in range(ll//8):
                for n in range(ll//8):
                    sub_block=block[m*8:m*8+8,n*8:n*8+8]
                    sub_block=np.float32(sub_block)
                    dct_block=cv2.dct(sub_block)
                    sum+=dct_block[0][0]
            Ds.append(sum)
    return Ds

def get_hs(img):
    img=cv2.cvtColor(img, cv2.COLOR_RGB2YUV)
    Y,U,V=cv2.split(img)
    h,w=Y.shape[0], Y.shape[1]
    l=128 #l是要分成16块的块大小
    M=h//l
    N=w//l
    Yb=get_block1(Y,M,N,l)
    HS=[]
    T=0.9
    for yb in Yb:#yb.size=l*l
        dc=get_dc(yb)
        dc_max=max(dc)
        hs=[]
        for d in dc:
            if d/dc_max>T:
                hs.append('1')
            else:
                hs.append('0')
        hs="".join(hs)
        HS.append(hs)
    return HS

#test
'''h=get_hs(img)
print(h)'''



#the establishment of video index structure
def get_data(Folder):
    data=[]
    for file in os.listdir(Folder):
        for f in os.listdir(Folder+file):
            path=Folder+file+'/'+f
            data.append(path)
    return data

def data_to_txt(Dic):
    for item in Dic.items():
        with open(r'D:/2.txt', 'a') as f:
            f.write(item[0]+" "+item[1][0]+" "+item[1][1]+" "+item[1][2]+" "+item[1][3]+'\n')
            #f.write('\t')

def get_dic(data):
    Data_Dic = dict()
    for img in data:
        path, frame = os.path.split(img)
        M=4
        h=[]
        for i in range(4):
            for j in range(4):
                h.append([path,frame,"".join(str(i)),"".join(str(j))])
        img = cv2.imread(img)
        img=cv2.resize(img,(512,512))# 512*512
        hs=get_hs(img)
        for i in range(len(hs)):
            if hs[i] not in Data_Dic:
                Data_Dic[hs[i]]=h[i]
    #data_to_txt(Data_Dic)
    return Data_Dic



#the secret information hiding
def get_secret(secret):
    secret=secret.replace(" ", "")#去除空格和字符
    secret=secret.replace(".","")
    Sect=[]
    for i in range(0,len(secret),2):
        s1=bin(ord(secret[i]))[2:].zfill(8)
        s2=bin(ord(secret[i+1]))[2:].zfill(8)
        s=s1+s2
        Sect.append(s)
    return Sect


def aes_encrypt(key,iv,text):
    key = key.encode('utf-8')
    iv = iv.encode('utf-8')
    cipher = AES.new(key, AES.MODE_CBC, iv)
    encrypt_bytes = cipher.encrypt(text.encode('utf-8'))
    result = str(base64.b64encode(encrypt_bytes), encoding='utf-8')
    return result

def text_to_str(text):
    s=""
    for t in text:
        s=s+t[0]+'|'+t[1]+'|'+t[2]+'|'+t[3]+'#'
    return s

def pkcs7padding(text):#明文使用PKCS7填充
    text=text_to_str(text)
    bs = 16
    length = len(text)
    bytes_length = len(text.encode('utf-8'))
    padding_size = length if (bytes_length == length) else bytes_length
    padding = bs - padding_size % bs
    padding_text = chr(padding) * padding
    return text + padding_text

def EN_AES(text):
    iv = '01pv928nv2i5ss68'
    key = '63f09k56nv2b10cf'
    text_padding = pkcs7padding(text)
    e = aes_encrypt(key,iv,text_padding)
    return e

def get_text(Dic,secret):
    text=[]
    for s in secret:
        for key in Dic:
            if s==key:
                text.append(Dic[key])
    return text

def hiding(secret):
    print("隐写中……")
    S=get_secret(secret)
    Folder = "D:/DAVIS/DAVIS-2017-trainval-480p/DAVIS/JPEGImages/480p/"
    data=get_data(Folder)
    Dic=get_dic(data)
    text=get_text(Dic, S)
    print("隐写信息为：", text)
    en_text=EN_AES(text)
    print("该信息加密为：", en_text)
    return en_text


#the extraction of secret information
def aes_decrypt(key,iv,text):
    """
    AES解密
    """
    key = key.encode('utf-8')
    iv = iv.encode('utf-8')
    cipher = AES.new(key, AES.MODE_CBC, iv)
    text = base64.b64decode(text)
    text = cipher.decrypt(text).decode('utf-8')
    return text

def DE_AES(en_text):
    iv = '01pv928nv2i5ss68'
    key = '63f09k56nv2b10cf'
    d = aes_decrypt(key,iv,en_text)
    return d

def str_to_text(s):
    S=s.split("#")
    for i in range(len(S)-1):
        S[i]=S[i].split("|")
    S.pop()#remove the last item
    return S

def extract(en_text):
    print("提取中……")
    d=DE_AES(en_text)
    text=str_to_text(d)
    Folder = "D:/DAVIS/DAVIS-2017-trainval-480p/DAVIS/JPEGImages/480p/"
    data=get_data(Folder)
    Dic=get_dic(data)
    T=[]
    for t in text:
        for key in Dic:
            if Dic[key]==t:
                T.append(key)
    #print(T)
    S=""
    for t in T:
        s1=chr(int(t[0:8],2))
        s2=chr(int(t[8:],2))
        S=S+s1+s2
    print("该信息提取为：", S)
    return S




if __name__ == '__main__':
    secret="3tet."
    print("秘密信息为：", secret)
    #secret = "Meet me at 2 in the park."
    text=hiding(secret)
    S=extract(text)


