/*
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/4/13
 */

#include "hr_sys.h"
#include "hr_run.h"
#include "../tools/regex_match.h"

long date_per_month[13][2]={
        {0,0},
        {31,31},
        {29,28},
        {31,31},
        {30,30},
        {31,31},
        {30,30},
        {31,31},
        {31,31},
        {30,30},
        {31,31},
        {30,30},
        {31,31}
};




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
        //TODO : bugs here--->can not match "query 000001" fix regex expression perhaps.
        if(!regex_match_with(cmd, QUERY_REG)){
                return QUERY;
        }
        //sort by (NAME|PID|WID|DATE|SALARY) (-d|-i)
        if(!regex_match_with(cmd,SORT_REG)){
                return SORT;
        }
        //sort by (NAME|PID|WID|DATE|SALARY)
        if(!regex_match_with(cmd,SORT_DEFAULT_REG)){
                return SORT_DEAF;
        }
        //delete <wid/pid/name>
        if(!regex_match_with(cmd,DELETE_REG)){
                return DELETE;
        }
        if(!regex_match_with(cmd,INSERT_INFO_REG)){
                return INSERT_INFO;
        }
        if(!regex_match_with(cmd,INSERT_COM_REG)){
                return INSERT_COMP;
        }
        return UNKOWN;



}

Position char_rank(const char * rank)
{
        Position p = -1;
        if (strcmp(rank, "BOSS") == 0) {
                p = BOSS;
        } else if (strcmp(rank, "MANAGER") == 0) {
                p = MANAGER;
        } else if (strcmp(rank, "BARTENDER") == 0) {
                p = BARTENDER;
        } else if (strcmp(rank, "COOK") == 0) {
                p = COOK;
        } else if (strcmp(rank, "CLEANER") == 0) {
                p = CLEANER;
        } else if (strcmp(rank, "CASHIER") == 0) {
                p = CASHIER;
        } else if (strcmp(rank, "WAREHOUSEMAN") == 0) {
                p = WAREHOUSEMAN;
        } else if (strcmp(rank, "FINANCE") == 0) {
                p = FINANCE;
        }

        return p;
}

Gender char_gender(const char *gender)
{
        Gender g =-1;
        if (strcmp(gender, "MALE") == 0) {
                g = MALE;
        } else if (strcmp(gender, "FEMALE") == 0) {
                g = FEMALE;
        }
        return g;
}


Field char_field(const char *field)
{
        Field f=-1;
        if(!strcmp(field,"NAME")){
                f=NAME;
        }
        else if(!strcmp(field,"PID")){
                f=PID;
        }
        else if(!strcmp(field,"WID")){
                f=WID;
        }
        else if(!strcmp(field,"DATE")){
                f=DATE;
        }
        else if(!strcmp(field,"SALARY")){
                f=SALARY;
        }
        return f;
}

int check_date(const char *date)
{
        long d = strtol(date,NULL,10);
        long yy=d/10000;
        if(yy>2021 ||yy<2018){
                printf(RED"Incorrect year.Only 2018 to 2021 are permitted.\n"NONE);
                return 1;
        }
        long mm=(d%10000)/100;
        if(!(1<=mm&&mm<=12)){
                printf(RED"Incorrect month.\n"NONE);
                return 2;
        }
        long dd=d%100;
        if(!(1<=dd&&dd<=31)){
                printf(RED"Incorrect day.\n"NONE);
                return 3;
        }

        //leap year
        int idx;
        if(__isleap(yy)){
                idx=0;
        }else{
                idx=1;
        }
        if(dd!=date_per_month[mm][idx]){
                printf("Incorrect day of this month.\n"NONE);
                return 4;
        }

        return 0;
}


