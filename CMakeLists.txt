cmake_minimum_required(VERSION 3.10)
project(main)

set(CMAKE_CXX_STANDARD 14)

# TENSORFLOW #
set(REQUIRED_LIBS ${TFLITE_LIBS})

# OPENCV (4 minimum required)#
find_package(OpenCV 4 REQUIRED)

find_package(Threads REQUIRED)

# LIBMOSQUITTO #
find_library(MOSQUITTO_LIBS mosquitto "lib")

# TENSORFLOW #
find_library(TFLITE_LIBRARY tensorflow-lite "lib")
# TENSORFLOW - FLATBUFFER#
find_library(FLATBUFFER_LIBRARY flatbuffers "lib")

include_directories("include")

set(REQUIRED_LIBS "stdc++fs")
list(APPEND REQUIRED_LIBS ${TFLITE_LIBRARY})
list(APPEND REQUIRED_LIBS ${FLATBUFFER_LIBRARY})
list(APPEND REQUIRED_LIBS ${OpenCV_LIBS})
list(APPEND REQUIRED_LIBS ${Threads_LIBS})
list(APPEND REQUIRED_LIBS ${MOSQUITTO_LIBS})

set(CMAKE_C_FLAGS "-pthread")

add_executable("main"
        src/main.cpp
        src/centroidtracker.cpp
        src/publisher.cpp
        src/image_ops.cpp
        include/publisher.h
        include/image_ops.h
        include/tensorflow_clss.h
        include/centroidtracker.h)

SET_TARGET_PROPERTIES(main PROPERTIES LINK_FLAGS "-no-pie")

# '-ldl' for Raspberry Pi compile
target_link_libraries("main" ${REQUIRED_LIBS} -lpthread -ldl -lmosquitto)
