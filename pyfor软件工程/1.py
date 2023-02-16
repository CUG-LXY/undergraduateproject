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

    #mask_img = h_dilate_img + v_dilate_img
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
    return img1,joints_img



ocr = CnOcr()
src='1.png'
raw = cv2.imread(src,1)

'''angle = get_minAreaRect(raw)[-1]
rotated = rotate_bound(raw, angle)
cv2.imshow('',rotated)
cv2.waitKey()'''
# 灰度图片
'''gray = cv2.cvtColor(raw, cv2.COLOR_BGR2GRAY)


binary = cv2.adaptiveThreshold(~gray, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 35, -5)
# 展示图片
cv2.imshow("binary_picture", binary)
cv2.waitKey()
print(binary.shape)
rows, cols = binary.shape[0],binary.shape[1]
scale = 40
# 自适应获取核值
# 识别横线:
kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (cols // scale, 1))
eroded = cv2.erode(binary, kernel, iterations=1)
dilated_col = cv2.dilate(eroded, kernel, iterations=1)
#cv2.imshow("excel_horizontal_line", dilated_col)
#cv2.waitKey()
# 识别竖线：
scale = 20
kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (1, rows // scale))
eroded = cv2.erode(binary, kernel, iterations=1)
dilated_row = cv2.dilate(eroded, kernel, iterations=1)
#cv2.imshow("excel_vertical_line：", dilated_row)
#cv2.waitKey()
# 将识别出来的横竖线合起来
bitwise_and = cv2.bitwise_and(dilated_col, dilated_row)
cv2.imshow("excel_bitwise_and", bitwise_and)
cv2.waitKey()
# 标识表格轮廓
merge = cv2.add(dilated_col, dilated_row)
#cv2.imshow("entire_excel_contour：", merge)
#cv2.waitKey()
# 两张图片进行减法运算，去掉表格框线
merge2 = cv2.subtract(binary, merge)
#cv2.imshow("binary_sub_excel_rect", merge2)
#cv2.waitKey()
new_kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (2, 2))
erode_image = cv2.morphologyEx(merge2, cv2.MORPH_OPEN, new_kernel)
#cv2.imshow('erode_image2', erode_image)
#cv2.waitKey()
merge3 = cv2.add(erode_image, bitwise_and)
#cv2.imshow('merge3', merge3)
#cv2.waitKey()'''
# 将焦点标识取出来
binary,mask_img=detectTable(src)
ys, xs = np.where(mask_img > 0)
#for x in xs:
    #for y in ys:
        #print(x)
#print(ys,xs)


# 横纵坐标数组
y_point_arr = []
x_point_arr = []
# 通过排序，排除掉相近的像素点，只取相近值的最后一点
# 这个10就是两个像素点的距离，不是固定的，根据不同的图片会有调整，基本上为单元格表格的高度（y坐标跳变）和长度（x坐标跳变）
i = 0
sort_x_point = np.sort(xs)
for i in range(len(sort_x_point) - 1):
    if sort_x_point[i + 1] - sort_x_point[i] > 25:
        x_point_arr.append(sort_x_point[i])
    i = i + 1
# 要将最后一个点加入
x_point_arr.append(sort_x_point[i])

i = 0
sort_y_point = np.sort(ys)
# print(np.sort(ys))
for i in range(len(sort_y_point) - 1):
    if (sort_y_point[i + 1] - sort_y_point[i] > 10):
        y_point_arr.append(sort_y_point[i])
    i = i + 1
y_point_arr.append(sort_y_point[i])

print(len(y_point_arr))
print(len(x_point_arr))
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