void logic_repl()
{
        InputBuffer * input = new_input_buffer();
        while(input!=nullptr){
                print_sign();
                read_input(input);
                //meta command
                char real_cmd[input->input_len+1];
                strcpy(real_cmd,input->buf);
                //if the first blank exists throw it
                if(input->buf[0]==' '){
                        strtok(real_cmd," ");
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
                // real_cmd is like [xxx xxx xxx ...]
                switch (regex_match_cmd(input->buf)) {

                        case SELECT_NAME: {
                                select_name();
                                continue;
                        }
                        case SELECT_PID: {
                                select_pid();
                                continue;
                        }
                        case SELECT_WID: {
                                select_wid();
                                continue;
                        }
                        case SELECT_GENDER:{
                                char *first = strtok(input->buf," ");
                                char *secd = strtok(NULL," ");
                                char *gend = strtok(NULL," ");
                                Gender g= char_gender(gend);
                                // select GENDER *
                                if(g==-1){
                                        select_gender();
                                        continue;
                                }
                                select_by_gender(g);
                                continue;
                        }
                        case SELECT_RANK:{
                                char *first = strtok(input->buf," ");
                                char *secd = strtok(NULL," ");
                                char *rank = strtok(NULL," ");
                                Position r= char_rank(rank);
                                //select RANK *
                                if(r==-1){
                                        select_rank();
                                        continue;
                                }
                                select_by_rank(r);
                                continue;
                        }
                        case SELECT_DATE: {
                                select_date();
                                continue;
                        }
                        case SELECT_ALL: {
                                select_all();
                                continue;
                        }
                        //  query  <index>                       : query by index
                        //                                         [available index]: <Name>
                        //                                                            <Pid>
                        //                                                            <Wid>
                        case QUERY:{
                                char *first = strtok(input->buf," ");
                                char *index = strtok(NULL," ");
                                Staff *target;
                                if(isdigit(index[0])){
                                        size_t len = strlen(index);
                                        if(len==6){
                                                target = query_by_wid(index);
                                                if(target){
                                                        show_a_query_info(target);
                                                }

                                        }
                                        else if(len == 14){
                                                target = query_by_pid(index);
                                                if(target){
                                                        show_a_query_info(target);
                                                }
                                        }
                                }
                                else{
                                        target= query_by_name(index);
                                        if(target){
                                                show_a_query_info(target);
                                        }
                                }
                                continue;

                        }
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
                        case SORT:{
                                char *first = strtok(input->buf," ");
                                char *secd = strtok(NULL," ");
                                char *field = strtok(NULL," ");
                                char *direc = strtok(NULL," ");
                                Field f= char_field(field);
                                int d=0;
                                if(direc[2]=='i'){
                                        d=0;
                                }
                                else{
                                        d=1;
                                }
                                sort_by(f,d);
                                continue;
                        }
                        // -i specified
                        case SORT_DEAF:{
                                char *first = strtok(input->buf," ");
                                char *secd = strtok(NULL," ");
                                char *field = strtok(NULL," ");
                                Field f= char_field(field);
                                int d=0;
                                sort_by(f,d);
                                continue;
                        }
                        //                                         [sample]: query YangYang
                        //  delete <index>                       : delete a staff with index
                        //                                         [available index]: <Name>
                        //                                                            <Pid>
                        //                                                            <Wid>
                        //                                         [sample]: delete YangYang
                        case DELETE:{
                                char *first = strtok(input->buf," ");
                                char *index = strtok(NULL," ");
                                Staff *target;
                                if(isdigit(index[0])){
                                        size_t len = strlen(index);
                                        //wid
                                        if(len==6){
                                                target = query_by_wid(index);
                                                if(target){
                                                        _remove_worker(target);
                                                }

                                        }
                                        //pid
                                        else if(len == 14){
                                                target = query_by_pid(index);
                                                if(target){
                                                        _remove_worker(target);

                                                }
                                        }
                                }
                                //name
                                else{
                                        target= query_by_name(index);
                                        if(target){
                                                _remove_worker(target);
                                        }
                                }
                                continue;
                        }
                        //  insert info <Name> <Hire date> <Gender> <Rank> <MPL> <Pid> <Wid> <Salary>
                        //  insert comp <Wid>  <complaint message>
                        //TODO : check date and other field.
                        case INSERT_INFO: {

                                char *inset = strtok(input->buf, " ");
                                char *info = strtok(NULL, " ");
                                char *name = strtok(NULL, " ");
                                char *date = strtok(NULL, " ");
                                if (check_date(date) != 0) {
                                        continue;
                                }
                                char *gender = strtok(NULL, " ");
                                char *rank = strtok(NULL, " ");
                                char *mpl = strtok(NULL, " ");
                                char *pid = strtok(NULL, " ");
                                char *wid = strtok(NULL, " ");
                                char *salary = strtok(NULL, " ");
                                if(salary[0]=='0'){
                                        printf(RED"Incorrect salary.\n"NONE);
                                        continue;
                                }
                                insert_worker(name,date,gender,rank,mpl,pid,wid,salary);
                                continue;
                        }
                        case INSERT_COMP:{
                                char *inset = strtok(input->buf, " ");
                                char *comp = strtok(NULL, " ");
                                char *wid = strtok(NULL, " ");
                                char *info = strtok(NULL, " ");
                                add_complaint(wid,info);

                        }
                        case UNKOWN:
                                printf("Unrecognized command '%s'\n", input->buf);
                                continue;
                }

        }
}


