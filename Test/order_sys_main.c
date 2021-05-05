/*
 * @author WangJ YangY
 * @email  jluelioyang2001@gamil.com
 * @date 2021/5/4
 */
#include "../order_system/order.h"

int main(void)
{
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
                                        //             if (warehouse_availble)
                                        //                 warehouse_update(order_list);
                                        return 1;
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
}
