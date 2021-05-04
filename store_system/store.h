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
    struct RE* next=NULL;
}RecordNode;
typedef struct{
    RecordNode RecordHead; //哨兵节点
    int num=0;
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
    int num=0;
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
    int wine_num=0;
    int snacks_num=0;
    int tea_num=0;
    int drinks_num=0;
}GoodList;

//原料结构体
typedef struct{
    char name[30];
    int num=0;
}MaterialNode;
typedef struct{
    MaterialNode MaterialArr[100];
    int num;
}MaterialList;

void arr_list(RecordList* RL,RecordList_arr* RLa); //!从链表写到结构体数组
void list_arr(RecordList* RL,RecordList_arr* RLa);  //!从结构体数组读到链表

void write_dat(GoodList* GL,MaterialList* ML,RecordList_arr* Rla); 
void read_struct_file(GoodList* GL,MaterialList* ML,RecordList_arr* Rla);
void update_material(RecordNode* Node,MaterialList* ML);
void add_record_file(RecordList* RL,MaterialList* ML);
void change_time_record_material(RecordList* RL,MaterialList* ML,char time[30],int new_num);
void delete_time_record_material(RecordList* RL,MaterialList* ML,char time[30]);

void query_record_time(RecordList* RL,char time[30]);
void query_record_time_to_time(RecordList* RL,char time1[30],char time2[30]);
void query_record_material_name(RecordList* RL,char material_name[30]);
void query_record_wholesaler_name(RecordList* RL,char wholesaler_name[30]);


void sort_record_time(RecordList* RL);
void sort_record_material_name(RecordList* RL);
void sort_record_wholesaler_name(RecordList* RL);

int available_num(char type[30],char goods[30],GoodList* GL,MaterialList* ML);
void order_material(char type[30],char goods[30],GoodList* GL,MaterialList* ML,int count);