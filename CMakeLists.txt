cmake_minimum_required(VERSION 3.17)
project(CDesign C)

set(CMAKE_C_STANDARD 99)

#可执行文件放在目录 bin下
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

SET(HEADER
        hr_sys.h
        menu.h
        process_bar.h
        print_color.h
        )
add_executable(CDesign

        ${HEADER}
        test_main.c)
