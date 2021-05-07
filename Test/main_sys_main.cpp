/*
 * Test/main_sys_main.c
 * @author WangJ
 * @email  jluelioyang2001@gamil.com
 * @date 2021/5/5
 */
#include "../main_bar_sys/order.h"
#include "../main_bar_sys/store.h"
#include "../for_cpp/financial.h"
#include "../tools/print_color.h"
#include <cstring>
#include <stdio.h>
typedef struct dish {
        char name[30];
        char type[30];
        float price;
        int available_number;
        int personalization_availble; //how many persoalized choice do i have?
        char personalization[20][100];
} dish;

typedef struct order {
        int index;
        int menu;               //correspond
        char name[30];
        char type[30];
        int number;
        float price;
        int personalization_request;
        char personlization[20][100]; //add space after each personlized choice
        struct order *next;
} order;

#define MENU_PATH "menu.txt"
#define warehouse_availble 1


 int input_int(int *);        //analize the int input
 void get_menu(void);
 void print_menu(void);
 void print_order(void);
 void print_order_interface(void);
 void add_dishes(void);                  //add a dishes into the oderlist
 void check(void);                       //check the ordered dishes and conduct some operation
 void delete_dishes(void);               //delete a dishews
 void change_order(void);                //change the number or personalization
 void change_order_number(int);          //change the number of a dishes
 void change_order_personalization(int); //change the personalization of a dishes
 int finish(void);                       //quit the system
 int confirm();


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

int dishes_number; //the amount of the dishes in the menu
int order_number;  //the amount of the dishes of the order list
dish menu[200];
order order_list[200];

GoodList gl;
MaterialList ml;
GoodList* GL=&gl;
MaterialList* ML=&ml;
RecordList rl;
RecordList* RL=&rl;
RecordList_arr rla;
RecordList_arr* RLa=&rla;


