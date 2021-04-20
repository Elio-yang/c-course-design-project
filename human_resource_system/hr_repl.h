/* REPL way to hr system
 *
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/4/13
 */

#ifndef CDESIGN_HR_REPL_H
#define CDESIGN_HR_REPL_H

#include "../tools/print_color.h"
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>

#define nullptr NULL

/* to get user input */
typedef struct {
        char *buf;
        size_t buf_len;
        ssize_t input_len;
}InputBuffer;

typedef enum{
    SAVE,RECOVERY
}HOW;

extern InputBuffer *new_input_buffer(void);
extern void read_input(InputBuffer *input_buffer);
extern void print_help(void);
extern void print_sign(void);
extern void print_hrsys_info(void);
extern void print_init(void);

extern void set_tty_mode(HOW how);
extern void set_no_echo();
extern int get_response(const char *tips);
extern void set_cr_nbuf();
extern void set_nodelay();





#endif //CDESIGN_HR_REPL_H
