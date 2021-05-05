/*
 * @Author: alone_yue
 * @Date: 2021-04-23 09:18:42
 */
#include<cstdio>
#include<cstdlib>
#include"../store_system/store.hpp"

//!    使用说明
//!    1.ML和GL由createfile执行后再由main执行后会进行初始化,
//!      但是由于程序执行后进货记录会改变ML和GL下一次GL和ML就是更新过后的了，如果想重新开始再执行一次createfile即可
//!    2.arr_list(RL,RLa)函数可以将之前的进货记录重新放到进货链表,如果想完全重新开始记录即可注释掉
int main(){
    GoodList gl;      
    MaterialList ml;
    GoodList* GL=&gl; 
    MaterialList* ML=&ml;
    RecordList rl;
    RecordList* RL=&rl;
    RecordList_arr rla;
    RecordList_arr* RLa=&rla;

    //!1.将文件读入结构体并将结构体读入链表
    read_struct_file(GL,ML,RLa);
    arr_list(RL,RLa);

    //2.从文件读入进货记录并更新仓库
    add_record_file(RL,ML);
    
    //3.根据时间 不知道原来是多少改为新的数量 并更新仓库(要求根据原来的数量和新的数量更新)
    char time[30]; int new_num;
    printf("请要修改记录的时间和改后数量:");
    scanf("%s %d",time,&new_num);
    change_time_record_material(RL,ML,time,new_num);

    //4.根据时间删除一条记录 并更新仓库
    printf("请要删除记录的时间:");
    scanf("%s",time);
    delete_time_record_material(RL,ML,time);

    //5.给我一个货物名字 返回能做几杯
    int num=available_num("Wine","Baileys",GL,ML);
    printf("还可以做%d杯\n",num);

    //6.生成订单并更新仓库
    order_material("Wine","Baileys",GL,ML,3);
    order_material("Wine","Baileys",GL,ML,3);

    //7.根据各种字段查询进货记录
    query_record_time(RL,"2021.05.05.12.04");
    query_record_time_to_time(RL,"2021.04.05","2021.10.05");
    query_record_material_name(RL,"wine_c");
    query_record_wholesaler_name(RL,"yue");

    //8.根据各种字段排序并输出进货记录
    sort_record_time(RL);
    sort_record_material_name(RL);
    sort_record_wholesaler_name(RL);

    //!7.程序结束将链表谢晖结构体并写回dat文件
    list_arr(RL,RLa);
    write_dat(GL,ML,RLa);

    system("pause");
    return 0;
}