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
        tools/regex_match.h
        menu.h
        )
SET(HR_HEADER
        human_resource_system/hr_repl.h
        human_resource_system/hr_sys.h
        human_resource_system/hr_run.h
        ${TOOL_HEADER}

        )

SET(HR_SRC
        human_resource_system/hr_sys.c
        human_resource_system/hr_repl.c
        human_resource_system/hr_run.c
        Test/test_hr_sys_main.c
)

SET(TOOL_SRC
        tools/quick_sort.c

)
add_definitions(-std=gnu99 )
link_libraries(pthread)

add_executable(test_hr

        ${HR_HEADER}
        ${HR_SRC}
        ${TOOL_SRC}

        )


add_executable(test_time
        Test/test_time_related_main.c
        )

add_executable(test_menu
        Test/test_menu.c
)

set(RSA_HEADER
        tools/rsa.c
        tools/rsa.h
)
add_executable(login
        human_resource_system/hr_repl.h
        ${RSA_HEADER}
        Test/encryption.c
        human_resource_system/hr_repl.c
        )

add_executable(order
        order_system/oder.c
)