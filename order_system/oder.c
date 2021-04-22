#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dish
{
    char name[50];
    unsigned int price;
    unsigned int available_number;
    int personalization_availble;
    char personalization[100];
    struct dish *next;
} menu[200];

struct order
{
    unsigned int index;
    char name[50];
    unsigned int number;
    unsigned int price;
    char personlization[100];
    struct order *next;
} * order_head; //the head of the order;

int delete_dishes() //success return 1,or return 0
{
    char name[50];
    printf("please input the dishes you don't want\n");
    scanf("%s", name);

    struct order *p = order_head, *q = order_head;
    while (strcmp(p->name, name) != 0 && p != NULL) //find the corresponding dishes
    {
        q = p;
        p = p->next;
    }

    if (p == NULL) //if cannot find the dishes
    {
        printf("dishes doesn't exist\n");
        return 0;
    }
    else
    {
        q->next = p->next;
        free(p);
        return 1;
    }
}
int change_order()
{
    char name[50];
    printf("please input the dishes to change\n");
    scanf("%s", name);

    struct order *p = order_head, *q = order_head;
    while (strcmp(p->name, name) != 0 && p != NULL) //find the corresponding dishes
    {
        q = p;
        p = p->next;
    }

    if (p == NULL) //if cannot find the dishes
    {
        printf("dishes doesn't exist\n");
        return 0;
    }
    else{
        char instruction;
        scanf("%c",instruction);

        switch (instruction)
        {
        case 'c':
            change_order();
            break;
        case 'd':
            delete_dishes();

        default:
            break;
        }
        return 1;
    }
}
void print_order_interface()
{
    //get_menu();
    printf("*you can place an order using the following command:*\n"
           "*a:add a dishes                                     *\n"
           "*c:check your order and change it                   *\n"
           "*q:quit the order interface directly                *\n"
           "*f:check confirm and finish your ordering           *\n");
}
int add_dishes() //需要设计输入，考虑情况
{
    struct order *q, *p = order_head;
    q = (struct order *)malloc(sizeof(struct order));

    printf("input format:index number\n");
    printf("please input the dishes you want\n");
    scanf("%d%d", q->index, q->number);

    while (p->next != NULL) //if p isn't the last one, then move afterwars
        p = p->next;
    p->next = q; //add node at the end of the order list.
    q->next = NULL;
}

void check()
{
    char instruction;
    struct order *p = order_head;
    while (p != NULL)
    {
        printf("%d:%s %d %s %d\n", p->index, p->name, p->number, p->personlization, p->price);
        p = p->next;
    }
    printf("you can change or delete dishes or quit by 'c'(change) or 'd'(delete) or 'q'(quit) command\n");
    while (1)
    {
        scanf("%c", &instruction);
        switch (instruction)
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
        printf("instuction doesn't exist\n");
            break;
        }
    }
}
int get_menu()
{
    FILE *p;
    if (p = fopen("菜单路径", "r") == NULL)
        printf("fail to get the menu\n");
    else
        while (p != NULL)
        {
        }
    return;
}

int main(void)
{
    print_order_interface();
    order_head = (struct order *)malloc(sizeof(struct order));
    order_head->next = NULL;

    char instruction;
    while (1)
    {
        scanf("%d", &instruction);
        switch (instruction)
        {
        case 'a':
            add_dishes(); //add dishes
            break;
        case 'c':
            check(); //check the whole order
            break;
        case 'f': //check,confrim the order and finish
            finish();
        case 'q':
            return 0; //quit the order interface directly
            break;
        default:
            printf("instuction doesn't exist\n");
            break;
        }
    }
    return 0;
}