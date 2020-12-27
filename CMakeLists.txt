cmake_minimum_required(VERSION 3.17)
project(LP C)

set(CMAKE_C_STANDARD 11)

add_executable(LP src/main.c src/main.h src/util.c src/util.h src/irs.c src/irs.h src/strs.h src/colors.h src/menu.h src/menu.c src/paths.h src/error.c src/error.h src/seg_social.c src/seg_social.h src/calendar.c src/calendar.h src/employees.c src/employees.h)