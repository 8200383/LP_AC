cmake_minimum_required(VERSION 3.17)
project(LP C)

set(CMAKE_C_STANDARD 99)

add_executable(LP src/main.c src/util.c src/util.h src/irs.c src/irs.h src/strs.h src/colors.h src/menu.h src/menu.c src/h_error.c src/h_error.h)