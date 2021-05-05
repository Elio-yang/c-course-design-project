#include<stdio.h>
#include "order.h"
#include "store.h"
#include<stdlib.h>
#include<string.h>

int main(void)
{
    GL=(GoodList*)malloc(sizeof(GoodList));
    ML=(MaterialList*)malloc(sizeof(MaterialList));
    RL=(RecordList*)malloc(sizeof(RecordList));
    RLa=(RecordList_arr*)malloc(sizeof(RecordList_arr));
    //!1.将文件读入结构体并将结构体读入链表
    read_struct_file(GL,ML,RLa);
    arr_list(RL,RLa);
    //2.从文件读入进货记录并更新仓库
    add_record_file(RL,ML);

    get_menu();
    print_menu();
    char instruction[100]; //the command
    while (1)
    {
        print_order_interface();
        gets(instruction);
        if (strlen(instruction) > 1) //incorrect command
        {
            printf("Instruction doesn't exist,please input again\n");
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
            {
                    for(int i=0;i<order_number;i++)
                    {
                        order_material(order_list[i].type,order_list[i].name,GL,ML,3);
                        char price[100];
                        sprintf(price,"%f",order_list[i].price);
                        //finance_record(order_list[i].name,price,ORDER);
                    }
                //!7.程序结束将链表写回结构体并写回dat文件
                list_arr(RL,RLa);
                write_dat(GL,ML,RLa);
                printf("Order finish successfully!\n");
                return 1;
            }
            break;
        case 'q':
            printf("Confirm to exit the ordering function(Y/N)?\n");
            if (confirm())
                return 0; //quit the order interface directly
            break;
        default:
            printf("Instruction doesn't exist,please input again\n");
            break;
        }
    }
}