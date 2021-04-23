#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int dishes_number; //the amount of the dishes
typedef struct dish
{
    char name[50];
    float price;
    unsigned int available_number;
    int personalization_availble; //how many persoalized choice do i have?
    char personalization[20][100];
} dish;


typedef struct order
{
    unsigned int index;
    char name[50];
    unsigned int number;
    float price;
    char personlization[20][100]; //add space after each personlized choice
    struct order *next;
}order; 
extern int delete_dishes();
extern int change_order();
extern void print_order_interface();
extern int add_dishes();
extern void check();
extern void get_menu();
extern int finish()