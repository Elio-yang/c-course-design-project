/*
 * for_cpp/financial.h
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/5/5
 */


#ifndef CDESIGN_FINANCIAL_H
#define CDESIGN_FINANCIAL_H
#include <stdint.h>
#include <stdio.h>
#include "../tools/time_related.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "../tools/time_related.h"
#include "../tools/quick_sort.h"
#include "../tools/print_color.h"
typedef enum {
        ORDER=0,
        INPUT,
        HR
}DealType;

typedef struct fi {
        char name[64];
        char price[32];
        char time[32];
        DealType type;
        struct fi* next;
}Fi_node;

typedef struct fi_info{
        int fd;
        Fi_node *head;
        uint32_t cnt;
        int dirty;
}F_list;
#define FINANCE_FILE "financial.txt"

extern void init_fi_sys();
extern void flush_fi_disk();

extern void update_finance_record(const char *name,const char *price,DealType type);
extern void print_financial_recd();

extern void query_from(const char *id1,const char *id2);
extern void query_finance(const char *id);

extern double double_price(char price[]);
extern void statistic();
extern void sort_data_by(DealType type, int choice,int direction);

extern void print_fisys_info(void);


#endif //CDESIGN_FINANCIAL_H
