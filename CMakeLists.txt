cmake_minimum_required(VERSION 3.10)
project(CDesign C)

set(CMAKE_C_STANDARD 99)

#可执行文件放在目录 bin下
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


SET (TOOL_HEADER
        tools/print_color.h
        tools/process_bar.h
        tools/time_related.h
        menu.h
        )


SET(HEADER
        hr_sys.h
        ${TOOL_HEADER}
        )
add_executable(test_hr

        ${HEADER}
        Test/test_hr_sys_main.c)

add_executable(test_time
        Test/test_time_related_main.c
        )

add_executable(test_menu
        Test/test_menu.c
)