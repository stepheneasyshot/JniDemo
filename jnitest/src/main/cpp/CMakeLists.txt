cmake_minimum_required(VERSION 3.18.1)

project("jni-test")

# 基础的实例demo
# 数据类型，jnienv,javavm，多线程，反射调用，异常处理
add_library(jni-test SHARED
        jni-test.cpp)
target_link_libraries(jni-test
        android
        log)

# cpu亲和性demo，将线程绑定到某颗cpu上进行
add_library(cpu-affinity SHARED
        cpu_affinity.cpp)
target_link_libraries(cpu-affinity
        android
        log)

# 图片模糊demo
add_library(image-blur SHARED
        image_blur.cpp)
target_link_libraries(image-blur
        android
        jnigraphics
        log)