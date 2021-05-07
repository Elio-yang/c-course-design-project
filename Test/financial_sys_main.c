/*
 * Test/financial_sys_main.c
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/5/6
 */

#include "../financial_system/financial.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../human_resource_system/hr_repl.h"
#include "../tools/regex_match.h"
#include "../human_resource_system/hr_run.h"
int main()
{
        init_fi_sys();
        print_fisys_info();
        InputBuffer *inputBuffer=new_input_buffer();
        while (inputBuffer!=nullptr){
                printf(GREEN BOLD"wyz-bar@financial "NONE"$ ");
                read_input(inputBuffer);
                switch (regex_match_cmd(inputBuffer->buf)) {
                        case ONE:{
                                print_financial_recd();
                                continue;
                        }
                        case TWO:{
                                printf("\nPlease input a id in the form of xxxxxxxxxxxx:\nid=");
                                InputBuffer *in2=new_input_buffer();
                                read_input(in2);
                                if(regex_match_with(in2->buf,ID_TIME)==0){
                                        char *time =strtok(in2->buf," ");
                                        char *space = strtok(NULL," ");
                                        query_finance(time);
                                        continue;
                                }
                                printf("ID form not correct.\n");
                                continue;

                        }
                        case THREE:{
                                printf("\nPlease input the start time:\n"
                                       "start time =");
                                InputBuffer *time1=new_input_buffer();
                                read_input(time1);
                                printf("\nPlease input the end time:\n"
                                       "end time =");
                                InputBuffer *time2=new_input_buffer();
                                read_input(time2);
                                if(regex_match_with(time1->buf,ID_TIME)==0 && regex_match_with(time2->buf,ID_TIME)==0){
                                        char *index1= strtok(time1->buf," ");
                                        char *s1= strtok(NULL," ");

                                        char *index2= strtok(time2->buf," ");
                                        char *s2= strtok(NULL," ");

                                        query_from(index1,index2);
                                        continue;
                                }
                                printf("Time form not correct.\n");
                                continue;
                        }
                        case FOUR:{
                                //name price time id
                                printf("\nPlease input information: <Name> <Costs(xxx.xx)> <Type(0|1|2)> \n");
                                InputBuffer *info=new_input_buffer();
                                read_input(info);
                                if(regex_match_with(info->buf,MATCH_FINFO_REG)==0){
                                        char *name = strtok(info->buf," ");
                                        char *Cost = strtok(NULL," ");
                                        char *type = strtok(NULL," ");
                                        char *time = strtok(NULL," ");
                                        char *s = strtok(NULL," ");
                                        update_finance_record(name,Cost, atoi(type));
                                }
                                else{
                                        printf("Incorrect info form\n");

                                }
                                continue;
                        }
                        case FIVE:{
                                printf("Please input record type (0 for Order,1 for Store, 2 for HR):");
                                InputBuffer *recd_t =new_input_buffer();
                                read_input(recd_t);
                                DealType t;
                                if(regex_match_with(recd_t->buf,NUM_ZERO)==0){
                                        t=ORDER;
                                }
                                else if(regex_match_with(recd_t->buf,NUM_ONE)==0){
                                        t=INPUT;
                                }
                                else if(regex_match_with(recd_t->buf,NUM_TWO)==0){
                                        t=HR;
                                }
                                else{
                                        printf("Type not support.\n");
                                        continue;
                                }

                                printf("Please input sort which field (0 for Name,1 for ID, 2 for Costs):");
                                InputBuffer *recd_f=new_input_buffer();
                                read_input(recd_f);
                                int f;
                                if(regex_match_with(recd_f->buf,NUM_ZERO)==0){
                                        f=0;
                                }
                                else if(regex_match_with(recd_f->buf,NUM_ONE)==0){
                                        f=1;
                                }
                                else if(regex_match_with(recd_f->buf,NUM_TWO)==0){
                                        f=2;
                                }
                                else{
                                        printf("Field not support.\n");
                                        continue;
                                }

                                printf("Please input sort direction(0 for increase,1 for decrease):");
                                InputBuffer *recd_d =new_input_buffer();
                                read_input(recd_d);
                                int d;
                                if(regex_match_with(recd_d->buf,NUM_ZERO)==0){
                                        d=0;
                                }
                                else if(regex_match_with(recd_d->buf,NUM_ONE)==0){
                                        d=1;
                                }
                                else{
                                        printf("Direction not support.\n");
                                        continue;
                                }
                                sort_data_by(t,f,d);
                                continue;
                        }
                        case SIX:{
                                statistic();
                                continue;
                        }
                        case UNKOWN:
                                printf("Unrecognized command '%s'\n", inputBuffer->buf);
                                printf(REVERSE BOLD
                                       "Choose function:                        \n"
                                       "1.print all records                     \n"
                                       "2.print with id                         \n"
                                       "3.print between id1 and id2             \n"
                                       "4.insert a new record                   \n"
                                       "5.sort the data                         \n"
                                       "6.statistics                            \n"
                                       "quit to exit.                           \n"NONE NONE);
                                continue;
                        case QUIT:{
                                flush_fi_disk();
                                exit(0);
                        }
                }
        }
}