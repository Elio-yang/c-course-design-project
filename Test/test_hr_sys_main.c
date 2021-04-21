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
        int pid;
        if((pid=fork())==0){
                char * const argv[]={
                        "login",
                        NULL
                };
                execv("login",argv);
        }
        wait(&status);
        //be careful of the usage of status
        if(WIFEXITED(status)&&((status & 0x000000ff) != 0)){
                exit_hr_sys();
        }else {
                logic_repl();
        }

        process_bar("Loading hr system");
        Staff *staff = query_by_name("YANGYANG");
        switch_to_hr_sys(staff);

        select_all();
        select_name();
        select_gender();
        select_by_gender(MALE);
        select_by_rank(BOSS);


        sort_by(NAME, 0);
        sort_by(PID, 0);
        sort_by(WID, 0);
        sort_by(DATE, 0);
        sort_by(SALARY, 0);


        exit_hr_sys();
        return 0;
}