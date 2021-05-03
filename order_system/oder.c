#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MENU_PATH "C:\\cprogramming\\C-Course-Design\\menu.TXT"
#define warehouse_availble 1
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

int dishes_number; //the amount of the dishes
int order_number;
dish menu[200];
order *order_head; //the head of the order;
void get_menu()
{
    FILE *p;
    if ((p = fopen(MENU_PATH, "r")) == NULL)
    {
        printf("fail to get the menu\n");
        return;
    }
    else
        while (1)
        {
            fscanf(p, "%[^,],%f,%d", menu[dishes_number].name, &menu[dishes_number].price, &menu[dishes_number].personalization_availble);
            if (!warehouse_availble)
                menu[dishes_number].available_number = 1;
            else
                menu[dishes_number].available_number = warehouse_check(menu[dishes_number].name);
            for (int i = 0; i < menu[dishes_number].personalization_availble; i++) //regular expression
                fscanf(p, "%[^s]", menu[dishes_number].personalization[i]);
            dishes_number++;
            if (feof(p))
                break;
            else
                fgetc(p); //diminish the \n in the end
        }
}
void print_menu()
{
    printf("*************************MENU*************************\n");
    for (int i = 0; i < dishes_number; i++)
        printf("*%2d.%-41s%.2fyuan\n", i + 1, menu[i].name, menu[i].price);
}

void print_order()
{
    printf("**********************ODER_LIST***********************\n");

    int aggregate_price = 0;
    order *p = order_head->next;
    while (p != NULL) //print the order
    {
        printf("*%2d.%-36s%-5d%.2fyuan\n", p->index, p->name, p->number, p->price);
        for (int i = 0; i < p->personalization_request; i++)
            printf(" %s", p->personlization[i]);

        aggregate_price += p->price;
        p = p->next;
    }
    printf("The aggregate price is %dyuan.\n", aggregate_price);
}

void print_order_interface()
{
    printf("*********************INSTRUCTION**********************\n"
           "*You can place an order using the following commands:*\n"
           "*a:Add a dishes                                      *\n"
           "*c:Check your order and change it                    *\n"
           "*q:Quit the order interface directly                 *\n"
           "*f:Check, confirm and finish your ordering           *\n");
}

int input1(int *instruction) //if input 0 then quit
{
    int number;
    printf("(input '0' to quit)\n");
    scanf("%d", &number);
    if (number == 0) //if quit
        return 0;
    else
    {
        *instruction = number;
        return 1;
    }
}

void change_order_number(order *p)
{
    int number;
    printf("Please input the number of the dishes\n");
    if (!input1(&number))
    {
        printf("fail to change the number\n");
        return;
    } //fail to get number
    while (number > menu[p->menu].available_number)
    {
        printf("Sorry, we only have %d %s left, Please input again\n", menu[p->menu].available_number, menu[p->menu].name);
        if (!input1(&number))
        {
            printf("fail to change the number\n");
            return;
        } //fail to get number
    }
    printf("Number has been changed successfully\n");
}

void change_order_personalization(order *p)
{
    int index = p->menu;
    int num = 0, taste;
    int individual[100]; //save the index of the requested personliazation
    if (menu[index].personalization_availble)
    {
        printf("*******************************************\n"
               "*The dishes has taste choice followed %s  *\n");
        for (int i = 0; i < menu[index].personalization_availble; i++)
            printf("*%d.%s                                    *\n", i, menu[index].personalization[i]);
        printf("Please input the number of the taste you want\n");
        while (1)
        {
            int flag = 0;
            if (!input1(&taste))
            {
                printf("fail to change the personalization\n");
                return;
            }
            if (taste < 0 || taste > menu[index].personalization_availble)
                printf("taste doesn't exist,Please input again\n");
            continue;
            individual[num++] = taste;
            char instruction[100];
            while (1)
            {
                printf("continue or not?(Y/N)\n");
                gets(instruction);
                if (strlen(instruction) > 1) //incorrect command
                {
                    printf("Instruction doesn't exist,please input again\n");
                    continue;
                }
                switch (instruction[0])
                {
                case 'Y':
                    flag = 1; //continue
                    break;
                case 'N':
                    flag = 0; //end
                    break;
                default:
                    printf("Instruction dosen't exist, please input again\n");
                    break;
                }
            }
            if (!flag)
                break;
        }
    }
    for (int i = 0; i < num; i++)
        strcpy(p->personlization[i], menu[index].personalization[individual[i]]);
}
int add_dishes() //q:0
{
    int num = 0, taste;
    int individual[100]; //save the index of the requested personliazation
    int index;
    int number; //find out if we have enough number of the dishes
    printf("Please input the index of the dishes you want\n");

    if (!input1(&index))
        return 0;                              //return 0 to directly quit
    while (index < 1 || index > dishes_number) //find out if we have the dishes
    {
        printf("Dishes doesn't exist,Please input again\n");
        if (!input1(&index))
            return 0; //return -0 to directly quit
    }
    index--; //begin with 0
    printf("Please input the number of the dishes\n");
    if (!input1(&number))
        return 0;
    while (number > menu[index].available_number)
    {
        printf("Sorry, we only have %d %s left, Please input again\n", menu[index].available_number, menu[index].name);
        if (!input1(&number))
            return 0;
    }

    if (menu[index].personalization_availble)
    {
        printf("*******************************************\n"
               "*The dishes has taste choice followed %s  *\n");
        for (int i = 0; i < menu[index].personalization_availble; i++)
            printf("*%d.%s                                    *\n", i, menu[index].personalization[i]);
        printf("Please input the number of the taste you want\n");
        while (1)
        {
            int flag = 0;
            if (!input1(&taste))
            {
                printf("fail to change the personalization\n");
                return;
            }
            if (taste < 0 || taste > menu[index].personalization_availble)
                printf("taste doesn't exist,Please input again\n");
            continue;
            individual[num++] = taste;
            char instruction[100];
            while (1)
            {
                printf("continue or not?(Y/N)\n");
                gets(instruction);
                if (strlen(instruction) > 1) //incorrect command
                {
                    printf("Instruction doesn't exist,please input again\n");
                    continue;
                }
                switch (instruction[0])
                {
                case 'Y':
                    flag = 1; //continue
                    break;
                case 'N':
                    flag = 0; //end
                    break;
                default:
                    printf("Instruction dosen't exist, please input again\n");
                    break;
                }
            }
            if (!flag)
                break;
        }
    }

    order *q, *p = order_head;
    q = (order *)malloc(sizeof(order));
    for (int i = 0; i < num; i++)
        strcpy(q->personlization[i], menu[index].personalization[individual[i]]);
    q->index = ++order_number;
    p->menu = index;
    strcpy(q->name, menu[index].name);
    q->number = number;
    q->price = menu[index].price * number;

    while (p->next != NULL) //if p isn't the last one, then move afterwars
        p = p->next;
    p->next = q; //add node at the end of the order list.
    q->next = NULL;
    printf("Add %d %s into the order successfully!\n", number, menu[index].name);
    return 1;
}

