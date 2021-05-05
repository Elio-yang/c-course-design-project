/*
 * @Author: alone_yue
 * @Date: 2021-05-04 08:09:42
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"store.hpp"

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
        if(i==6) {printf("没有这个商品 亲！"); return -1;}

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
        if(i==6) {printf("没有这个商品 亲！"); return -1;}

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
        if(i==6) {printf("没有这个商品 亲！"); return -1;}

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
        if(i==6) {printf("没有这个商品 亲！"); return -1;}

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
void order_material(char type[30],char goods[30],GoodList* GL,MaterialList* ML,int count){
    if(strcmp(type,"Wine")==0){
        //!找到WineArr对应index
        int i;
        for(i=0;i<GL->wine_num;i++){
            if(strcmp(goods,GL->WineArr[i].name)==0) break;
        }
        if(i==6) {printf("没有这个商品 亲!\n"); return;}

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
        if(i==6) {printf("没有这个商品 亲!\n"); return;}

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
        if(i==6) {printf("没有这个商品 亲!\n"); return;}

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
        if(i==6) {printf("没有这个商品 亲!\n"); return;}

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
