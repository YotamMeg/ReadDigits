cmake_minimum_required(VERSION 3.24)
project(ex4_yotam267)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex4_yotam267
        Activation.h
        Dense.h
        main.cpp
        Matrix.h
        MlpNetwork.h Matrix.cpp Activation.cpp Dense.cpp MlpNetwork.cpp)
