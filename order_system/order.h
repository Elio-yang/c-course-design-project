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