int main()
{

        //!1.将文件读入结构体并将结构体读入链表
        read_struct_file(GL,ML,RLa);
        arr_list(RL,RLa);

        //2.从文件读入进货记录并更新仓库
        add_record_file(RL,ML);

        get_menu();
        print_menu();
        init_fi_sys();
        char instruction[100]; //the command
        while (1)
        {
                print_order_interface();
                printf(GREEN BOLD"wyz-bar@order " NONE"$ ");
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
                                        if (warehouse_availble)
                                                for(int i=0;i<order_number;i++)
                                                {
                                                        order_material(order_list[i].type,order_list[i].name,GL,ML,order_list[i].number);
                                                        char price[100];
                                                        sprintf(price,"%f",order_list[i].price);
                                                        update_finance_record(order_list[i].name,price,ORDER);
                                                }
                                        //!7.程序结束将链表写回结构体并写回dat文件
                                        list_arr(RL,RLa);
                                        write_dat(GL,ML,RLa);
                                        flush_fi_disk();
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


void arr_list(RecordList* RL,RecordList_arr* RLa){ //!从结构体数组读到链表
        for(int i=0;i<RLa->num;i++){
                RecordNode_arr* Node=&RLa->RecordArr[i];

                //!创建临时节点并赋值
                RecordNode* temp=(RecordNode*)malloc(sizeof(RecordNode));
                for(int i=0;i<strlen(Node->time);i++){
                        temp->time[i]=Node->time[i];
                }
                temp->time[strlen(Node->time)]='\0';

                for(int i=0;i<strlen(Node->material_name);i++){
                        temp->material_name[i]=Node->material_name[i];
                }
                temp->material_name[strlen(Node->material_name)]='\0';

                for(int i=0;i<strlen(Node->wholesaler_name);i++){
                        temp->wholesaler_name[i]=Node->wholesaler_name[i];
                }
                temp->wholesaler_name[strlen(Node->wholesaler_name)]='\0';

                temp->num=Node->num;
                temp->next=NULL;

                //!链表头插
                temp->next=RL->RecordHead.next;
                RL->RecordHead.next=temp;
                RL->num++;
        }
}
void list_arr(RecordList* RL,RecordList_arr* RLa){  //!从链表读到结构体数组
        RecordNode* Node=RL->RecordHead.next;
        RLa->num=0;
        while(Node!=NULL){
                RecordNode_arr temp;

                for(int i=0;i<strlen(Node->time);i++){
                        temp.time[i]=Node->time[i];
                }
                temp.time[strlen(Node->time)]='\0';

                for(int i=0;i<strlen(Node->material_name);i++){
                        temp.material_name[i]=Node->material_name[i];
                }
                temp.material_name[strlen(Node->material_name)]='\0';

                for(int i=0;i<strlen(Node->wholesaler_name);i++){
                        temp.wholesaler_name[i]=Node->wholesaler_name[i];
                }
                temp.wholesaler_name[strlen(Node->wholesaler_name)]='\0';

                temp.num=Node->num;

                //!给结构体数组赋值
                RLa->RecordArr[RLa->num++]=temp;

                Node=Node->next;
        }
}

void write_dat(GoodList* GL,MaterialList* ML,RecordList_arr* RLa){
        FILE* goodfile=fopen("GoodList.dat","wb");
        FILE* materialfile=fopen("MaterialList.dat","wb");
        FILE* recordListfile=fopen("RecordList.dat","wb");

        //!写GL到文件
        fwrite(&GL->wine_num,sizeof(int),1,goodfile);
        fwrite(&GL->snacks_num,sizeof(int),1,goodfile);
        fwrite(&GL->tea_num,sizeof(int),1,goodfile);
        fwrite(&GL->drinks_num,sizeof(int),1,goodfile);
        for(int i=0;i<GL->wine_num;i++){
                fwrite(&GL->WineArr[i],sizeof(GoodNode),1,goodfile);
        }
        for(int i=0;i<GL->snacks_num;i++){
                fwrite(&GL->SnacksArr[i],sizeof(GoodNode),1,goodfile);
        }
        for(int i=0;i<GL->tea_num;i++){
                fwrite(&GL->TeaArr[i],sizeof(GoodNode),1,goodfile);
        }
        for(int i=0;i<GL->drinks_num;i++){
                fwrite(&GL->DrinksArr[i],sizeof(GoodNode),1,goodfile);
        }

        //!写ML到文件
        fwrite(&ML->num,sizeof(int),1,materialfile);
        for(int i=0;i<ML->num;i++){
                fwrite(&ML->MaterialArr[i],sizeof(MaterialNode),1,materialfile);
        }

        //!写RL到文件
        fwrite(&RLa->num,sizeof(int),1,recordListfile);
        for(int i=0;i<RLa->num;i++){
                fwrite(&RLa->RecordArr[i],sizeof(RecordNode_arr),1,recordListfile);
        }


        fclose(goodfile);
        fclose(materialfile);
        fclose(recordListfile);
}
void read_struct_file(GoodList* GL,MaterialList* ML,RecordList_arr* RLa){
        FILE* goodfile=fopen("GoodList.dat","rb");
        FILE* materialfile=fopen("MaterialList.dat","rb");
        FILE* recordListfile=fopen("RecordList.dat","rb");

        //!读文件到GL
        fread(&GL->wine_num,sizeof(int),1,goodfile);
        fread(&GL->snacks_num,sizeof(int),1,goodfile);
        fread(&GL->tea_num,sizeof(int),1,goodfile);
        fread(&GL->drinks_num,sizeof(int),1,goodfile);
        for(int i=0;i<GL->wine_num;i++){
                fread(&GL->WineArr[i],sizeof(GoodNode),1,goodfile);
        }
        for(int i=0;i<GL->snacks_num;i++){
                fread(&GL->SnacksArr[i],sizeof(GoodNode),1,goodfile);
        }
        for(int i=0;i<GL->tea_num;i++){
                fread(&GL->TeaArr[i],sizeof(GoodNode),1,goodfile);
        }
        for(int i=0;i<GL->drinks_num;i++){
                fread(&GL->DrinksArr[i],sizeof(GoodNode),1,goodfile);
        }

        //!读文件到ML
        fread(&ML->num,sizeof(int),1,materialfile);
        for(int i=0;i<ML->num;i++){
                fread(&ML->MaterialArr[i],sizeof(MaterialNode),1,materialfile);
        }

        //!读文件到RL
        fread(&RLa->num,sizeof(int),1,recordListfile);
        for(int i=0;i<RLa->num;i++){
                fread(&RLa->RecordArr[i],sizeof(RecordNode_arr),1,recordListfile);
        }

        fclose(goodfile);
        fclose(materialfile);
        fclose(recordListfile);
}

void update_material(RecordNode* Node,MaterialList* ML){ //!被调用函数
        for(int i=0;i<ML->num;i++){
                if(strcmp(ML->MaterialArr[i].name,Node->material_name)==0){
                        ML->MaterialArr[i].num+=Node->num;
                        return;
                }
        }
}
void add_record_file(RecordList* RL,MaterialList* ML){ //!从文件读取进货信息
        FILE* file=fopen("record.txt","r");

        //!读入节点
        RecordNode* Node=(RecordNode*)malloc(sizeof(RecordNode));
        Node->next=NULL;
        while(fscanf(file,"%s %s %s %d",Node->time,Node->material_name,Node->wholesaler_name,&Node->num)!=EOF){
                //!创建临时节点并赋值
                RecordNode* temp=(RecordNode*)malloc(sizeof(RecordNode));
                for(int i=0;i<strlen(Node->time);i++){
                        temp->time[i]=Node->time[i];
                }
                temp->time[strlen(Node->time)]='\0';

                for(int i=0;i<strlen(Node->material_name);i++){
                        temp->material_name[i]=Node->material_name[i];
                }
                temp->material_name[strlen(Node->material_name)]='\0';

                for(int i=0;i<strlen(Node->wholesaler_name);i++){
                        temp->wholesaler_name[i]=Node->wholesaler_name[i];
                }
                temp->wholesaler_name[strlen(Node->wholesaler_name)]='\0';

                temp->num=Node->num;
                temp->next=NULL;

                //!链表头插
                temp->next=RL->RecordHead.next;
                RL->RecordHead.next=temp;
                RL->num++;
                update_material(temp,ML);
        }

        fclose(file);
}

void change_time_record_material(RecordList* RL,MaterialList* ML,char time[30],int new_num){
        RecordNode* temp=RL->RecordHead.next;
        while(temp!=NULL&&strcmp(temp->time,time)!=0){
                temp=temp->next;
        }
        if(temp==NULL) {printf("您好！没有这条记录哦!\n"); return;}

        //!根据时间找到货物名称并更新仓库
        temp->num=new_num;
        for(int i=0;i<ML->num;i++){
                if(strcmp(temp->material_name,ML->MaterialArr[i].name)==0){
                        ML->MaterialArr[i].num=new_num;
                }
        }
}
void delete_time_record_material(RecordList* RL,MaterialList* ML,char time[30]){
        RecordNode* temp0=&RL->RecordHead;
        RecordNode* temp=RL->RecordHead.next;
        while(temp!=NULL&&strcmp(temp->time,time)!=0){
                temp0=temp;
                temp=temp->next;
        }
        if(temp==NULL) {printf("您好！没有这条记录哦!\n"); return;}

        //!更新仓库
        for(int i=0;i<ML->num;i++){
                if(strcmp(temp->material_name,ML->MaterialArr[i].name)==0){
                        ML->MaterialArr[i].num-=temp->num; //!减去这条记录的数量
                }
        }
        //!删除记录(删除链表节点)
        temp0->next=temp->next;
        free(temp);
}

void query_record_time(RecordList* RL,char time[30]){
        if(RL->RecordHead.next==NULL) {printf("进货记录为空"); return;}
        printf("开始查询时间为%s的记录\n",time);
        RecordNode* temp=RL->RecordHead.next;
        int cnt=1;
        int flag=0;
        while(temp!=NULL){
                if(strcmp(temp->time,time)==0){
                        printf("第%d条记录:%s %s %s %d\n",cnt++,temp->time,temp->material_name,temp->wholesaler_name,temp->num);
                        flag=1;
                }
                temp=temp->next;
        }
        if(flag==0){
                printf("查无此纪录\n");
        }
}
void query_record_time_to_time(RecordList* RL,char time1[30],char time2[30]){
        if(RL->RecordHead.next==NULL) {printf("进货记录为空"); return;}
        printf("开始查询时间%s到%s的记录\n",time1,time2);
        RecordNode* temp=RL->RecordHead.next;
        int cnt=1;
        int flag=0;
        while(temp!=NULL){
                if(strcmp(temp->time,time1)>=0&&strcmp(temp->time,time2)<=0){
                        printf("第%d条记录:%s %s %s %d\n",cnt++,temp->time,temp->material_name,temp->wholesaler_name,temp->num);
                        flag=1;
                }
                temp=temp->next;
        }
        if(flag==0){
                printf("查无此纪录\n");
        }
}
void query_record_material_name(RecordList* RL,char material_name[30]){
        if(RL->RecordHead.next==NULL) {printf("进货记录为空"); return;}
        printf("开始查询原料为%s的记录\n",material_name);
        RecordNode* temp=RL->RecordHead.next;
        int cnt=1;
        int flag=0;
        while(temp!=NULL){
                if(strcmp(temp->material_name,material_name)==0){
                        printf("第%d条记录:%s %s %s %d\n",cnt++,temp->time,temp->material_name,temp->wholesaler_name,temp->num);
                        flag=1;
                }
                temp=temp->next;
        }
        if(flag==0){
                printf("查无此纪录\n");
        }
}
void query_record_wholesaler_name(RecordList* RL,char wholesaler_name[30]){
        if(RL->RecordHead.next==NULL) {printf("进货记录为空"); return;}
        printf("开始查询处理人%s的记录\n",wholesaler_name);
        RecordNode* temp=RL->RecordHead.next;
        int cnt=1;
        int flag=0;
        while(temp!=NULL){
                if(strcmp(temp->wholesaler_name,wholesaler_name)==0){
                        printf("第%d条记录:%s %s %s %d\n",cnt++,temp->time,temp->material_name,temp->wholesaler_name,temp->num);
                        flag=1;
                }
                temp=temp->next;
        }
        if(flag==0){
                printf("查无此纪录\n");
        }
}

void sort_record_time(RecordList* RL){
        if(RL->RecordHead.next==NULL) {printf("进货记录为空"); return;}
        printf("以时间排序为:\n");
        RecordNode* head=(RecordNode*)malloc(sizeof(RecordNode));
        head->next=NULL;
        RecordNode* p1;
        RecordNode* p2;

        //!插入排序
        RecordNode* p=RL->RecordHead.next;
        while(p!=NULL){
                p1=head;
                p2=head->next;
                while(p2!=NULL&&strcmp(p->time,p2->time)>=0){
                        p1=p2;
                        p2=p2->next;
                }

                //!把p信息赋给t
                RecordNode* t=(RecordNode*)malloc(sizeof(RecordNode));
                for(int i=0;i<strlen(p->time);i++){
                        t->time[i]=p->time[i];
                }
                t->time[strlen(p->time)]='\0';

                for(int i=0;i<strlen(p->material_name);i++){
                        t->material_name[i]=p->material_name[i];
                }
                t->material_name[strlen(p->material_name)]='\0';

                for(int i=0;i<strlen(p->wholesaler_name);i++){
                        t->wholesaler_name[i]=p->wholesaler_name[i];
                }
                t->wholesaler_name[strlen(p->wholesaler_name)]='\0';

                t->num=p->num;
                t->next=NULL;

                //!头插入
                p1->next=t;
                t->next=p2;

                //!进货记录下一条
                p=p->next;
        }

        //!输出
        int cnt=1;
        RecordNode* temp=head->next;
        while(temp!=NULL){
                printf("第%d条记录:%s %s %s %d\n",cnt++,temp->time,temp->material_name,temp->wholesaler_name,temp->num);
                temp=temp->next;
        }
}
void sort_record_material_name(RecordList* RL){
        if(RL->RecordHead.next==NULL) {printf("进货记录为空"); return;}
        printf("以货物名称排序为:\n");
        RecordNode* head=(RecordNode*)malloc(sizeof(RecordNode));
        head->next=NULL;
        RecordNode* p1;
        RecordNode* p2;

        //!插入排序
        RecordNode* p=RL->RecordHead.next;
        while(p!=NULL){
                p1=head;
                p2=head->next;
                while(p2!=NULL&&strcmp(p->material_name,p2->material_name)>=0){
                        p1=p2;
                        p2=p2->next;
                }

                //!把p信息赋给t
                RecordNode* t=(RecordNode*)malloc(sizeof(RecordNode));
                for(int i=0;i<strlen(p->time);i++){
                        t->time[i]=p->time[i];
                }
                t->time[strlen(p->time)]='\0';

                for(int i=0;i<strlen(p->material_name);i++){
                        t->material_name[i]=p->material_name[i];
                }
                t->material_name[strlen(p->material_name)]='\0';

                for(int i=0;i<strlen(p->wholesaler_name);i++){
                        t->wholesaler_name[i]=p->wholesaler_name[i];
                }
                t->wholesaler_name[strlen(p->wholesaler_name)]='\0';

                t->num=p->num;
                t->next=NULL;

                //!头插入
                p1->next=t;
                t->next=p2;

                //!进货记录下一条
                p=p->next;
        }

        //!输出
        int cnt=1;
        RecordNode* temp=head->next;
        while(temp!=NULL){
                printf("第%d条记录:%s %s %s %d\n",cnt++,temp->time,temp->material_name,temp->wholesaler_name,temp->num);
                temp=temp->next;
        }
}
void sort_record_wholesaler_name(RecordList* RL){
        if(RL->RecordHead.next==NULL) {printf("进货记录为空"); return;}
        printf("以处理人排序为:\n");
        RecordNode* head=(RecordNode*)malloc(sizeof(RecordNode));
        head->next=NULL;
        RecordNode* p1;
        RecordNode* p2;

        //!插入排序
        RecordNode* p=RL->RecordHead.next;
        while(p!=NULL){
                p1=head;
                p2=head->next;
                while(p2!=NULL&&strcmp(p->wholesaler_name,p2->wholesaler_name)>=0){
                        p1=p2;
                        p2=p2->next;
                }

                //!把p信息赋给t
                RecordNode* t=(RecordNode*)malloc(sizeof(RecordNode));
                for(int i=0;i<strlen(p->time);i++){
                        t->time[i]=p->time[i];
                }
                t->time[strlen(p->time)]='\0';

                for(int i=0;i<strlen(p->material_name);i++){
                        t->material_name[i]=p->material_name[i];
                }
                t->material_name[strlen(p->material_name)]='\0';

                for(int i=0;i<strlen(p->wholesaler_name);i++){
                        t->wholesaler_name[i]=p->wholesaler_name[i];
                }
                t->wholesaler_name[strlen(p->wholesaler_name)]='\0';

                t->num=p->num;
                t->next=NULL;

                //!头插入
                p1->next=t;
                t->next=p2;

                //!进货记录下一条
                p=p->next;
        }

        //!输出
        int cnt=1;
        RecordNode* temp=head->next;
        while(temp!=NULL){
                printf("第%d条记录:%s %s %s %d\n",cnt++,temp->time,temp->material_name,temp->wholesaler_name,temp->num);
                temp=temp->next;
        }
}

int available_num(char type[30],char goods[30],GoodList* GL,MaterialList* ML){
        if(strcmp(type,"Wine")==0){
                //!找到WineArr对应index
                int i;
                for(i=0;i<GL->wine_num;i++){
                        if(strcmp(goods,GL->WineArr[i].name)==0) break;
                }
                if(i==GL->wine_num) {printf("没有这个商品 亲！ %s \n",goods); return -1;}

                //!计算哪种原料最少就是能做的数量
                int min=10000;
                for(int j=0;j<GL->WineArr[i].item_num;j++){
                        int index=GL->WineArr[i].item[j];
                        int num=ML->MaterialArr[index-1].num;
                        if(num<min){
                                min=num;
                        }
                }
                return min;
        }
        if(strcmp(type,"Snacks")==0){
                //!找到SnacksArr对应index
                int i;
                for(i=0;i<GL->snacks_num;i++){
                        if(strcmp(goods,GL->SnacksArr[i].name)==0) break;
                }
                if(i==GL->snacks_num) {
                        printf("没有这个商品 亲！ %s \n",goods);
                        return -1;
                }

                //!计算哪种原料最少就是能做的数量
                int min=10000;
                for(int j=0;j<GL->SnacksArr[i].item_num;j++){
                        int index=GL->SnacksArr[i].item[j];
                        int num=ML->MaterialArr[index-1].num;
                        if(num<min){
                                min=num;
                        }
                }
                return min;

        }
        if(strcmp(type,"Tea")==0){
                //!找到WineArr对应index
                int i;
                for(i=0;i<GL->tea_num;i++){
                        if(strcmp(goods,GL->TeaArr[i].name)==0) break;
                }
                if(i==GL->tea_num) {printf("没有这个商品 亲！ %s \n",goods); return -1;}

                //!计算哪种原料最少就是能做的数量
                int min=10000;
                for(int j=0;j<GL->TeaArr[i].item_num;j++){
                        int index=GL->TeaArr[i].item[j];
                        int num=ML->MaterialArr[index-1].num;
                        if(num<min){
                                min=num;
                        }
                }
                return min;

        }
        if(strcmp(type,"Drinks")==0){
                //!找到WineArr对应index
                int i;
                for(i=0;i<GL->drinks_num;i++){
                        if(strcmp(goods,GL->DrinksArr[i].name)==0) break;
                }
                if(i==GL->drinks_num) {printf("没有这个商品 亲！ %s \n",goods); return -1;}

                //!计算哪种原料最少就是能做的数量
                int min=10000;
                for(int j=0;j<GL->DrinksArr[i].item_num;j++){
                        int index=GL->DrinksArr[i].item[j];
                        int num=ML->MaterialArr[index-1].num;
                        if(num<min){
                                min=num;
                        }
                }
                return min;

        }

        printf("输入类别有误！");
        return -1;
}
void order_material(char type[],char goods[],GoodList* GL,MaterialList* ML,int count){
        if(strcmp(type,"Wine")==0){
                //!找到WineArr对应index
                int i;
                for(i=0;i<GL->wine_num;i++){
                        if(strcmp(goods,GL->WineArr[i].name)==0) break;
                }
                if(i==GL->wine_num) {printf("没有这个商品 亲!\n"); return;}

                //!计算哪种原料最少就是能做的数量
                int min=10000;
                for(int j=0;j<GL->WineArr[i].item_num;j++){
                        int index=GL->WineArr[i].item[j];
                        int num=ML->MaterialArr[index-1].num;
                        if(num<min){
                                min=num;
                        }
                }

                //!开始制作并更新仓库
                if(count>min) {printf("做不了那么多 只能做%d杯了\n",min); return;}
                for(int j=0;j<GL->WineArr[i].item_num;j++){
                        int index=GL->WineArr[i].item[j];
                        ML->MaterialArr[index-1].num-=count;
                }
                printf("已做完%d杯\n",count); return;
        }
        if(strcmp(type,"Snacks")==0){
                //!找到SnacksArr对应index
                int i;
                for(i=0;i<GL->snacks_num;i++){
                        if(strcmp(goods,GL->SnacksArr[i].name)==0) break;
                }
                if(i==GL->snacks_num) {printf("没有这个商品 亲!\n"); return;}

                //!计算哪种原料最少就是能做的数量
                int min=10000;
                for(int j=0;j<GL->SnacksArr[i].item_num;j++){
                        int index=GL->SnacksArr[i].item[j];
                        int num=ML->MaterialArr[index-1].num;
                        if(num<min){
                                min=num;
                        }
                }

                //!开始制作并更新仓库
                if(count>min) {printf("做不了那么多 只能做%d杯了\n",min); return;}
                for(int j=0;j<GL->SnacksArr[i].item_num;j++){
                        int index=GL->SnacksArr[i].item[j];
                        ML->MaterialArr[index-1].num-=count;
                }
                printf("已做完%d杯\n",count); return;

        }
        if(strcmp(type,"Tea")==0){
                //!找到WineArr对应index
                int i;
                for(i=0;i<GL->tea_num;i++){
                        if(strcmp(goods,GL->TeaArr[i].name)==0) break;
                }
                if(i==GL->tea_num) {printf("没有这个商品 亲!\n"); return;}

                //!计算哪种原料最少就是能做的数量
                int min=10000;
                for(int j=0;j<GL->TeaArr[i].item_num;j++){
                        int index=GL->TeaArr[i].item[j];
                        int num=ML->MaterialArr[index-1].num;
                        if(num<min){
                                min=num;
                        }
                }

                //!开始制作并更新仓库
                if(count>min) {printf("做不了那么多 只能做%d杯了\n",min); return;}
                for(int j=0;j<GL->TeaArr[i].item_num;j++){
                        int index=GL->TeaArr[i].item[j];
                        ML->MaterialArr[index-1].num-=count;
                }
                printf("已做完%d杯\n",count); return;

        }
        if(strcmp(type,"Drinks")==0){
                //!找到WineArr对应index
                int i;
                for(i=0;i<GL->drinks_num;i++){
                        if(strcmp(goods,GL->DrinksArr[i].name)==0) break;
                }
                if(i==GL->drinks_num) {printf("没有这个商品 亲!\n"); return;}

                //!计算哪种原料最少就是能做的数量
                int min=10000;
                for(int j=0;j<GL->DrinksArr[i].item_num;j++){
                        int index=GL->DrinksArr[i].item[j];
                        int num=ML->MaterialArr[index-1].num;
                        if(num<min){
                                min=num;
                        }
                }

                //!开始制作并更新仓库
                if(count>min) {printf("做不了那么多 只能做%d杯了\n",min); return;}
                for(int j=0;j<GL->DrinksArr[i].item_num;j++){
                        int index=GL->DrinksArr[i].item[j];
                        ML->MaterialArr[index-1].num-=count;
                }
                printf("已做完%d杯\n",count); return;

        }

        printf("输入类别有误!\n");
        return;
}


int input_int(int *instruction) //if input 0 then quit
{
        char number[100]; //save the number
        int flag = 0;
        int i, len;
        int count = 0;
        while (flag == 0)
        {
                printf("(input '0' to quit)\n");
                gets(number);
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
                        for (int i = 0; i < menu[dishes_number].personalization_availble; i++) //get the personalization message
                                fscanf(p, "%s", menu[dishes_number].personalization[i]);
                        if(dishes_number<20)
                                memcpy(menu[dishes_number].type,"Wine",sizeof("Wine"));
                        else if(dishes_number<33)
                                memcpy(menu[dishes_number].type,"Snacks",sizeof("Snacks"));
                        else if(dishes_number<39)
                                memcpy(menu[dishes_number].type,"Tea",sizeof("Tea"));
                        else if(dishes_number<47)
                                memcpy(menu[dishes_number].type,"Drinks",sizeof("Drinks"));
                        if (!warehouse_availble) //warehouseinterface1
                                menu[dishes_number].available_number = 2;
                        else
                                menu[dishes_number].available_number = available_num(menu[dishes_number].type,menu[dishes_number].name,GL,ML);
                        dishes_number++;
                        if (feof(p))
                                break;
                        else
                                fgetc(p); //diminish the \n in the end
                }
}
void print_menu()
{
        printf("+-------------------------------MENU---------------------------------------+\n");
        for (int i = 0; i < dishes_number; i++)
                printf("|%2d.%-40s%.2f        yuan              |\n", i + 1, menu[i].name, menu[i].price);
        printf("+--------------------------------------------------------------------------+\n");

}

void print_order()
{
        printf("--------------------------------ORDER_LIST----------------------------------------\n");

        int aggregate_price = 0;
        for (int i = 0; i < order_number; i++) //print the order
        {
                printf("%2d.%-36s%-5d%.2fyuan\n", i + 1, order_list[i].name, order_list[i].number, order_list[i].price);
                for (int j = 0; j < order_list[i].personalization_request; j++)
                        printf(" %s\n", order_list[i].personlization[j]);

                aggregate_price += order_list[i].price;
        }
        printf("The aggregate price is %d yuan.\n", aggregate_price);
}

void print_order_interface()
{
        printf(""
               "--------------------------------INSTRUCTION--------------------------------+\n"
               "|You can place an order using the following commands:                      |\n"
               "|a:Add a dishes                                                            |\n"
               "|c:Check your order and change it                                          |\n"
               "|q:Quit the order interface directly                                       |\n"
               "|f:Check, confirm and finish your ordering                                 |\n"
               "+--------------------------------------------------------------------------+\n");
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
                return; //return 0 to directly quit
        }
        while (index < 1 || index > dishes_number) //find out if we have the dishes
        {
                printf("Dishes doesn't exist,Please input again\n");
                if (!input_int(&index))
                {
                        return; //return -0 to directly quit
                }
        }
        index--; //begin with 0
        printf("Please input the number of the dishes\n");
        if (!input_int(&number))
        {
                return;
        }
        while (number < 1 || number > menu[index].available_number)
        {
                printf("Sorry, we only have %d %s left, Please input again\n", menu[index].available_number, menu[index].name);
                if (!input_int(&number))
                {
                        return;
                }
        }
        // getchar();            //加入confirm后不用getchar？？？
        if (menu[index].personalization_availble) //choose the taste
        {
                printf("+-----------------------------------------------------------------------+\n"
                       "|The dishes has taste choice followed                                   |\n");
                for (int i = 0; i < menu[index].personalization_availble; i++)
                        printf("|%d.%-50s                   |\n", i + 1, menu[index].personalization[i]);
                printf("+-----------------------------------------------------------------------+\n");
                while (1)
                {
                        printf("Please input the number of the taste you want\n");
                        if (!input_int(&taste))
                        {
                                printf("Fail to get the personalization\n");
                                return;
                        }
                        if (taste < 1 || taste > menu[index].personalization_availble)
                        {
                                printf("Taste doesn't exist,Please input again\n");
                                continue;
                        }

                        int j; //judge if the taste has been chosen
                        for (j = 0; j < num; j++)
                                if (individual[j] == taste - 1)
                                        break;
                        if (j == num)
                                individual[num++] = taste - 1;
                        else
                                printf("Taste exists!\n");
                        printf("Continue or not?(Y/N)\n");

                        if (!confirm())
                                break;
                }
        }

        for (int i = 0; i < num; i++) //get the dishes message into the oerder list
                strcpy(order_list[order_number].personlization[i], menu[index].personalization[individual[i]]);
        order_list[order_number].personalization_request = num;
        order_list[order_number].menu = index;
        strcpy(order_list[order_number].name, menu[index].name);
        order_list[order_number].number = number;
        order_list[order_number].price = menu[index].price * number;
        strcpy(order_list[order_number].type,menu[index].type);
        order_number++;
        printf("Adding %d %s into the order successfully!\n", number, menu[index].name);
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
                        printf("Instruction doesn't exist,please input again\n");
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
                printf("Fail to delete dishes");
                return;
        }
        while (index < 1 || index > order_number) //incorrect input
        {
                printf("Dishes doesn't exist,please input again\n");
                if (!input_int(&index))
                {
                        printf("Fail to delete dishes\n");
                        return;
                }
        }
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
                return;
        }
        while (index < 1 || index > order_number)
        {
                printf("Dishes doesn't exist,please input again\n");
                if (!input_int(&index))
                {
                        return;
                }
        }

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
                return;
        } //fail to get number
        while (number < 1||number > menu[index].available_number)
        {
                printf("Sorry, we only have %d %s left, Please input again\n", menu[index].available_number, menu[index].name);
                if (!input_int(&number))
                {
                        printf("Fail to change the number\n");
                        return;
                } //fail to get number
        }
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

        printf("+-----------------------------------------------------------------+\n"
               "|The dishes has taste choice followed                |\n");
        for (int i = 0; i < menu[index].personalization_availble; i++)
                printf("|%d.%-50s|\n", i + 1, menu[index].personalization[i]);
        while (1)
        {
                printf("Please input the number of the taste you want\n");
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

                int j; //judge if the taste has been chosen
                for (j = 0; j < num; j++)
                        if (individual[j] == taste - 1)
                                break;
                if (j == num)
                        individual[num++] = taste - 1;
                else
                        printf("Taste exists!\n");
                printf("Continue or not?(Y/N)\n");

                if (!confirm())
                        break;
        }
        printf("Are you sure you want?\n");
        for (int i = 0; i < num; i++)
                printf("%s ", menu[index].personalization[individual[i]]);
        printf("(Y/N)\n");
        if (confirm())
        {
                for (int i = 0; i < num; i++)
                        strcpy(order_list[order].personlization[i], menu[index].personalization[individual[i]]);
                order_list[order].personalization_request = num;
                printf("You have changed the taste of %s successfully!", order_list[order].name);
        }
}

int finish()
{
        char instruction[100];
        while (1)
        {
                print_order();
                printf("Are you going to confirm(y) your order or change(c) it?\n");
                printf("Input q to go back to instrution interface\n");
                gets(instruction);
                if (strlen(instruction) > 1) //incorrect command
                {
                        printf("Instruction doesn't exist,please input again\n");
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
                                printf("Instruction doesn't existp please input again\n");
                                break;
                }
        }
}

int confirm() //Y/N?
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
