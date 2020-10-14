__author__ = "Luke Liu"
#encoding="utf-8"

''' importing related libraries '''
import numpy as np
import dlib
import cv2

# SSD标签
CLASSES = ["background", "aeroplane", "bicycle", "bird", "boat",
	"bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
	"dog", "horse", "motorbike", "person", "pottedplant", "sheep",
	"sofa", "train", "tvmonitor"]

# 读取caffe网络模型结构文件
def read_caffeNet_structure_and_weights(caffeNet_structure_path,model_weights_path):
    '''
    :param caffeNet_structure_path: .prototxt  file 
    :param model_weights_path: .caffemodel file
    :return: 
    '''
    # 读取了网络的结构以及权重
    net = cv2.dnn.readNetFromCaffe(caffeNet_structure_path,
                                   model_weights_path)
    return net

# 图像预处理
def imagePreprocessing(image_data):
    # 预处理操作,获得高和宽
    (h, w) = image_data.shape[:2]
    # 设置宽度的长度是600
    width = 600
    # 确定要缩放的比例
    r = width / float(w)
    # 获得等比缩放的宽和高
    dim = (width, int(h * r))
    # resize 图片
    frame = cv2.resize(image_data, dim, interpolation=cv2.INTER_AREA)
    # 获得灰度的图片
    rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    return rgb


# 视频追踪
def VideoObjectTrack(video_path,net,confidence=0.5,saved=True):
    '''
    
    :param video_path: 
    :param net: 
    :return: 
    '''

    # 获取一个视频capture
    cap = cv2.VideoCapture(video_path)
    # 读取每一帧，判断是否为最后一帧，图片预处理

    while True:
        ret ,frame =cap.read()
        if frame is None:
            break

        rgb_image =imagePreprocessing(frame)
        # 高和宽为rgb_image的前2维度
        h,w =rgb_image.shape[:2]
        blobs =cv2.dnn.blobFromImage(rgb_image,0.007843, (w, h), 127.5)

        if saved == True:
            fourcc = cv2.VideoWriter_fourcc(*"MJPG")
            writer = cv2.VideoWriter("onlySSD_outcome.avi", fourcc, 30,
                                     (rgb_image.shape[1], rgb_image.shape[0]), True)

        net.setInput(blobs)
        # 前向传播
        detections= net.forward() # outputshape is [1,1,x,7]
        # [image_id, label_id, confidence, xmin, ymin, xmax, ymax]
        for i in np.arange(0,detections.shape[2]):
            cur_confidence = detections[0,0,i,2]
            if cur_confidence>confidence:
                label_idx = detections[0,0,i,1]
                label=CLASSES[int(label_idx)]

                if label=="person":
                    box = detections[0,0,i,3:7] * np.array([w, h, w, h])
                    (startX, startY, endX, endY) = box.astype("int")
                    cv2.rectangle(rgb_image, (startX, startY), (endX, endY), (0, 0, 255),
                              3)
                    cv2.putText(rgb_image, label + "{}".format(i), (int((startX + endX) / 2) - 15, startY - 15),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.45, (0, 255, 0), 2)
                    cv2.imshow("Person_detect", rgb_image)
                    # 保存
                    if saved:
                        writer.write(rgb_image)

        # 按照esc 退出
        key = cv2.waitKey(1) & 0xFF

        # 退出
        if key == 27:

            break

    cap.release()
    cv2.destroyAllWindows()







# test the Image
def Image_detect_test(image_path,net,confidence=0.5):
    frame = cv2.imread(image_path)
    rgb_image = imagePreprocessing(frame)

    # 输入caffe-ssd 获得forward 点的结果，并且查看detection的shape
    h, w = rgb_image.shape[:2]
    blobs = cv2.dnn.blobFromImage(rgb_image, 0.007843, (w, h), 127.5)

    net.setInput(blobs)

    detections = net.forward()



    # caffe 的最后一层输出为[1,1,x,7]
    # 其中x是最后保留的框的个数，最后一维存放的数据为：
    # [image_id, label_id, confidence, xmin, ymin, xmax, ymax]
    # 遍历每一个结果
    for i in np.arange(0, detections.shape[2]):
        cur_confidence = detections[0, 0, i, 2]

        if cur_confidence > confidence:
            label_id = detections[0, 0, i, 1]
            label = CLASSES[int(label_id)]
            if label == "person":
                box = detections[0, 0, i, 3:7] * np.array([w, h, w, h])
                (startX, startY, endX, endY) = box.astype("int")

                cv2.rectangle(rgb_image, (startX, startY), (endX, endY), (0, 0, 255),
                              3)
                cv2.putText(rgb_image,label+"{}".format(i),(int((startX+endX)/2)-15,startY-15),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.45, (0, 255, 0), 2)
                cv2.imshow("Person_detect", rgb_image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()








# test
if __name__ == '__main__':
    # 一会要追踪多个目标
    trackers = []
    labels = []

    # 读取网络
    net =read_caffeNet_structure_and_weights("mobilenet_ssd/MobileNetSSD_deploy.prototxt",
                                             "mobilenet_ssd/MobileNetSSD_deploy.caffemodel")

    VideoObjectTrack("race.mp4",net=net,confidence=0.5)
    # Image_detect_test("mobilenet_ssd/test.jpg",net=net,confidence=0.9)


