cmake_minimum_required(VERSION 3.24)
project(sc_2023)

set(CMAKE_CXX_STANDARD 20)

add_executable(sc_2023 main.cpp User/User.cpp User/User.h Constants/Constants.cpp Constants/Constants.h Network/Network.cpp Network/Network.h Process/Process.h Process/Process.cpp Simulator/Simulator.cpp Simulator/Simulator.h Generator/UniformGenerator.cpp Generator/UniformGenerator.h Generator/SeedGenerator.cpp Generator/SeedGenerator.cpp Generator/SeedGenerator.h)
