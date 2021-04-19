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
        get_authority();
        logic_repl();


        process_bar("Loading hr system");
        Staff *staff = query_by_name("YANGYANG");
        switch_to_hr_sys(staff);

        select_all();
        printf("***\n");
        select_name();
        printf("***\n");
        select_gender();
        printf("***\n");
        select_by_gender(MALE);
        printf("***\n");
        select_by_rank(BOSS);
        printf("***fork_test\n");


        sort_by(NAME, 0);
        printf("***\n");
        sort_by(PID, 0);
        printf("***\n");
        sort_by(WID, 0);
        printf("***\n");
        sort_by(DATE, 0);
        printf("***\n");
        sort_by(SALARY, 0);


        exit_hr_sys();
        return 0;
}