/*
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/4/13
 */

#ifndef CDESIGN_HR_RUN_H
#define CDESIGN_HR_RUN_H

typedef enum {
        META_COMMAND_SUCCESS,
        META_COMMAND_UNRECOGNIZED_COMMAND,
        META_COMMAND_FAIL,
} Meta_command_result;

typedef enum {
        PREPARE_SUCCESS,
        PREPARE_UNRECOGNIZED_STATEMENT,
        PREPARE_SYNTAX_ERROR,
        PREPARE_STRING_TOO_LONG,
        PREPARE_NEGATIVE_ID
} Prepare_result;

typedef enum {
        STATEMENT_INSERT,
        STATEMENT_SELECT
} Statement_type;


typedef enum {
        EXECUTE_SUCCESS,EXECUTE_TABLE_FULL,UNKOWN
}Execute_result;



extern void logic_repl();
extern Meta_command_result do_meta_command(InputBuffer*inputBuffer);



#endif //CDESIGN_HR_RUN_H
