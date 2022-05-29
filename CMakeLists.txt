cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(PROJECT_NAME TIC-TAC-TOE)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} src/main.cpp src/Header.h src/func.cpp)