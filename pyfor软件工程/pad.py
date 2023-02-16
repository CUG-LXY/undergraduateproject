from PIL import Image, ImageDraw, ImageFont
from paddleocr import PaddleOCR, draw_ocr
import cv2
import math
import numpy as np
import random




#画图
def draw_txt(img,boxes,txts):
    h,w=img.size[0],img.size[1]
    img1 = Image.new('RGB', (h,w), (255, 255, 255))
    draw = ImageDraw.Draw(img)
    draw1 = ImageDraw.Draw(img1)

    fontStyle = ImageFont.truetype("simsun.ttc",size=30, encoding="utf-8")
    for (box,txt) in zip(boxes,txts):
        color = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
        draw.rectangle(((box[0][0], box[0][1]),(box[2][0], box[2][1])), fill=None, outline=color, width=2)
        draw1.rectangle(((box[0][0], box[0][1]), (box[2][0], box[2][1])), fill=None, outline=color, width=2)
        draw1.text((box[0][0], box[0][1]), txt, (0,0,0), font=fontStyle)

    res = np.hstack([img, img1])
    return res


def ocr_table(img_path,save_path):
    ocr = PaddleOCR(use_angle_cls=True, use_gpu=False)
    #img_path = '32.jpg'
    result = ocr.ocr(img_path, cls=True)
    # for line in result:
        # print(line)
    boxes = [line[0] for line in result]
    txts = [line[1][0] for line in result]
    #scores = [line[1][1] for line in result]
    img = Image.open(img_path).convert('RGB')
    #get_img = draw_ocr(img, boxes, txts, scores)
    get_img=draw_txt(img,boxes,txts)
    cv2.imwrite(save_path,get_img)
    #cv2.imshow('ext_words',get_img)
    #cv2.waitKey()


def ocr_table(img_path):
    ocr = PaddleOCR(use_angle_cls=True, use_gpu=False)
    result = ocr.ocr(img_path, cls=True)
    for line in result:
        print(line)
    boxes = [line[0] for line in result]
    txts = [line[1][0] for line in result]
    #print(boxes)
    #print(txts)

if __name__ == '__main__':
    #img_path = '1.png'
    img_path = '39.jpg'
    save_path = 're.png'
    ocr_table(img_path)#,save_path)



