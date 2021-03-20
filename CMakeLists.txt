cmake_minimum_required(VERSION 3.17)
project(CDesign C)

set(CMAKE_C_STANDARD 99)

#可执行文件放在目录 bin下
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(CDesign
        hr_sys.h
        menu.h
        test_main.c)
