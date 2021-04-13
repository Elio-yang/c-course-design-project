/*
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/4/13
 */

#include <stdio.h>
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
        printf("hr > ");
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

void delete_input_buffer(InputBuffer *inputBuffer)
{
        free(inputBuffer->buf);
        free(inputBuffer);
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
}

void print_help(void)
{
        printf("Options:\n"
               "  .open <filename>                     : open & load a .db file\n"
               "  .exit                                : exits SQLdb\n"
               "  .const                               : show related constants\n"
               "  .tree                                : tree visualization\n"
               "  select                               : show all rows\n"
               "  insert <id> <username> <email>       : insert a row record\n"
        );
}
void print_init(void)
{
        printf("Must input a database filename(ended with .db) first.\n");
        printf("filename > :");
}
