/*
 * @author Yang Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/3/19
 */

#ifndef CDESIGN_PRINT_COLOR_H
#define CDESIGN_PRINT_COLOR_H

/*
 * usage :
 * printf( Effective “str\n” NONE);
 *
 * */

#define NONE                 "\e[0m"
#define BLACK                "\e[0;30m"
/*粗体黑*/
#define L_BLACK              "\e[1;30m"
#define RED                  "\e[0;31m"
#define L_RED                "\e[1;31m"
#define GREEN                "\e[0;32m"
#define L_GREEN              "\e[1;32m"
#define BROWN                "\e[0;33m"
/*粗体黄*/
#define YELLOW               "\e[1;33m"
#define BLUE                 "\e[0;34m"
#define L_BLUE               "\e[1;34m"
#define PURPLE               "\e[0;35m"
#define L_PURPLE             "\e[1;35m"
/*蓝青色*/
#define CYAN                 "\e[0;36m"
#define L_CYAN               "\e[1;36m"
#define GRAY                 "\e[0;37m"
/*粗体黄*/
#define WHITE                "\e[1;37m"
/* 粗体 */
#define BOLD                 "\e[1m"
/* 带下划线 */
#define UNDERLINE            "\e[4m"
/* 频闪 */
#define BLINK                "\e[5m"
/* 背景色反转 */
#define REVERSE              "\e[7m"
#define HIDE                 "\e[8m"
/* 清空屏幕*/
#define CLEAR                "\e[2J"

#endif //CDESIGN_PRINT_COLOR_H
