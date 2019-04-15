cmake_minimum_required(VERSION 3.13)
project(GBP_Client)

set(CMAKE_CXX_STANDARD 14)

add_executable(GBP_Client Main/main.cpp Client/Client.cpp)