import cv2
import numpy as np
import math
from skimage.metrics import structural_similarity as ssim
from skimage.measure import compare_ssim
def psnr1(img1,img2):
    #compute mse
    # mse = np.mean((img1-img2)**2)
    mse = np.mean((img1/1.0-img2/1.0)**2)
    #compute psnr
    if mse < 1e-10:
        return 100
    psnr1 = 20*math.log10(255/math.sqrt(mse))
    return psnr1

def psnr2(img1,img2):
    mse = np.mean((img1/255.0-img2/255.0)**2)
    if mse < 1e-10:
        return 100
    psnr2 = 20*math.log10(1/math.sqrt(mse))
    return psnr2


def en_arnold(img):#a=1,b=1
    h,w=img.shape[0],img.shape[1]
    arnold_img=np.zeros((h,w),np.uint8)
    N=h
    a=1
    b=1
    for xn in range(h):
        for  yn in range(w):
            new_x=(1*xn+a*yn)%N
            new_y=(b*xn+(a*b+1)*yn)%N
            arnold_img[new_x,new_y]=img[xn,yn]
    return arnold_img

def de_arnold(img):#a=1,b=1
    h,w=img.shape[0],img.shape[1]
    de_arnold_img=np.zeros((h,w),np.uint8)
    N=h
    a=1
    b=1
    for xn in range(h):
        for  yn in range(w):
            new_x=((a*b+1)*xn-b*yn)%N
            new_y=((-a)*xn+yn)%N
            de_arnold_img[new_x,new_y]=img[xn,yn]
    de_arnold_img=np.array(de_arnold_img,dtype=np.uint8)
    return de_arnold_img

