import os
import cv2
from cnocr import CnOcr
import numpy as np
import re



def detectTable(imgpath):
    img1 = cv2.imread(imgpath)
    # img1 =cv2.resize(img1,None,fx=0.3, fy=0.3, interpolation = cv2.INTER_CUBIC)
    if len(img1.shape) == 2:  # 灰度图
        gray_img = img1
    elif len(img1.shape) == 3:
        gray_img = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)

    thresh_img = cv2.adaptiveThreshold(~gray_img, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 15, -2)
    #cv2.imshow('', thresh_img)
    #cv2.waitKey()
    h_img = thresh_img.copy()
    v_img = thresh_img.copy()

    '''
    此处形态学因子是一条直线，长度一定要设置的合适，由于表格有倾斜，
    图像越大，该值就要设置的越大，否则不能提取出水平线       
    '''
    h_structure = cv2.getStructuringElement(cv2.MORPH_RECT, (30, 1))  # 形态学因子
    h_erode_img = cv2.erode(h_img, h_structure, 1)

    # 膨胀图像
    h_dilate_img = cv2.dilate(h_erode_img, h_structure, 1)
    #cv2.imshow("h_erode",h_dilate_img)
    #cv2.waitKey()

    # 此处形态学因子是一条直线，长度一定要设置的合适，否则不能提取出垂直线
    v_structure = cv2.getStructuringElement(cv2.MORPH_RECT, (1, 30))  # 形态学因子
    v_erode_img = cv2.erode(v_img, v_structure, 1)
    # 膨胀图像
    v_dilate_img = cv2.dilate(v_erode_img, v_structure, 1)

    mask_img = h_dilate_img + v_dilate_img
    #win = cv2.namedWindow("mask", flags=2)
    #cv2.imshow("mask", mask_img)
    #cv2.waitKey()
    #merge2 = cv2.subtract(thresh_img, mask_img)
    #cv2.imshow("binary_sub_excel_rect", merge2)
    #cv2.waitKey()
    # cv2.bitwise_and图像进行与运算
    joints_img = cv2.bitwise_and(h_dilate_img, v_dilate_img)
    cv2.imshow('',joints_img)
    cv2.waitKey()
    contours, hierarchy = cv2.findContours(mask_img, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)  # binary
    print(type(contours), len(contours))  # 共几个轮廓
    #print(contours[0])
    #print(contours)
    #print(contours)
    c = sorted(contours, key=cv2.contourArea, reverse=True)[0]

    return img1,joints_img



ocr = CnOcr()
src='7.png'
raw = cv2.imread(src,1)


# 将焦点标识取出来
binary,mask_img=detectTable(src)
(ys, xs) = np.where(mask_img > 0)
for xx in (ys,xs):
    print(xx)
#for x in xs:
    #for y in ys:
        #print(x)
#print(ys,xs)

h=50
w=180
for xx in (ys,xs):
    cell=binary[xx[0]:xx[0]+h,xx[1]:xx[1]+w]
    cv2.imshow("pic_"+str(xx[1])+str(xx[0]),cell)
    cv2.waitKey()
    text=ocr.ocr(cell)
    text = "".join([str(s) for s in text])
    print('单元格图片信息：%s' % ''.join(text))

# 循环y坐标，x坐标分割表格
control=3
data = [[] for i in range(len(y_point_arr))]
for i in range(len(y_point_arr) - 1):
    for j in range(len(x_point_arr) - 1):
        #print(y_point_arr[i]-1)
        # 在分割时，第一个参数为y坐标，第二个参数为x坐标
        cell = binary[y_point_arr[i]+control:y_point_arr[i + 1]-control, x_point_arr[j]+control:x_point_arr[j + 1]-control]
        cv2.imshow("sub_pic" + str(i) + str(j), cell)
        cv2.waitKey()
        # 读取文字，此为默认英文
        # pytesseract.pytesseract.tesseract_cmd = 'E:/Tesseract-OCR/tesseract.exe'
        text1 = ocr.ocr(cell)


        # 去除特殊字符
        #text1 = re.findall(r'[^\*"/:?\\|<>″′‖ 〈\n]', text1, re.S)
        text1 = "".join([str(s)for s in text1])
        #text2=''.join(text1)
        #print(text1)
        print('单元格图片信息：%s' % ''.join(text1))
        data[i].append(text1)
        j = j + 1
    i = i + 1

'''with open(path, "w", newline='') as csv_file:
      writer = csv.writer(file, dialect='excel')
      for index, item in enumerate(data):
          if index != 0 and index != len(data) - 1:
              writer.writerows([[item[0], item[1], item[2], item[3], item[4], item[5]]])'''
