/*
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/3/19
 */

// testing part
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
                        "login",
                        NULL
                };
                execv("login",argv);
        }
        wait(&status);
        if(WIFEXITED(status)&&((status & 0x000000ff) != 0)){
                exit_hr_sys();
        }else {
                logic_repl();
        }
        return 0;
}