def get_macroblocks(img):
    h,w=img.shape[0],img.shape[1]
    blocks=[]
    for i in range(h//16):
        for j in range(w//16):
            block = img[i*16:i*16 + 16, j*16:j*16 + 16]
            blocks.append(block)

    return blocks

def block_to_img(blocks):
    h,w=512,512
    count=0
    img=np.zeros([h,w])
    for i in range(h // 16):
        for j in range(w // 16):
            img[i * 16:i * 16 + 16, j * 16:j * 16 + 16]=blocks[count]
            count+=1
            #blocks.append(block)
    img=np.array(img,dtype=np.uint8)
    return img

def get_nnz(block):#16*16
    nnz=[]
    for i in range(4):
        for j in range(4):
            b=block[i*4:i*4+4,j*4:j*4+4]
            b=np.array(b)
            nz=np.count_nonzero(b)
            nnz.append(nz)

    max_nnz=max(nnz)
    return max_nnz

def is_embed(blocks,K):
    is_embed = []
    for b in blocks:
        max = get_nnz(b)
        #print(max)
        if max > K:
            is_embed.append(1)
        else:
            is_embed.append(0)
    return is_embed

def embedding(blocks,watermarking,K,weight):
    is_em=is_embed(blocks,K)
    for i in range(len(blocks)):
        if is_em[i]==1:
            if blocks[i][1][1]!=0 and blocks[i][1][2] != 0 and blocks[i][2][1] !=0 and blocks[i][2][2] != 0:
                nnz_c1=blocks[i][1][3]
                nnz_c=blocks[i][2][1]
                nnz_c2=blocks[i][2][3]
                sum=abs(nnz_c1)+abs(nnz_c2)
                print(sum)
                if watermarking[i]==0:# and abs(nnz_c)>=sum/2:
                    if nnz_c<=0:
                        blocks[i][2][1] = -sum/2
                    else:
                        blocks[i][2][1] = sum/2
                if watermarking[i]==1:
                    if nnz_c<=0:
                        blocks[i][2][1]=-sum/2-weight
                    else:
                        blocks[i][2][1] = sum / 2 + weight

            else:
                nnz_c1 = blocks[i][1][1]
                nnz_c = blocks[i][2][1]
                nnz_c2 = blocks[i][2][2]
                sum = abs(nnz_c1) + abs(nnz_c2)
                if watermarking[i] == 0:  # and abs(nnz_c)>=sum/2:
                    if nnz_c <= 0:
                        blocks[i][2][1] = -sum / 2
                    else:
                        blocks[i][2][1] = sum / 2
                if watermarking[i] == 1:
                    if nnz_c <= 0:
                        blocks[i][2][1] = -sum / 2 - weight
                    else:
                        blocks[i][2][1] = sum / 2 + weight

    return blocks

def extract(blocks,K):
    watermarking=[]
    is_em=is_embed(blocks,K)
    for i in range(len(blocks)):
        if is_em[i]==1:
            if blocks[i][1][1]!=0 and blocks[i][1][2] != 0 and blocks[i][2][1] !=0 and blocks[i][2][2] != 0:
                nnz_c1=blocks[i][1][3]
                nnz_c=blocks[i][2][1]
                nnz_c2=blocks[i][2][3]
                sum=abs(nnz_c1)+abs(nnz_c2)
                if nnz_c<=sum/2:
                    watermarking.append(0)
                else:
                    watermarking.append(1)

            else:
                nnz_c1 = blocks[i][1][1]
                nnz_c = blocks[i][2][1]
                nnz_c2 = blocks[i][2][2]
                sum = abs(nnz_c1) + abs(nnz_c2)
                if nnz_c<=sum/2:
                    watermarking.append(0)
                else:
                    watermarking.append(1)
    return watermarking

def image_binarization(img):

    retval, dst = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)
    cv2.imwrite('baboon.bmp', dst)



def get_watermark(img):
    wm=[]
    img=np.array(img)
    h,w=img.shape[0],img.shape[1]
    #print(h,w)
    for i in range(h):
        for j in range(w):
            #print(img[i][j])
            if img[i][j]==0:
                wm.append(0)
            if img[i][j]==255:
                wm.append(1)

    return wm

def watermarking_to_img(watermarking):
    img=np.zeros([32,32])
    count=0
    for i in range(32):
        for j in range(32):
            if watermarking[count]==0:
                img[i][j]=0
            if watermarking[count]==1:
                img[i][j]=255
            #img[i][j]=watermarking[count]
            count+=1
    img=np.array(img,dtype=np.uint8)
    return img


def watermarking_embed():
    img = cv2.imread('baboon.bmp', 0)
    # image_binarization(img)
    secret=get_watermark(img)
    img1=cv2.imread('scenery.png')
    #img1=cv2.cvtColor(img1, cv2.COLOR_BGR2YUV)
    cv2.imshow('', img1)
    cv2.waitKey()
    Y,R,B=cv2.split(img1)
    R=en_arnold(R)
    #cv2.imshow('',R)
    #cv2.waitKey()
    blocks=get_macroblocks(R)
    K=3
    weight=10

    w_block=embedding(blocks, secret, K, weight)
    img_em=block_to_img(w_block)
    img_em=de_arnold(img_em)
    #print(img_em.shape)
    img2=cv2.merge([Y,img_em,B])
    cv2.imwrite('w_lena.bmp',img2)
    cv2.imshow('',img2)
    cv2.waitKey()
    return img1,img2

def watermarking_ext():
    img = cv2.imread('w_lena.bmp')
    Y, R, B = cv2.split(img)
    R = en_arnold(R)
    blocks = get_macroblocks(R)
    K=3
    w=extract(blocks,K)
    img2=watermarking_to_img(w)
    cv2.imwrite('ext_baboon.bmp',img2)
    cv2.imshow('',img2)
    cv2.waitKey()
    return img2


img1,img2=watermarking_embed()

ssim1 =  compare_ssim(img1, img2, multichannel = True)
print(ssim1)
print(psnr2(img1,img2))
correct_prediction = np.equal(img1,img2)
print(np.mean(correct_prediction))
img3=watermarking_ext()
img4=cv2.imread('baboon.bmp',0)
cv2.imshow('',img4)
cv2.waitKey()
print(psnr1(img3,img4))
ssim2 =  compare_ssim(img3, img4, multichannel = True)
print(ssim2)
correct_prediction = np.equal(img3,img4)
print(np.mean(correct_prediction))