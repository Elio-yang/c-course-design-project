#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MENU_PATH "C:\\cprogramming\\C-Course-Design\\menu.TXT"
int dishes_number; //the amount of the dishes
int order_number;
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
    int personalization_request;
    char personlization[20][100]; //add space after each personlized choice
    struct order *next;
} order;
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
            menu[dishes_number].available_number = 1;
            //menu[dishes_number].available_number = warehouse_check(menu[dishes_number].name);
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

order *print_order()
{
    printf("**********************ODER_LIST***********************\n");
    int aggregate_price = 0;
    order *p = order_head->next;
    while (p->next != NULL) //print the order
    {
        printf("%d.%s %d", p->index, p->name, p->number);
        for (int i = 0; i < p->personalization_request; i++)
            printf(" %s", p->personlization[i]);
        printf("%.2fyuan\n", p->price);

        aggregate_price += p->price;
        p = p->next;
    }
    return p;
    printf("The aggregate price is %d\n", aggregate_price);
}

void print_order_interface()
{
    printf("*********************INSTRUCTION**********************\n"
           "*You can place an order using the following commands:*\n"
           "*a:add a dishes                                      *\n"
           "*c:check your order and change it                    *\n"
           "*q:quit the order interface directly                 *\n"
           "*f:check confirm and finish your ordering            *\n");
}

int delete_dishes() //success return 1,or return 0
{
    char name[50];
    printf("Please input the dishes you don't want\n");
    scanf("%s", name);

    order *p = order_head, *q = order_head;
    while (strcmp(p->name, name) != 0 && p != NULL) //find the corresponding dishes
    {
        q = p;
        p = p->next;
    }

    if (p == NULL) //if cannot find the dishes
    {
        printf("Dishes doesn't exist\n");
        return 0;
    }
    else
    {
        q->next = p->next;
        free(p);
        return 1;
    }
}

int input1(int *instruction) //if input 0 then quit
{
    printf("(input '0' to quit)\n");
    scanf("%d", instruction);
    if (*instruction == 0) //if quit
        return 0;
    else
        return 1;
}
int add_dishes() //q:0
{
    int i, num = 0, taste;
    int individual[100];
    int index;
    int number; //find out if we have enough number of the dishes
    printf("Please input the index of the dishes you want\n");

    if (!input1(&index))
        return 0; //return 0 to directly quit

    while (index < 1 || index > dishes_number) //find out if we have the dishes
    {
        printf("Dishes doesn't exist,Please input again\n");
        if (!input1(&index))
            return 0; //return -0 to directly quit
    }
    printf("Please input the number of the dishes\n");
    if (!input1(&number))
        return 0;
    while (number > menu[index - 1].available_number)
    {
        printf("Sorry, we only have %d %s left, Please input again\n", menu[index - 1].available_number, menu[index - 1].name);
        if (!input1(&number))
            return 0;
    }

    if (menu[index - 1].personalization_availble)
    {
        printf("*******************************************\n"
               "*The dishes has taste choice followed %s  *\n");
        for (i = 0; menu[index - 1].personalization_availble; i++)
            printf("*%d.%s                                    *\n", i, menu[index - 1].personalization[i]);
        printf("Please input the number of the taste you want\n");
        while (1)
        {
            if (!input1(&taste))
                return 0;
            if (taste < 0 || taste > i)
                printf("taste doesn't exist,Please input again\n");
            continue;
            individual[num++] = taste;
            printf("continue or quit?\n");
        }
    }

    order *q, *p = order_head;
    q = (order *)malloc(sizeof(order));
    for (int i = 0; i < num; i++)
        strcpy(q->personlization[i], menu[index - 1].personalization[individual[i]]);
    q->index = ++order_number;
    strcpy(q->name, menu[index - 1].name);
    q->number = number;
    q->price = menu[index - 1].price * number;

    while (p->next != NULL) //if p isn't the last one, then move afterwars
        p = p->next;
    p->next = q; //add node at the end of the order list.
    q->next = NULL;
    return 1;
}

int change_order()
{
    int index;
    printf("Please input the index of the dishes you want to change\n");
    if (!input1(index))
        return 0;
    while (index <= 0 || index > order_number)
    {
        printf("Dishes doesn't exist,please input again\n");
        if (!input1(index))
            return 0;
    }
    order *p = order_head, *q = order_head;
    for (int i = 0; i < index - 1; i++) //find the corresponding dishes
    {
        q = p;
        p = p->next;
    }
    char instruction[10];
    while (1)
    {
        printf("you can change the number or the personalization of the dishes by the command 'c' or 'p'\n");
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
            printf("Please input the number again\n");
            scanf("%d", p->number);
            break;

        case 'p':
            printf("%s", p->personlization);
            printf("Please choose the taste again\n");
            scanf("%d", p->number);
            break;

        case 'q':
            return;
        default:
            printf("Instruction doesn't exist,please input again\n");
            break;
        }
    }
    return 1;
}

void change() //check or finish?
{
    char instruction[100];
    while (1)
    {
        printf("You can change or delete dishes by 'c'(change) or 'd'(delete) command\n");
        printf("Input q to quit\n");
        gets(instruction);
        if (strlen(instruction) > 1) //incorrect command
        {
            printf("instuction doesn't exist,please input again\n");
            continue;
        }
        switch (instruction[0])
        {
        case 'c':
            change_order();
            break;

        case 'd':
            delete_dishes();
            break;

        case 'q':
            return;
            
        default:
            printf("Instruction doesn't exist, please input again\n");
            break;
        }
    }
}

void check()
{
    if (order_head->next == NULL)
    {
        printf("You don't have any dishes oreded\n");
        return;
    }
    print_order();
    change();
}

int finish()
{
    char instruction;
    print_order();
    printf("are you going to confirm(q) your order or change(c) it?\n");
    while (1)
    {
        scanf("%c", &instruction);
        switch (instruction)
        {
        case 'q':
            return 1;
            break;
        case 'c':
            change();
            break;
        default:
            printf("instuction doesn't exist\n"
                   "Please input again\n");
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
            break;
        case 'c':
            check(); //check the whole order
            break;
        case 'f':              //check,confrim the order and finish
            if (finish() == 1) //if user decides to finish then update the ware house and quit
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