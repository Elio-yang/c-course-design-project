cmake_minimum_required(VERSION 3.10)
project(CDesign C)

set(CMAKE_C_STANDARD 99)

#可执行文件放在目录 bin下
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


SET (TOOL_HEADER
        tools/print_color.h
        tools/process_bar.h
        tools/time_related.h
        tools/quick_sort.h
        menu.h
        )


SET(HEADER
        human_resource_system/hr_repl.h
        human_resource_system/hr_sys.h
        ${TOOL_HEADER}
        )
add_definitions(-std=gnu99)
add_executable(test_hr

        ${HEADER}
        human_resource_system/hr_sys.c
        human_resource_system/hr_repl.c
        tools/quick_sort.c
        Test/test_hr_sys_main.c
        )

add_executable(test_time
        Test/test_time_related_main.c
        )

add_executable(test_menu
        Test/test_menu.c
)