/*
 * Test/store_sys_main.cpp
 * @Author: alone_yue
 * @Date: 2021-04-23 09:18:42
 */
#include<cstdio>
#include<cstdlib>
#include "../for_cpp/financial.h"
#include"../single_store_system/store.h"
#include "../tools/process_bar.h"

int main(){

        GoodList gl;
        MaterialList ml;
        GoodList* GL=&gl;
        MaterialList* ML=&ml;
        RecordList rl;
        RecordList* RL=&rl;
        RecordList_arr rla;
        RecordList_arr* RLa=&rla;

        init_fi_sys();
        //!1.将文件读入结构体并将结构体读入链表
        read_struct_file(GL,ML,RLa);
        //arr_list(RL,RLa);

        process_bar("Start loading files and testing");
        //2.从文件读入进货记录并更新仓库
        add_record_file(RL,ML);
        printf("-----------------------------------------------------------------------------------------\n\n");

        //3.根据时间 不知道原来是多少改为新的数量 并更新仓库(要求根据原来的数量和新的数量更新)
        change_time_record_material(RL,ML,"2021.05.05.12.28",100);
        printf("-----------------------------------------------------------------------------------------\n\n");

        //4.根据时间删除一条记录 并更新仓库
        delete_time_record_material(RL,ML,"2021.05.05.12.28");
        printf("-----------------------------------------------------------------------------------------\n\n");


        //5.输出原料及数量
        print_material(ML);
        printf("-----------------------------------------------------------------------------------------\n\n");



        //6.给我一个货物名字 返回能做几杯
        int num;
        num=available_num("Wine","Baileys",GL,ML);
        printf("还可以做%d杯\n",num);
        num=available_num("Wine","Malibu",GL,ML);
        printf("还可以做%d杯\n",num);
        num=available_num("Snacks","PearsinRedWine",GL,ML);
        printf("还可以做%d杯\n",num);
        num=available_num("Snacks","zzzzzz",GL,ML);
        printf("还可以做%d杯\n",num);
        num=available_num("Sack","zzzzzz",GL,ML);
        printf("还可以做%d杯\n",num);
        printf("-----------------------------------------------------------------------------------------\n\n");

        //7.生成订单并更新仓库
        order_material("Wine","Baileys",GL,ML,3);
        order_material("Wine","Malibu",GL,ML,2);
        order_material("Snacks","PearsinRedWine",GL,ML,2);
        order_material("Snacs","PearsinRedWine",GL,ML,2);
        order_material("Snacks","Pead!!!!! Wine",GL,ML,2);
        printf("-----------------------------------------------------------------------------------------\n\n");

        //8.根据各种字段查询进货记录
        query_record_time(RL,"2021.05.05.12.04");
        query_record_time_to_time(RL,"2021.04.05","2021.10.05");
        query_record_material_name(RL,"wine_c");
        query_record_wholesaler_name(RL,"yue");
        printf("-----------------------------------------------------------------------------------------\n\n");

        //9.根据各种字段排序并输出进货记录
        sort_record_time(RL);
        sort_record_material_name(RL);
        sort_record_wholesaler_name(RL);
        printf("-----------------------------------------------------------------------------------------\n\n");



        //!10.程序结束将链表谢晖结构体并写回dat文件
        list_arr(RL,RLa);
        write_dat(GL,ML,RLa);

        flush_fi_disk();
        exit(0);
}
