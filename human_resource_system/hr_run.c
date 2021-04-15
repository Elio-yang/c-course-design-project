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
                        fprintf(stderr,"Must supply a .txt filename.\n");
                        return META_COMMAND_FAIL;
                }

                int status = match_pattern(filename,txt_file_reg);
                if(status==-1){
                        fprintf(stderr,"Must supply a .txt filename.\n");
                        return META_COMMAND_FAIL;
                }

                sync_hr_sys();
                load_hr_file(filename);
                return META_COMMAND_SUCCESS;
        }

        return META_COMMAND_UNRECOGNIZED_COMMAND;
}



void logic_repl()
{
        InputBuffer * input = new_input_buffer();
        while(input!=nullptr){
                print_sign();
                read_input(input);
                //meta command
                if (input->buf[0]=='.'){
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
        }
}


