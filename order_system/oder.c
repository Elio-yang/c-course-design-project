//All the input must be char and be analyzed later
//使用序号来确定输入，使用strcmp也可以？但是考虑到使用系统的便捷，这里使用了序号来定位
//结构体数组为定位结构体的元素提供了便利，如果需要结点的序号，最好用结构体
//这里需要记录order的数量，修改，删除，order时都需要通过索引号来定位
//非void类型函数的返回值需要被某个变量或者标准输入吸收？？？？？？？
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//TODO : mention path
#define MENU_PATH "C:\\cprogramming\\C-Course-Design\\menu.TXT"
#define warehouse_availble 0
#include "order.h"


int dishes_number; //the amount of the dishes in the menu
int order_number;  //the amount of the dishes of the order list
dish menu[200];
order order_list[200];

int input_int(int *instruction) //if input 0 then quit
{
        char number[100]; //save the number
        int flag = 0;
        int i, len;
        int count = 0;
        while (flag == 0)
        {
                printf("(input '0' to quit)\n");
                scanf("%s", number);
                len = strlen(number);
                for (i = 0; i < len; i++) //if has character not a number
                        if (number[i] - '0' < 0 || number[i] - '0' > 9)
                        {
                                printf("Input error, please input again\n");
                                break;
                        }
                if (i == len)
                        flag = 1;
        }
        if (number[0] == '0' && len == 1)
                return 0;
        else
        {
                for (int i = 0; i < len; i++) //analiyze the input
                {
                        count *= 10;
                        count += number[i] - '0';
                }
        }
        *instruction = count;
        return 1;
}

