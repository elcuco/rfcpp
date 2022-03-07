cmake_minimum_required(VERSION 3.5)

project(rfcpp2047 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(rfcpp
    base64.h
    rfc2045.cpp
    rfc2045.h
    rfc2047.cpp
    rfc2047.h
    rfc4648.h
)

add_executable(test main.cpp)
target_link_libraries(test rfcpp)
