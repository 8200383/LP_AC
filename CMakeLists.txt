cmake_minimum_required(VERSION 3.17)
project(LP C)

set(CMAKE_C_STANDARD 99)

add_executable(LP src/main.c src/util.c src/util.h src/table.c src/table.h src/strs.h src/colors.h)