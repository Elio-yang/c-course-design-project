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
        EXECUTE_SUCCESS, EXECUTE_TABLE_FULL, UNKOWN_STATEMENT
} Execute_result;

typedef enum {
        SELECT_NAME,
        SELECT_PID,
        SELECT_WID,
        SELECT_GENDER,
        SELECT_RANK,
        SELECT_DATE,
        SELECT_ALL,

        QUERY,
        SORT,
        DELETE,
        INSERT_INFO,
        INSERT_COMP,
        UNKOWN
} Cmd_type;

extern void logic_repl();

extern Meta_command_result do_meta_command(InputBuffer *inputBuffer);


#endif //CDESIGN_HR_RUN_H