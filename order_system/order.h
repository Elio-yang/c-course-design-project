#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct dish
{
    char name[50];
    float price;
    int available_number;
    int personalization_availble; //how many persoalized choice do i have?
    char personalization[20][100];
} dish;

typedef struct order
{
        int index;
        int menu;
        char name[50];
        int number;
        float price;
        int personalization_request;
        char personlization[20][100]; //add space after each personlized choice
        struct order *next;
} order;

extern int input_int(int*);
extern void get_menu(void);
extern void print_menu(void);
extern void print_order(void);
extern void print_order_interface(void);
extern void add_dishes(void);
extern void check(void);
extern void delete_dishes(void);
extern void change_order(void);
extern void change_order_number(int);
extern void change_order_personalization(int);
extern int finish(void);
extern int confirm();