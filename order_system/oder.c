#include "order.h"
int a;

dish menu[200];
order *order_head; //the head of the order;

int delete_dishes() //success return 1,or return 0
{
    char name[50];
    printf("please input the dishes you don't want\n");
    scanf("%s", name);

    order *p = order_head, *q = order_head;
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

    order *p = order_head, *q = order_head;
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
        char instruction;
        printf("you can change the number or the personalization of the dishes by the command 'c' or 'p'\n");
        scanf("%c", instruction);

        switch (instruction)
        {
        case 'n':
            printf("please input the number again\n");
            scanf("%d", p->number);
            break;

        case 'p':
            printf("%s", p->personlization);
            printf("please choose the taste again\n");
            scanf("%d", p->number);
            break;

        default:
            printf("instruction doesn't exist");
            break;
        }
        return 1;
    }
}
void print_order_interface()
{
    //get_menu();
    printf("*********************instructions*********************\n"
           "*you can place an order using the following command: *\n"
           "*a:add a dishes                                      *\n"
           "*c:check your order and change it                    *\n"
           "*q:quit the order interface directly                 *\n"
           "*f:check confirm and finish your ordering            *\n");
}

int add_dishes() //需要设计输入，考虑情况
{
    unsigned int index;
    unsigned int number; //find out if we have enough number of the dishes
    char taste[100];
    printf("please input the index of the dishes you want\n");
    scanf("%d", &index);
    if (index < 1 || index > dishes_number) //find out if we have the dishes
    {
        printf("dishes doesn't exist\n");
        return 0;
    }
    else
    {
        printf("please input the number of the dishes\n");
        scanf("%d", &number);
        while (number > menu[index - 1].available_number)
        {
            printf("sorry, we only have %d %s left\n, please input again", &menu[index - 1].available_number, &menu[index - 1].name);
            scanf("%d", &number);
        }
        if (menu[index - 1].personalization_availble)
        {
            printf("the dishes has taste choice followed %s\n", menu[index].personalization); //??
            printf("please input the taste you want");
            while (1)
            {
                char choice[20];
                unsigned int i;
                scanf("%s", choice);

                for (i = 0; i < menu[index - 1].personalization_availble; i++)
                    if (strcmp(menu[index - 1].personalization[i], choice) == 0)
                        break;
                if (i < menu[index - 1].personalization_availble)
                {
                    strcat(taste, choice);

                    char insturcution;
                    printf("continue(c) or quit(q)?\n");
                    scanf("%c", &insturcution);
                    if (insturcution == 'q')
                        break;
                    else
                    {
                        char insturcution;
                        printf("taste doesn't exist\n"
                               "continue(c) or quit(q)?");
                        scanf("%c", &insturcution);
                        if (insturcution == 'q')
                            return -1;
                    }
                }
            }
        }
    }

    order *q, *p = order_head;
    q = (order *)malloc(sizeof(order));
    q->index = index;
    strcpy(q->name, menu[index - 1].name);
    q->number = number;
    q->price = menu[index - 1].price;
    strcpy(q->personlization[], taste);

    while (p->next != NULL) //if p isn't the last one, then move afterwars
        p = p->next;
    p->next = q; //add node at the end of the order list.
    q->next = NULL;
    return 1;
}

void check()
{
    order *p = order_head;
    while (p != NULL) //print the order
    {
        printf("%d:%s %d %s %d\n", p->index, p->name, p->number, p->personlization, p->price);
        p = p->next;
    }

    char instruction;
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
void get_menu()
{
    FILE *p;
    if (p = fopen("C:\\cprogramming\\C-Course-Design\\menu.TXT", "r") == NULL)
        {
            printf("fail to get the menu\n");
            return 0;
        }
    else
        while (!feof(p))
        {
            fscanf(p, "%[^,],%f,%d", menu[dishes_number].name, &menu[dishes_number].price, &menu[dishes_number].personalization_availble);
            menu[dishes_number].available_number = warehouse_check(menu[dishes_number].name);
            for(int i=0;i<menu[dishes_number].personalization_availble;i++)                                           //regular expression
                fscanf(p,"%[^\s]",menu[dishes_number].personalization[i]);
            printf("%s %.2f",menu[dishes_number].name,menu[dishes_number].price);
            dishes_number++;
        }
}

int finish()
{
    order *p = order_head;
    while (p != NULL) //print the order
    {
        printf("%d:%s %d %s %d\n", p->index, p->name, p->number, p->personlization, p->price);
        p = p->next;
    }
    return 1;
}

int main(void)
{
    print_order_interface();
    order_head = (order *)malloc(sizeof(order));
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
        case 'f':              //check,confrim the order and finish
            if (finish() == 1) //if user decides to finish then update the ware house and quit
            {
                warehouse_update(order_head);
                return 1;
            }
            break;
        case 'q':
            return 0; //quit the order interface directly
            break;
        default:
            printf("instuction doesn't exist\n");
            break;
        }
    }
}