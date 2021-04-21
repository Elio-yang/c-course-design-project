/*
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/4/13
 */

#include "hr_sys.h"
#include "hr_run.h"
#include "../tools/regex_match.h"


Meta_command_result do_meta_command(InputBuffer *inputBuffer)
{
        char *cp_in=(char *) malloc(sizeof(char)*(inputBuffer->input_len+1));
        strcpy(cp_in,inputBuffer->buf);
        char *meta = strtok(cp_in," ");
        if(!strcmp(meta,".exit")){
                exit_hr_sys();
        }

        if(!strcmp(meta,".help")){
                print_help();
                return META_COMMAND_SUCCESS;
        }

        if(!strcmp(meta,".sync")){
                sync_hr_sys();
                return META_COMMAND_SUCCESS;
        }

        if(!strcmp(meta,".load")){
                char *filename= strtok(NULL," ");
                if(filename==nullptr){
                        fprintf(stderr,"Must supply a "BOLD".txt"NONE" filename.\n");
                        return META_COMMAND_FAIL;
                }

                int status = regex_match_with(filename, TXT_FILE_REG);
                if(status==-1){
                        fprintf(stderr,"Must supply a correct "BOLD".txt"NONE" filename(a-zA-Z0-9_.) without any special characters.\n");
                        return META_COMMAND_FAIL;
                }

                sync_hr_sys();
                load_hr_file(filename);
                return META_COMMAND_SUCCESS;
        }

        return META_COMMAND_UNRECOGNIZED_COMMAND;
}

Cmd_type regex_match_cmd(const char *cmd)
{
        //select *
        if(!regex_match_with(cmd,SELECT_All_REG)){
                return SELECT_ALL;
        }
        //select NAME
        if(!regex_match_with(cmd,SELECT_NAME_REG)){
                return SELECT_NAME;
        }
        //select PID
        if(!regex_match_with(cmd,SELECT_PID_REG)){
                return SELECT_PID;
        }
        //select WID
        if(!regex_match_with(cmd,SELECT_WID_REG)){
                return SELECT_WID;
        }
        //select GENDER (MALE/FEMALE)
        if(!regex_match_with(cmd,SELECT_GENDER_REG)){
                return SELECT_GENDER;
        }
        //select RANK (BOSS|MANAGER|BARTENDER|COOK|CLEANER|CASHIER|WAREHOUSEMAN|FINANCE|*)
        if(!regex_match_with(cmd,SELECT_RANK_REG)){
                return SELECT_RANK;
        }
        //select DATE
        if(!regex_match_with(cmd,SELECT_DATE_REG)){
                return SELECT_DATE;
        }
        //query <wid/pid/name>
        if(!regex_match_with(cmd, QUERY_REG)){
                return QUERY;
        }
        //sort by (NAME|PID|WID|DATE|SALARY) (-d|-i)
        if(!regex_match_with(cmd,SORT_REG)){
                return SELECT_PID;
        }
        //delete <wid/pid/name>
        if(!regex_match_with(cmd,DELETE_REG)){
                return DELETE;
        }

        return UNKOWN;



}

Execute_result do_command(InputBuffer *inputBuffer)
{
        char *cp_in=(char*) malloc(sizeof(char)*(inputBuffer->input_len+1));
        strcpy(cp_in,inputBuffer->buf);


}
void logic_repl()
{
        InputBuffer * input = new_input_buffer();
        while(input!=nullptr){
                print_sign();
                read_input(input);
                //meta command
                char *real_cmd=nullptr;
                //if the first blank exists throw it
                if(input->buf[0]==' '){
                        real_cmd= strtok(input->buf," ");
                }else{
                        //blank spaces are delivered
                        real_cmd=input->buf;
                }

                if(*real_cmd==0){
                        // empty cmd
                        continue;
                }
                //do meta cmd
                if (real_cmd[0]=='.'){
                        switch (do_meta_command(input)) {
                                case META_COMMAND_FAIL:
                                case META_COMMAND_SUCCESS:
                                        continue;
                                case META_COMMAND_UNRECOGNIZED_COMMAND:
                                        printf("Unrecognized command '%s'\n", input->buf);
                                        continue;
                                default:
                                        continue;
                        }
                }
//select *                             : show all information
//select <field>                       : show field specified information
//                                        [available fields]:   NAME
//                                                              PID
//                                                              WID
//                                                              GENDER MALE/FEMALE/*
//                                                              RANK   BOSS/MANAGER/BARTENDER
//                                                                    COOK/CLEANER/CASHIER
//                                                                    WAREHOUSEMAN/FINANCE/*
//                                                              DATE
//                                         [sample]: select NAME
//                                                   select GENDER MALE
//  query  <index>                       : query by index
//                                         [available index]: <Name>
//                                                            <Pid>
//                                                            <Wid>
//                                         [sample]: query YangYang
//  sort by <field> <-d>                 : sort information by field
//                                         [available field]:  NAME
//                                                             PID
//                                                             WID
//                                                             DATE
//                                                             SALARY
//                                         [available direction]: -i   increasing order
//                                                                -d   decreasing order
//                                         [sample]: sort by NAME -i
//                                         [default]: -i specified
//  delete <index>                       : delete a staff with index
//                                         [available index]: <Name>
//                                                            <Pid>
//                                                            <Wid>
//                                         [sample]: delete YangYang
//  insert info <Name> <Hire date> <Gender> <Rank> <MPL> <Pid> <Wid> <Salary>
//  insert comp <Wid>  <complaint message>

                // real_cmd is like [xxx xxx xxx ...]
                switch (regex_match_cmd(real_cmd)) {

                        case SELECT_NAME:
                                select_name();
                                continue;
//                        case SELECT_PID:
//                                select_pid();
//                                continue;
//                        case SELECT_WID:
//                                select_wid();
//                                continue;
                        case SELECT_GENDER:
                                select_gender();
                                continue;
                        case SELECT_RANK:{
                                char *first = strtok(input->buf," ");
                                char *secd = strtok(NULL," ");
                                char *rank = strtok(NULL," ");
                                char *four = strtok(NULL," ");
                                Position r;
                                continue;
                        }
//                        case SELECT_DATE:
//                                select_date();
//                                continue;
                        case SELECT_ALL:
                                select_all();
                                continue;
                        case QUERY:
                                break;
                        case SORT:
                                break;
                        case DELETE:
                                break;
                        case INSERT_INFO:
                                break;
                        case INSERT_COMP:
                                break;
                        case UNKOWN:
                                printf("Unrecognized command '%s'\n", input->buf);
                                continue;
                }

        }
}


