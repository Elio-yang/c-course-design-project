/*
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/4/13
 */

#ifndef CDESIGN_HR_RUN_H
#define CDESIGN_HR_RUN_H


#include "hr_run.h"
#include "hr_repl.h"
#include "hr_sys.h"

typedef enum {
        META_COMMAND_SUCCESS,
        META_COMMAND_UNRECOGNIZED_COMMAND,
        META_OPEN_SUCCESS
} Meta_command_result;

typedef enum {
        PREPARE_SUCCESS,
        PREPARE_UNRECOGNIZED_STATEMENT,
        PREPARE_SYNTAX_ERROR,
        PREPARE_STRING_TOO_LONG,
        PREPARE_NEGATIVE_ID
} Prepare_result;

typedef enum {
        EXECUTE_SUCCESS,EXECUTE_TABLE_FULL,UNKOWN
}Execute_result;


extern void logic_repl();



#endif //CDESIGN_HR_RUN_H
