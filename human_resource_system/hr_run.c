/*
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/4/13
 */


#include "hr_run.h"

void logic_repl()
{
        InputBuffer * input = new_input_buffer();
        do{
                print_sign();
                read_input(input);
                //meta command
                if (input->buf[0]=='.'){

                }
        }while(0);
}


