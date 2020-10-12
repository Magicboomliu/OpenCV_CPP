__author__ = "Luke Liu"
#encoding="utf-8"

#导入需要的库文件
import matplotlib.pyplot as plt
import cv2
import os, glob
import numpy as np
from Parking_spot import Parking_spot
import pickle

# 引入 keras 库
from PIL import Image
from keras.applications.imagenet_utils import preprocess_input
from keras.models import load_model
from keras.preprocessing import image


# 图像处理
def img_process(test_images,park):

    #将图片保留一部分颜色，做bit-and运算
    white_yellow_images = list(map(park.select_rgb_white_yellow, test_images))
    # park.show_images(white_yellow_images)
    #图像转化为灰度图像
    gray_images = list(map(park.convert_gray_scale, white_yellow_images))
    # park.show_images(gray_images)
    # 对图像进行Canny边缘检测
    edge_images = list(map(park.detect_edges, gray_images))
    # park.show_images(edge_images)

    #提取停车场我们需要的那部分区域roi_images
    roi_images = list(map(park.select_region, edge_images))
    # park.show_images(roi_images)

    #对提取出来的roi_images检测直线，在这里使用Hough直线检测
    list_of_lines = list(map(park.hough_lines_detect, roi_images))

    #在原图上画出停车位的直线的图
    line_images = []
    for image, lines in zip(test_images, list_of_lines):
        line_images.append(park.draw_lines(image, lines))
    # park.show_images(line_images)

    #在图像中对停车位的区域进行聚类，得到每个聚类的坐标
    rect_images = []
    rect_coords = []
    for image, lines in zip(test_images, list_of_lines):
        new_image, rects = park.identify_blocks(image, lines)
        rect_images.append(new_image)
        rect_coords.append(rects)
    #展示一下划分的图片
    # park.show_images(rect_images)

    #微调一下矩形 delineated, 统计spot_pos的个数
    delineated = []
    spot_pos = []
    for image, rects in zip(test_images, rect_coords):
        new_image, spot_dict = park.draw_parking(image, rects)
        delineated.append(new_image)
        spot_pos.append(spot_dict)

    # park.show_images(delineated)

    # 选择第2张图片作为最后的字典结果
    final_spot_dict = spot_pos[1]
    print(len(final_spot_dict))

    #将字典的结果保存在pickle文件中，方便调用使用
    with open('spot_dict.pickle', 'wb') as handle:
        pickle.dump(final_spot_dict, handle, protocol=pickle.HIGHEST_PROTOCOL)

    park.save_images_for_cnn(test_images[0], final_spot_dict)

    return final_spot_dict

# 读取训练好的h5模型导入模型
def keras_model(weights_path):
    model = load_model(weights_path)
    return model

# test the image
def img_test(test_images,final_spot_dict,model,class_dictionary):
    for i in range (len(test_images)):
        predicted_images = park.predict_on_image(test_images[i],final_spot_dict,model,class_dictionary)

# 这个main函数就是为了测试而建立的
if __name__ == '__main__':
    # 标签对应的字典
    class_dictionary = {}
    class_dictionary[0] = 'empty'
    class_dictionary[1] = 'occupied'
    trained_model_path='car1.h5'



    test_images_path = [cv2.imread(os.path.join("test_images",f)) for f in os.listdir('test_images')]
    park=Parking_spot()
    park.show_images(test_images_path)
    final_spot_dict= img_process(test_images=test_images_path,park=park)

    # 载入模型
    model = keras_model(trained_model_path)

    # 测试图片
    img_test(test_images_path,final_spot_dict=final_spot_dict,model=model,class_dictionary=class_dictionary)





