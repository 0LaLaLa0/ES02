cmake_minimum_required(VERSION 3.6)
project(ES02)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -fno-exceptions -Wno-format -fno-rtti -std=c++1y")

set(SOURCE_FILES src/main.cpp src/Printf.cpp include/Printf.h)
add_executable(ES02 ${SOURCE_FILES})