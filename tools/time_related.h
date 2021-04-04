/*
 * tools/time_related.h
 * mainly used for system time related work
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date  2021/4/4
 */


#ifndef CDESIGN_TIME_RELATED_H
#define CDESIGN_TIME_RELATED_H

#include <stdlib.h>
#include <time.h>
#include <string.h>
/* xxxx-xx-xx xx:xx */
typedef struct{
        char yy[4];
        char MM[2];
        char dd[2];
        char hh[2];
        char mm[3];
}Time;

/*      Union structure
 * *-----*----*----*----*------*
 * | yy  | MM | dd | hh | mm \0|
 * *-----*----*----*----*------*
 * |     whole time            |
 * *---------------------------*
 * Union means split time or whole time
 * when you want to get the whole time
 * FormatTime *ft = current_sys_time();
 * char *time_now = ft->whole_time;
 * */
typedef union{
        Time split_time;
        char whole_time[15];
}FormatTime;


#define format_time_len 17

/* return the current system time
 * like this format 202104042208
 * Usage : FormatTime *ft = current_sys_time();
 * */
FormatTime *current_sys_time()
{
        Time * sys_time =(Time *)malloc(sizeof(*sys_time));
        char buf[32];
        time_t this_time = time(NULL);
        struct tm *t=localtime(&this_time);
        strftime(buf,32,"%Y %m %d %H %M",t);
        char *yy = strtok(buf," ");
        char *MM = strtok(NULL," ");
        char *dd = strtok(NULL," ");
        char *hh =strtok(NULL," ");
        char *mm =strtok(NULL," ");

        strcpy(sys_time->yy,yy);
        strcpy(sys_time->yy+4,MM);
        strcpy(sys_time->yy+6,dd);
        strcpy(sys_time->yy+8,hh);
        strcpy(sys_time->yy+10,mm);

        FormatTime *ft=(FormatTime*)malloc(sizeof(*ft));
        memcpy(&ft->split_time,sys_time, sizeof(*sys_time));
        return ft;
}

/* return the formatted time from a FormatTime var pointer
 * like this format : 2021-04-04 22:08 */
char * format_time(FormatTime *ft)
{
        char *format=(char*)malloc(sizeof(char)*format_time_len);
        char *sys_time=ft->whole_time;
        strncpy(format,sys_time,4);
        format[4]='-';
        strncpy(format+5,sys_time+4,2);
        format[7]='-';
        strncpy(format+8,sys_time+6,2);
        format[10]=' ';
        strncpy(format+11,sys_time+8,2);
        format[13]=':';
        strncpy(format+14,sys_time+10,2);
        format[16]='\0';
//        (format[5]!='0')?:(format[5]=' ');
//        (format[8]!='0')?:(format[8]=' ');
        return format;
}




#endif //CDESIGN_TIME_RELATED_H
