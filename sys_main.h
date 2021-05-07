/*
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/3/20
 */

#ifndef CDESIGN_CREATER_INFO_H
#define CDESIGN_CREATER_INFO_H


#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "./human_resource_system/hr_run.h"
#include "./human_resource_system/hr_repl.h"
#include <sys/wait.h>

#define HR_EXE "aHR_SYS"
#define MAIN_EXE "aMAIN_SYS"
#define STORE_EXE "aSTORE_SYS"
#define FI_EXE "aFI_SYS"



extern void print_dispatchsys_info(void);

#endif //CDESIGN_CREATER_INFO_H
