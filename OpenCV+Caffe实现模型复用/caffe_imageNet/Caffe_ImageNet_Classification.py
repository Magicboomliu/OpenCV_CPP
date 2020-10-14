__author__ = "Luke Liu"
#encoding="utf-8"

# 引入需要的库文件
import cv2
import numpy as np
import  os

# 标签文件处理
def read_the_label_files(caffe_labels_path):
    # 读取每一行
    rows = open(caffe_labels_path).read().strip().split("\n")
    # 获得每一个class
    classes = [r[r.find(" ") + 1:].split(",") for r in rows]
    # 获得粗略的classes和精细的classes
    rough_classes = [c[0] for c in classes]


    return rough_classes

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

# 读取测试图片
def test_images(path):
    image_paths = [os.path.join(path,f) for f in os.listdir(path)]
    return image_paths

# 图像的预处理（单张图片）
def preprocess_image(image_path):
    img_data=cv2.imread(image_path)
    resized = cv2.resize(img_data, (224, 224))
    # image scalefactor size mean swapRB
    # 这里的blob就是一个len为1的batch,最后一个维度为Imagenet所有图像，RGB的均值，要
    # 减去，去除影响
    blob = cv2.dnn.blobFromImage(resized, 1, (224, 224), (104, 117, 123))
    # The output shape is (1,3,224,224), batch is 1,dim is 3, width and height is 224
    print("First Blob: {}".format(blob.shape))

    return blob

# 利用 Caffe ImageNet的网络进行前向传播
def Caffe_classification_ImageNet(net,inputdata,classes):
    '''
    :param net: loaded Caffe Data 
    :param inputdata: input processed data
    :return: 
    '''
    # 输入数据
    net.setInput(inputdata)
    # 前向传播得到结果，
    preds = net.forward()
    outcome_list=[]
    # 排序，取分类可能性最大的
    for i in range(len(preds)):
        idx=np.argmax(preds[i])
        text = "Label: {}, {:.2f}%".format(classes[idx],
                                           preds[i][idx] * 100)
        outcome_list.append(text)

    return outcome_list
# 在图片上显示最后结果
def show_on_image(image_path,outcome,saved=True):
    '''
    :param image: 把分类结果写在image上面 
    :return: 
    '''
    for i in range(len(image_path)):

        image=cv2.imread(image_path[i])
        cv2.putText(image, outcome[i], (5, 25), cv2.FONT_HERSHEY_SIMPLEX,
                0.7, (0, 255, 0), 2)
        if saved:
            cv2.imwrite("Test{}.png".format(i),image)
        # 显示
        cv2.imshow("Image", image)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

#  图像预处理，批量的图片
def preprocess_images(imagelists_path):
    # 载入图片
    batch_image=[]
    for img in imagelists_path:
        img_data =cv2.imread(img)
        img_data =cv2.resize(img_data,(224,224))
        batch_image.append(img_data)

    # batch_images
    batch_images_caffe= cv2.dnn.blobFromImages(batch_image,1,(224,224),(104, 117, 123))


    return  batch_images_caffe



# Test the caffe model
if __name__ == '__main__':

    # load the caffe_net structure and weights
    net = read_caffeNet_structure_and_weights(caffeNet_structure_path="bvlc_googlenet.prototxt",
                                              model_weights_path="bvlc_googlenet.caffemodel")

    # load the classes list
    rough_classes =read_the_label_files('synset_words.txt')


    image_paths = test_images("images")
    blob = preprocess_images(image_paths)

    outcome = Caffe_classification_ImageNet(net=net,inputdata=blob,
                                            classes=rough_classes)
    show_on_image(image_paths,outcome)