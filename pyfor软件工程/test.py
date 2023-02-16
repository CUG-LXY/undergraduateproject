from cnstd import CnStd
from cnocr import CnOcr
import cv2
std = CnStd()
cn_ocr = CnOcr()

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
    win = cv2.namedWindow("mask", flags=2)
    cv2.imshow("mask", mask_img)
    cv2.waitKey()
    merge2 = cv2.subtract(thresh_img, mask_img)
    cv2.imshow("binary_sub_excel_rect", merge2)
    cv2.waitKey()
    cv2.imwrite('33.png',merge2)
    # cv2.bitwise_and图像进行与运算
    '''joints_img = cv2.bitwise_and(h_dilate_img, v_dilate_img)
    cv2.imshow('',joints_img)
    cv2.waitKey()
    return img1,joints_img'''

#detectTable('7.png')
box_info_list = std.detect('p3.jpg')

for box_info in box_info_list:

    cropped_img = box_info['cropped_img']  # 检测出的文本框
    ocr_res = cn_ocr.ocr_for_single_line(cropped_img)
    print('ocr result: %s' % ''.join(ocr_res))


'''from cnocr import CnOcr
ocr = CnOcr()
res = ocr.ocr('22.png')
res="".join([str(s) for s in res])
print("Predicted Chars:", res)

name = ["yu", "zi", "sheng"]
print("".join(name))  # "yuzisheng"'''

'''from PIL import Image
import pytesseract

text = pytesseract.image_to_string(Image.open(r'test.png'))
print(text)'''


'''import keras
import numpy as np
import cv2
import tensorflow as tf
layers=keras.layers
Model=keras.Model
models=keras.models
Conv=layers.Conv2D
Optimizer=keras.optimizers.Adam(learning_rate=3e-3,epsilon=1e-08)
TimeDistributed=layers.TimeDistributed
Input=layers.Input
Pool=layers.MaxPool2D
BN=layers.BatchNormalization
UpSample=layers.UpSampling2D
Resize=layers.Reshape
  


F= np.random.rand(3,9,32,32)
model=build_rnn(F)
model.summary'''