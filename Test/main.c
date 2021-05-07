/* Main schedule program
 * Test/main.c
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/5/5
 */

#include "../sys_main.h"


char *const argv_hr[]={HR_EXE,NULL};
char *const argv_main[]={MAIN_EXE,NULL};
char *const argv_store[]={STORE_EXE, NULL};
char *const argv_fi[]={FI_EXE,NULL};

typedef char*const* argv_t ;
argv_t argv[]={
        argv_hr,
        argv_main,
        argv_store,
        argv_fi
};

void print_dispatchsys_info(void)
{
        char *buf = ordinary_time();
        printf(""
               "*--------------------------------------------------------*\n"
               "| DISPATCH  version  %s                 |\n"
               "| MIT License                                            |\n"
               "| https://github.com/Elio-yang/C-Course-Design           |\n"
               "| Copyright (c) 2021 Elio-yang  alone-yue jakiejoe       |\n"
               "*--------------------------------------------------------*\n"
               "<Enter> for usage hints.\n", buf);
}

void execute(char *const argv_e[])
{
        int pid;
        int existstatus;
        pid=fork();
        switch (pid) {
                case -1:
                        perror("fork failed.\n");
                        exit(1);
                case 0:
                        execv(argv_e[0],argv_e);
                        perror("execv error\n");
                        exit(1);
                default:
                        while (wait(&existstatus)!=pid){;}
                        printf("process %s exited with status %d,%d\n",
                               argv_e[0],existstatus>>8,existstatus&0377);
        }
}


int main()
{

        printf(BOLD"*----------------------------------------------------*\n"NONE
               BOLD"|  "BLINK UNDERLINE"DISPATCH Program Started"NONE"                          |\n"NONE
               BOLD"*----------------------------------------------------*\n\n"NONE);
        print_dispatchsys_info();
        InputBuffer *inputBuffer=new_input_buffer();
        while(inputBuffer!=nullptr){
                printf(GREEN BOLD"wyz-bar@shell "NONE"$ ");
                read_input(inputBuffer);
                switch (regex_match_cmd(inputBuffer->buf)) {
                        case HR_E:{
                                execute(argv[0]);
                                continue;
                        }
                        case MAIN_E:{
                                execute(argv[1]);
                                continue;
                        }
                        case STORE_E:{
                                execute(argv[2]);
                                continue;
                        }
                        case FI_E:{
                                execute(argv[3]);
                                continue;
                        }
                        case UNKOWN:{
                                printf("Unrecognized command '%s'\n", inputBuffer->buf);
                                printf(REVERSE BOLD""
                                       " <HR>    to schedule human resource system.     \n"
                                       " <MAIN>  to schedule order system.              \n"
                                       " <STORE> to schedule store test.                \n"
                                       " <FI>    to schedule financial system.          \n"
                                       " quit    to quit the system.                    \n"NONE NONE);

                                continue;
                        }
                        case QUIT:{
                                exit(0);
                        }
                }
        }
}