void delete_dishes() //success return 1,or return 0
{
    int index;
    printf("Please input the index of the dishes you don't want\n");
    if (!input1(&index))
        return;
    while (index <= 0 || index > order_number) //incorrect input
    {
        printf("Dishes doesn't exist,please input again\n");
        if (!input1(&index))
            return;
    }
    order *p = order_head, *p_front = order_head;
    for (int i = 0; i < index; i++) //find the corresponding dishes
    {
        p_front = p;
        p = p->next;
    }
    getchar(); //aborb the empty string from input1
    char instruction[100];
    while (1)
    {
        printf("Are youe sure you want to delete the dishes?(Y/N)\n");
        gets(instruction);
        if (strlen(instruction) > 1) //incorrect command
        {
            printf("Instruction doesn't exist,please input again\n");
            continue;
        }
        switch (instruction[0])
        {
        case 'Y':
            p_front->next = p->next;
            printf("You hane successfully delete the %s!", p->name);
            free(p);
            return;
        case 'N':
            return;
        default:
            printf("Instruction dosen't exist, please input again\n");
            break;
        }
    }
}

void change_order()
{
    int index;
    printf("Please input the index of the dishes you want to change\n");
    if (!input1(&index))
        return;
    while (index <= 0 || index > order_number)
    {
        printf("Dishes doesn't exist,please input again\n");
        if (!input1(&index))
            return;
    }
    order *p = order_head->next;
    for (int i = 0; i < index; i++) //find the corresponding dishes
        p = p->next;

    getchar(); //aborb the empty string from input1
    char instruction[100];
    while (1)
    {
        printf("You can change the number or the personalization of the dishes by the command 'n' or 'p'\n");
        printf("Input q to quit\n");
        gets(instruction);
        if (strlen(instruction) > 1) //incorrect command
        {
            printf("Instruction doesn't exist,please input again\n");
            continue;
        }
        switch (instruction[0])
        {
        case 'n':
            change_order_number(p);
            getchar();
            break;

        case 'p':
            change_order_personalization(p);
            getchar();
            break;
        case 'q':
            return;
        default:
            printf("Instruction doesn't exist,please input again\n");
            break;
        }
    }
    return;
}

void check()
{
    if (order_head->next == NULL)
    {
        printf("You don't have any dishes oreded\n");
        return;
    }
    char instruction[100];
    while (1)
    {
        print_order();
        printf("You can change or delete dishes by 'c'(change) or 'd'(delete) command\n");
        printf("Input q to quit\n");
        gets(instruction);
        if (strlen(instruction) > 1) //incorrect command
        {
            printf("Instuction doesn't exist,please input again\n");
            continue;
        }
        switch (instruction[0])
        {
        case 'c':
            change_order();
            getchar();
            break;

        case 'd':
            delete_dishes();
            getchar();
            break;

        case 'q':
            return;

        default:
            printf("Instruction doesn't exist, please input again\n");
            break;
        }
    }
}

int finish()
{
    char instruction[100];
    while (1)
    {
        printf("Are you going to confirm(y) your order or change(c) it?\n");
        printf("Input q to quit\n");
        gets(instruction);
        if (strlen(instruction) > 1) //incorrect command
        {
            printf("Instuction doesn't exist,please input again\n");
            continue;
        }
        switch (instruction[0])
        {
        case 'y':
            return 1;
        case 'c':
            check();
            break;
        case 'q':
            return 0;
        default:
            printf("Instuction doesn't existp please input again\n");
            break;
        }
    }
}

int main(void)
{
    get_menu();
    print_menu();
    order_head = (order *)malloc(sizeof(order));
    order_head->next = NULL;

    char instruction[100]; //the command
    while (1)
    {
        print_order_interface();
        gets(instruction);
        if (strlen(instruction) > 1) //incorrect command
        {
            printf("instuction doesn't exist,please input again\n");
            continue;
        }
        switch (instruction[0])
        {
        case 'a':
            add_dishes(); //add dishes
            getchar();    //??
            break;
        case 'c':
            check();   //check the whole order
            getchar(); //??
            break;
        case 'f':              //check,confrim the order and finish
            if (finish() == 1) //if user decides to finish then update the ware house and quit
            {
                if (warehouse_availble)
                    warehouse_update(order_head);
                return 1;
                break;
            case 'q':
                return 0; //quit the order interface directly
                break;
            default:
                printf("Instruction doesn't exist,please input again\n");
                break;
            }
        }
    }
}