cmake_minimum_required(VERSION 3.5)

project(rfcpp2047 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(rfcpp
    rfcpp/base64.h
    rfcpp/rfc2045.cpp
    rfcpp/rfc2045.h
    rfcpp/rfc2047.cpp
    rfcpp/rfc2047.h
    rfcpp/rfc4648.h
)

target_include_directories(rfcpp PRIVATE rfcpp )
target_include_directories(rfcpp PUBLIC . )

add_executable(test examples/test.cpp)
target_link_libraries(test rfcpp)