void get_menu()
{
        FILE *p;
        if ((p = fopen(MENU_PATH, "r")) == NULL)
        {
                printf("Fail to get the menu\n");
                return;
        }
        else
                while (1)
                {
                        fscanf(p, "%[^,],%f,%d", menu[dishes_number].name, &menu[dishes_number].price, &menu[dishes_number].personalization_availble);
                        if (!warehouse_availble) //warehouseinterface1
                                menu[dishes_number].available_number = 1;
                        //            else
                        //                menu[dishes_number].available_number = warehouse_check(menu[dishes_number].name);
                        for (int i = 0; i < menu[dishes_number].personalization_availble; i++) //get the personalization message
                                fscanf(p, "%s", menu[dishes_number].personalization[i]);
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
        for (int i = 0; i < order_number; i++) //print the order
        {
                printf("*%2d.%-36s%-5d%.2fyuan\n", i + 1, order_list[i].name, order_list[i].number, order_list[i].price);
                for (int j = 0; j < order_list[i].personalization_request; i++)
                        printf(" %s\n", order_list[i].personlization[j]);

                aggregate_price += order_list[i].price;
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
void add_dishes() //q:0
{
        int num = 0, taste;
        int individual[100]; //save the index of the requested personliazation
        int index;
        int number; //find out if we have enough number of the dishes
        printf("Please input the index of the dishes you want\n");

        if (!input_int(&index))
        {
                getchar();
                return; //return 0 to directly quit
        }
        while (index < 1 || index > dishes_number) //find out if we have the dishes
        {
                printf("Dishes doesn't exist,Please input again\n");
                if (!input_int(&index))
                {
                        getchar();
                        return; //return -0 to directly quit
                }
        }
        index--; //begin with 0
        printf("Please input the number of the dishes\n");
        if (!input_int(&number))
        {
                getchar();
                return;
        }
        while (number > menu[index].available_number)
        {
                printf("Sorry, we only have %d %s left, Please input again\n", menu[index].available_number, menu[index].name);
                if (!input_int(&number))
                {
                        getchar();
                        return;
                }
        }
        getchar();
        if (menu[index].personalization_availble) //choose the taste
        {
                printf("******************************************************\n"
                       "*The dishes has taste choice followed %s             *\n");
                for (int i = 0; i < menu[index].personalization_availble; i++)
                        printf("*%d.%s                                    *\n", i + 1, menu[index].personalization[i]);
                while (1)
                {
                        printf("Please input the number of the taste you want\n");
                        if (!input_int(&taste))
                        {
                                printf("Fail to get the personalization\n");
                                getchar();
                                return;
                        }
                        getchar();
                        if (taste < 1 || taste > menu[index].personalization_availble)
                        {
                                printf("Taste doesn't exist,Please input again\n");
                                continue;
                        }
                        individual[num++] = taste - 1;
                        printf("Continue or not?(Y/N)\n");

                        if (!confirm())
                                break;
                }
        }

        for (int i = 0; i < num; i++)                   //get the dishes message into the oerder list
                strcpy(order_list[order_number].personlization[i], menu[index].personalization[individual[i]]);
        order_list[order_number].personalization_request = num;
        order_list[order_number].menu = index;
        strcpy(order_list[order_number].name, menu[index].name);
        order_list[order_number].number = number;
        order_list[order_number].price = menu[index].price * number;
        order_number++;
        printf("Add %d %s into the order successfully!\n", number, menu[index].name);
        return;
}
void check()
{
        char instruction[100];
        while (1)
        {
                if (order_number == 0)
                {
                        printf("You don't have any dishes oreded\n");
                        return;
                }
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

void delete_dishes() //success return 1,or return 0
{
        int index;
        printf("Please input the index of the dishes you don't want\n");
        if (!input_int(&index))
        {
                getchar();
                printf("Fail to delete dishes");
                return;
        }
        while (index < 1 || index > order_number) //incorrect input
        {
                printf("Dishes doesn't exist,please input again\n");
                if (!input_int(&index))
                {
                        getchar();
                        printf("Fail to delete dishes");
                        return;
                }
        }
        getchar(); //aborb the empty string from input_int
        printf("Are youe sure you want to delete the dishes?(Y/N)\n");
        if (confirm())
        {
                for (int i = index; i <= order_number; i++)
                        order_list[i - 1] = order_list[i];
                printf("You have successfully delete the %s!\n", order_list[index - 1].name);
                order_number--;
        }
}

void change_order()
{
        int index;
        printf("Please input the index of the dishes you want to change\n");
        if (!input_int(&index))
        {
                getchar();
                return;
        }
        while (index < 1 || index > order_number)
        {
                printf("Dishes doesn't exist,please input again\n");
                if (!input_int(&index))
                {
                        getchar();
                        return;
                }
        }

        getchar(); //aborb the empty string from input_int
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
                                change_order_number(index - 1);
                                break;

                        case 'p':
                                change_order_personalization(index - 1);
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

void change_order_number(int order)
{
        int number;
        int index = order_list[order].menu;
        printf("Please input the number of the dishes\n");
        if (!input_int(&number))
        {
                printf("Fail to change the number\n");
                getchar(); //aborb the return value of input
                return;
        } //fail to get number
        while (number > menu[index].available_number)
        {
                printf("Sorry, we only have %d %s left, Please input again\n", menu[index].available_number, menu[index].name);
                if (!input_int(&number))
                {
                        getchar();
                        printf("Fail to change the number\n");
                        return;
                } //fail to get number
        }
        getchar();
        printf("Are sure you want %d %s?(Y/N)\n", number, order_list[order].name);
        if (confirm())
        {
                order_list[order].number = number;
                printf("Number has been changed successfully!\n");
        }
}

void change_order_personalization(int order)
{
        int index = order_list[order].menu;
        int num = 0, taste;
        int individual[100]; //save the index of the requested personliazation
        if (!menu[index].personalization_availble)
        {
                printf("Personlization option doesn't exist!\n");
                return;
        }

        printf("******************************************************\n"
               "*The dishes has taste choice followed %s             *\n");
        for (int i = 0; i < menu[index].personalization_availble; i++)
                printf("*%d.%s                                    *\n", i + 1, menu[index].personalization[i]);
        printf("Please input the number of the taste you want\n");
        while (1)
        {
                int flag = 0;
                if (!input_int(&taste))
                {
                        printf("Fail to change the personalization\n");
                        return;
                }
                if (taste < 0 || taste > menu[index].personalization_availble)
                {
                        printf("Taste doesn't exist,Please input again\n");
                        continue;
                }
                individual[num++] = taste - 1;
                char instruction[100];
                printf("Continue or not?(Y/N)\n");

                if (!confirm())
                        break;
        }
        printf("Are you sure you want?\n");
        for (int i = 0; i < num; i++)
                printf("%s ", menu[index].personalization[individual[i]]);
        printf("(Y/N)\n");
        if (confirm())
                for (int i = 0; i < num; i++)
                        strcpy(order_list[order].personlization[i], menu[index].personalization[individual[i]]);
}

int finish()
{
        char instruction[100];
        while (1)
        {
                printf("Are you going to confirm(y) your order or change(c) it?\n");
                printf("Input q to go back to instrution interface\n");
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

int confirm()           //Y/N?
{
        char instruction[100];
        while (1)
        {
                gets(instruction);
                if (strlen(instruction) > 1) //incorrect command
                {
                        printf("Instruction doesn't exist,please input again\n");
                        continue;
                }
                switch (instruction[0])
                {
                        case 'Y':
                                return 1;
                        case 'N':
                                return 0;
                        default:
                                printf("Instruction dosen't exist, please input again\n");
                                break;
                }
        }
}