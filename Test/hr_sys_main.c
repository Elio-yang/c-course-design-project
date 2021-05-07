/*
 * Test/hr_sys_main.c
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/3/19
 */


#include "../human_resource_system/hr_sys.h"
#include "../human_resource_system/hr_run.h"
#include <pthread.h>

int main()
{
        print_hrsys_info();
        sys_init();
        int status;
        if(!fork()){
                char * const argv[]={
                        "aLOGIN",
                        NULL
                };
                execv("aLOGIN",argv);
        }
        wait(&status);
        if(WIFEXITED(status)&&((status & 0x000000ff) != 0)){
                exit_hr_sys();
        }else {
                logic_repl();
        }
        return 0;
}