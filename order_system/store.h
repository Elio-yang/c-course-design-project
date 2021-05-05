#ifndef _STORE_
#define _STRORE_
/*
 * @Author: alone_yue
 * @Date: 2021-04-22 16:46:19
 */
#include<stdio.h>

//!进货记录结构体及链表
typedef struct RE{
    char time[30];
    char material_name[30];
    char wholesaler_name[30];
    int num;
    struct RE* next;
}RecordNode;
typedef struct{
    RecordNode RecordHead; //哨兵节点
    int num;
}RecordList;

//!进货记录结构体及数组
typedef struct{
    char time[30];
    char material_name[30];
    char wholesaler_name[30];
    int num;
}RecordNode_arr;
typedef struct{
    RecordNode_arr RecordArr[10000]; 
    int num;
}RecordList_arr;

//商品结构体及数组
typedef struct{
    char name[30];
    int item_num;
    int item[20];
}GoodNode;
typedef struct{
    GoodNode WineArr[100];
    GoodNode SnacksArr[100];
    GoodNode TeaArr[100];
    GoodNode DrinksArr[100];
    int wine_num;
    int snacks_num;
    int tea_num;
    int drinks_num;
}GoodList;

//原料结构体
typedef struct{
    char name[30];
    int num;
}MaterialNode;
typedef struct{
    MaterialNode MaterialArr[100];
    int num;
}MaterialList;

extern void arr_list(RecordList* RL,RecordList_arr* RLa); //!从链表写到结构体数组
extern void list_arr(RecordList* RL,RecordList_arr* RLa);  //!从结构体数组读到链表

extern void write_dat(GoodList* GL,MaterialList* ML,RecordList_arr* Rla); 
extern void read_struct_file(GoodList* GL,MaterialList* ML,RecordList_arr* Rla);
extern void update_material(RecordNode* Node,MaterialList* ML);
extern void add_record_file(RecordList* RL,MaterialList* ML);
extern void change_time_record_material(RecordList* RL,MaterialList* ML,char time[30],int new_num);
extern void delete_time_record_material(RecordList* RL,MaterialList* ML,char time[30]);

extern void query_record_time(RecordList* RL,char time[30]);
extern void query_record_time_to_time(RecordList* RL,char time1[30],char time2[30]);
extern void query_record_material_name(RecordList* RL,char material_name[30]);
extern void query_record_wholesaler_name(RecordList* RL,char wholesaler_name[30]);


extern void sort_record_time(RecordList* RL);
extern void sort_record_material_name(RecordList* RL);
extern void sort_record_wholesaler_name(RecordList* RL);

extern int available_num(char type[30],char goods[30],GoodList* GL,MaterialList* ML);
extern void order_material(char type[30],char goods[30],GoodList* GL,MaterialList* ML,int count);
#endif