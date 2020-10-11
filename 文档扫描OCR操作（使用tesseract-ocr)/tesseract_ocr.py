__author__ = "Luke Liu"
#encoding="utf-8"
# https://digi.bib.uni-mannheim.de/tesseract/
# 配置环境变量如E:\Program Files (x86)\Tesseract-OCR
# tesseract -v进行测试
# tesseract XXX.png 得到结果
# pip install pytesseract
# anaconda lib site-packges pytesseract pytesseract.py
# tesseract_cmd 修改为绝对路径即可
from PIL import Image
import pytesseract
import cv2
import os
import matplotlib.pyplot as plt

preprocess = 'thresh'  # thresh

image = cv2.imread('scan.jpg')
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)


if preprocess == "thresh":
    gray = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]

if preprocess == "blur":
    gray = cv2.medianBlur(gray, 3)

filename = "{}.png".format(os.getpid())
cv2.imwrite(filename, gray)

print("begin")
tessdata_dir_config = '--tessdata-dir "C:\\Program Files (x86)\\Tesseract-OCR\\tessdata"'
text = pytesseract.image_to_string(Image.open(filename),config=tessdata_dir_config)
print("OK")
print(text)

with open("content.txt",'wb') as f:
    f.write(bytes(text.encode('utf-8')))


os.remove(filename)
cv2.imshow("Image", image)
cv2.imshow("Output", gray)
cv2.waitKey(0)
