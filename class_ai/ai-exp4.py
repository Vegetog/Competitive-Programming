import tensorflow as tf
from tensorflow.keras import layers, models
import time
import numpy as np
import matplotlib.pyplot as plt

# 数据加载和预处理
(train_images, train_labels), (test_images, test_labels) = tf.keras.datasets.mnist.load_data()
train_images = train_images.reshape((60000, 28, 28, 1)).astype('float32') / 255
test_images = test_images.reshape((10000, 28, 28, 1)).astype('float32') / 255

# 1. LeNet-5模型
def create_lenet():
    model = models.Sequential([
        layers.Conv2D(6, (5, 5), activation='relu', input_shape=(28, 28, 1)),
        layers.MaxPooling2D((2, 2)),
        layers.Conv2D(16, (5, 5), activation='relu'),
        layers.MaxPooling2D((2, 2)),
        layers.Flatten(),
        layers.Dense(120, activation='relu'),
        layers.Dense(84, activation='relu'),
        layers.Dense(10, activation='softmax')
    ])
    return model

# 2. 简化版AlexNet（因为MNIST图像太小，需要调整）
def create_alexnet():
    model = models.Sequential([
        # 输入层
        layers.Input(shape=(28, 28, 1)),  # MNIST 图像是 28x28x1
        
        # 第一个卷积块 - 减小卷积核和步长
        layers.Conv2D(96, 3, strides=1, padding='same', activation='relu'),
        layers.MaxPooling2D(2, strides=2),  # 输出 14x14
        layers.BatchNormalization(),
        
        # 第二个卷积块
        layers.Conv2D(256, 3, padding='same', activation='relu'),
        layers.MaxPooling2D(2, strides=2),  # 输出 7x7
        layers.BatchNormalization(),
        
        # 第三个卷积块
        layers.Conv2D(384, 3, padding='same', activation='relu'),
        layers.BatchNormalization(),
        
        # 第四个卷积块
        layers.Conv2D(384, 3, padding='same', activation='relu'),
        layers.BatchNormalization(),
        
        # 第五个卷积块
        layers.Conv2D(256, 3, padding='same', activation='relu'),
        layers.MaxPooling2D(2, strides=2),  # 输出 3x3
        layers.BatchNormalization(),
        
        # 全连接层
        layers.Flatten(),
        layers.Dense(2048, activation='relu'),  # 减小全连接层的大小
        layers.Dropout(0.5),
        layers.Dense(1024, activation='relu'),  # 减小全连接层的大小
        layers.Dropout(0.5),
        layers.Dense(10, activation='softmax')  # 10个类别（MNIST数据集）
    ])
    
    return model


# 3. 传统BP神经网络
def create_bp_network():
    model = models.Sequential([
        layers.Flatten(input_shape=(28, 28, 1)),
        layers.Dense(512, activation='relu'),
        layers.Dense(256, activation='relu'),
        layers.Dense(10, activation='softmax')
    ])
    return model

# 数据增强
data_augmentation = tf.keras.Sequential([
    layers.RandomRotation(0.1),
    layers.RandomZoom(0.1),
    layers.RandomTranslation(0.1, 0.1)
])

# 评估函数
def evaluate_model(model_fn, model_name, use_augmentation=False):
    model = model_fn()
    model.compile(optimizer='adam',
                 loss='sparse_categorical_crossentropy',
                 metrics=['accuracy'])
    
    # 记录开始时间
    start_time = time.time()
    
    # 训练
    if use_augmentation:
        train_dataset = tf.data.Dataset.from_tensor_slices((train_images, train_labels))
        train_dataset = train_dataset.shuffle(60000).batch(32)
        train_dataset = train_dataset.map(
            lambda x, y: (data_augmentation(x, training=True), y))
        history = model.fit(train_dataset, epochs=10, 
                          validation_data=(test_images, test_labels))
    else:
        history = model.fit(train_images, train_labels, epochs=10,
                          validation_data=(test_images, test_labels))
    
    # 记录训练时间
    training_time = time.time() - start_time
    
    # 测试性能
    start_time = time.time()
    test_loss, test_acc = model.evaluate(test_images, test_labels, verbose=0)
    inference_time = time.time() - start_time
    
    return {
        'model_name': model_name,
        'accuracy': test_acc,
        'training_time': training_time,
        'inference_time': inference_time,
        'history': history.history
    }

# 运行实验
models_to_evaluate = [
    (create_lenet, 'LeNet-5'),
    (create_alexnet, 'AlexNet'),
    (create_bp_network, 'BP Network')
]

results = []
for model_fn, name in models_to_evaluate:
    # 不使用数据增强
    result = evaluate_model(model_fn, f"{name}")
    results.append(result)
    
    # 使用数据增强
    result = evaluate_model(model_fn, f"{name} (with augmentation)", True)
    results.append(result)
