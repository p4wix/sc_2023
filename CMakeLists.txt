cmake_minimum_required(VERSION 3.24)
project(sc_2023)

set(CMAKE_CXX_STANDARD 20)

add_executable(sc_2023 main.cpp User/User.cpp User/User.h BaseStation/BaseStation.cpp BaseStation/BaseStation.h Constants/Constants.cpp Constants/Constants.h Network/Network.cpp Network/Network.h)
