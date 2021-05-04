#ifndef _ORDER_H
#define _ORDER_H
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
extern int input_int(int *);                   //analize the int input
extern void get_menu(void);
extern void print_menu(void);
extern void print_order(void);
extern void print_order_interface(void);
extern void add_dishes(void);                  //add a dishes into the oderlist
extern void check(void);                       //check the ordered dishes and conduct some operation
extern void delete_dishes(void);               //delete a dishews
extern void change_order(void);                //change the number or personalization
extern void change_order_number(int);          //change the number of a dishes
extern void change_order_personalization(int); //change the personalization of a dishes
extern int finish(void);                       //quit the system
extern int confirm();                          //confirm user's change delete or exit
extern int warehouse_check(dish);              //warehouse interface1:give a name return the number of the dishes available
extern int warehouse_update(order);            //warehouse interface2:give the order message then update the warehouse return true or false
extern int finance_record(order);              //finance interface:update the order record

#endif