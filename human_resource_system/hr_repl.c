/*
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/4/13
 */

#include <stdio.h>
#include <unistd.h>
#include "hr_repl.h"
#include "../tools/time_related.h"


InputBuffer *new_input_buffer()
{
        InputBuffer *new_buffer = (InputBuffer *) malloc(sizeof(*new_buffer));
        new_buffer->buf = nullptr;
        new_buffer->buf_len = 0;
        new_buffer->input_len = 0;
        return new_buffer;
}

void print_sign(void)
{
        printf(GREEN BOLD"wyz-bar@hr "NONE"$ ");
}

void read_input(InputBuffer *input_buffer)
{
        ssize_t bytes_read =
                getline(&(input_buffer->buf), &(input_buffer->buf_len), stdin);
        if (bytes_read < 0) {
                printf("Error reading input\n");
                exit(EXIT_FAILURE);
        }
        input_buffer->input_len = bytes_read - 1;
        input_buffer->buf[bytes_read - 1] = '\0';
}

void print_hrsys_info(void)
{
        char *buf = ordinary_time();
        printf(""
               "*--------------------------------------------------------*\n"
               "| HR-system version  %s                 |\n"
               "| MIT License                                            |\n"
               "| https://github.com/Elio-yang/C-Course-Design           |\n"
               "| Copyright (c) 2021 Elio-yang  alone-yue jakiejoe       |\n"
               "*--------------------------------------------------------*\n"
               "Enter \".help\" for usage hints.\n", buf);
        print_init();
}

void print_help(void)
{
        printf(REVERSE
               "Options:                                                                                        \n"
               "  .load <filename>                     : open & load a .txt file                                \n"
               "  .exit                                : exits hr_sys                                           \n"
               "  .sync                                : synchronize with disk file                             \n"
               "  select *                             : show all information                                   \n"
               "  select <field>                       : show field specified information                       \n"
               "                                         [available fields]: NAME                               \n"
               "                                                             PID                                \n"
               "                                                             WID                                \n"
               "                                                             GENDER MALE/FEMALE/*               \n"
               "                                                             RANK   BOSS/MANAGER/BARTENDER      \n"
               "                                                                    COOK/CLEANER/CASHIER        \n"
               "                                                                    WAREHOUSEMAN/FINANCE/*      \n"
               "                                                             DATE                               \n"
               "                                         [sample]: select NAME                                  \n"
               "                                                   select GENDER MALE                           \n"
               "  query  <index>                       : query by index                                         \n"
               "                                         [available index]: <Name>                              \n"
               "                                                            <Pid>                               \n"
               "                                                            <Wid>                               \n"
               "                                         [sample]: query YangYang                               \n"
               "  sort by <field> <-d>                 : sort information by field                              \n"
               "                                         [available field]:  NAME                               \n"
               "                                                             PID                                \n"
               "                                                             WID                                \n"
               "                                                             DATE                               \n"
               "                                                             SALARY                             \n"
               "                                         [available direction]: -i   increasing order           \n"
               "                                                                -d   decreasing order           \n"
               "                                         [sample]: sort by NAME -i                              \n"
               "                                         [default]: -i specified                                \n"
               "  delete <index>                       : delete a staff with index                              \n"
               "                                         [available index]: <Name>                              \n"
               "                                                            <Pid>                               \n"
               "                                                            <Wid>                               \n"
               "                                         [sample]: delete YangYang                              \n"
               "  insert info <Name> <Hire date> <Gender> <Rank> <MPL> <Pid> <Wid> <Salary>                     \n"
               "  insert comp <Wid>  <complaint message>                                                        \n"
               "  ps: All inputs are not case-sensitive                                                         \n"
               NONE
        );
}

void print_init(void)
{
        printf("Must input a human resource filename(ended with .txt) first.\n");
}


void set_tty_mode(HOW how)
{
        static struct termios ori_mode;
        static int ori_flag;
        if (how == SAVE) {
                tcgetattr(0, &ori_mode);
                ori_flag = fcntl(0, F_GETFL);
        } else if (how == RECOVERY) {
                tcsetattr(0, TCSANOW, &ori_mode);
                fcntl(0, F_SETFL, ori_flag);
        }
}

void set_no_echo()
{
        struct termios tty_state;
        tcgetattr(0, &tty_state);
        tty_state.c_cflag &= ~(ECHO | ECHOE | ECHOK);
        tcsetattr(0, TCSANOW, &tty_state);
}

int get_response(const char *tips)
{
        int input;
        printf("%s(y/n)\n", tips);
        fflush(stdout);
        while (1) {

                int c;
                while ((c = getchar()) != EOF && strchr("nNyY", c) == NULL) { ;
                }
                input = tolower(c);
                if (input == 'y') {
                        _exit(0);
                }
                if (input == 'n') {
                        return -1;
                }
        }
}

//set char-by-char & nobuf
void set_cr_nbuf()
{
        struct termios tty_state;
        tcgetattr(0, &tty_state);
        tty_state.c_cflag &= ~ICANON;
        tty_state.c_cc[VMIN] = 1;
        tcsetattr(0, TCSANOW, &tty_state);
}
// set no delay
void set_nodelay()
{
        int flags;
        flags= fcntl(0,F_GETFL);
        flags|=O_NDELAY;
        fcntl(0,F_SETFL,flags);
}