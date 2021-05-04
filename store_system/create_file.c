/*
 * @Author: alone_yue
 * @Date: 2021-04-23 09:53:24
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//商品结构体及数组
typedef struct{
    char name[30];
    int item_num=0;
    int item[20]={0};
}GoodNode;
typedef struct{
    GoodNode WineArr[20];
    GoodNode SnacksArr[13];
    GoodNode TeaArr[6];
    GoodNode DrinksArr[9];
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
    int num=0;
}MaterialList;

//记录结构体
typedef struct RE{
    char time[30];
    char material_name[30];
    char wholesaler_name[30];
    int num;
}RecordNode;
typedef struct{
    RecordNode RecordHead[10000]; //哨兵节点
    int num=0;
}RecordList;

void create_good_name(GoodList* GL){
    FILE* Winefile=fopen("F:\\PROJECT\\all_code\\zzzzzzzz_txt\\Wine.txt","r");
    FILE* Snacksfile=fopen("F:\\PROJECT\\all_code\\zzzzzzzz_txt\\Snacks.txt","r");
    FILE* Teafile=fopen("F:\\PROJECT\\all_code\\zzzzzzzz_txt\\Tea.txt","r");
    FILE* Drinksfile=fopen("F:\\PROJECT\\all_code\\zzzzzzzz_txt\\Drinks.txt","r");

    char temp[30];
    while(fgets(temp,30,Winefile)!=NULL){
        int len=strlen(temp);
        for(int i=0;i<len-1;i++){
            GL->WineArr[GL->wine_num].name[i]=temp[i];
        }
        GL->WineArr[GL->wine_num].name[len-1]='\0';
        GL->wine_num++;
    }
    while(fgets(temp,30,Snacksfile)!=NULL){
        int len=strlen(temp);
        for(int i=0;i<len-1;i++){
            GL->SnacksArr[GL->snacks_num].name[i]=temp[i];
        }
        GL->SnacksArr[GL->snacks_num].name[len-1]='\0';
        GL->snacks_num++;
    }
    while(fgets(temp,30,Teafile)!=NULL){       
        int len=strlen(temp);
        for(int i=0;i<len-1;i++){
            GL->TeaArr[GL->tea_num].name[i]=temp[i];
        }
        GL->TeaArr[GL->tea_num].name[len-1]='\0';
        GL->tea_num++;
    }
    while(fgets(temp,30,Drinksfile)!=NULL){
        int len=strlen(temp);
        for(int i=0;i<len-1;i++){
            GL->DrinksArr[GL->drinks_num].name[i]=temp[i];
        }
        GL->DrinksArr[GL->drinks_num].name[len-1]='\0';
        GL->drinks_num++;
    }

    fclose(Winefile);
    fclose(Snacksfile);
    fclose(Teafile);
    fclose(Drinksfile);
}

void create_material(MaterialList* ML){
    FILE* file=fopen("F:\\PROJECT\\all_code\\zzzzzzzz_txt\\material.txt","r");

    char temp[30];
    while(fgets(temp,30,file)!=NULL){
        //!fgets函数会自动把换行符加入字符串末尾
        int len=strlen(temp);
        for(int i=0;i<len-1;i++){
            ML->MaterialArr[ML->num].name[i]=temp[i];
        }
        ML->MaterialArr[ML->num].name[len-1]='\0';
        ML->num++;
    }

    fclose(file);
}

void create_good_material(GoodList* GL){
    FILE* file=fopen("F:\\PROJECT\\all_code\\zzzzzzzz_txt\\1-20_21-33_34-39_40-48.txt","r");
    char temp[30]; int i;

    i=0;
    while(fgets(temp,30,file)!=NULL){
        int len=strlen(temp);
        for(int j=0;j<len;j++){
            if(temp[j]!=' '&&temp[j]!='\n'){
                GL->WineArr[i].item[GL->WineArr[i].item_num++]=temp[j]-48;
            }
        }
        i++;
        if(i==GL->wine_num) break;
    }
    
    i=0;
    while(fgets(temp,30,file)!=NULL){
        int len=strlen(temp);
        for(int j=0;j<len;j++){
            if(temp[j]!=' '&&temp[j]!='\n'){
                GL->SnacksArr[i].item[GL->SnacksArr[i].item_num++]=temp[j]-48;
            }
        }
        i++;
        if(i==GL->snacks_num) break;
    }
    
    i=0;
    while(fgets(temp,30,file)!=NULL){
        int len=strlen(temp);
        for(int j=0;j<len;j++){
            if(temp[j]!=' '&&temp[j]!='\n'){
                GL->TeaArr[i].item[GL->TeaArr[i].item_num++]=temp[j]-48;
            }
        }
        i++;
        if(i==GL->tea_num) break;
    }

    i=0;
    while(fgets(temp,30,file)!=NULL){
        int len=strlen(temp);
        for(int j=0;j<len;j++){
            if(temp[j]!=' '&&temp[j]!='\n'){
                GL->DrinksArr[i].item[GL->DrinksArr[i].item_num++]=temp[j]-48;
            }
        }
        i++;
        if(i==GL->drinks_num) break;
    }
    

    fclose(file);
}

void write_dat(GoodList* GL,MaterialList* ML){
    FILE* goodfile=fopen("F:\\PROJECT\\all_code\\zzzzzzzz_txt\\GoodList.dat","wb");
    FILE* materialfile=fopen("F:\\PROJECT\\all_code\\zzzzzzzz_txt\\MaterialList.dat","wb");

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


    fclose(goodfile);
    fclose(materialfile);
}

int main(){
    GoodList gl;      
    MaterialList ml;
    GoodList* GL=&gl; 
    MaterialList* ML=&ml;
    RecordList rl;
    RecordList* RL=&rl;

    create_good_name(GL);
    create_material(ML);
    create_good_material(GL);
    
    
    write_dat(GL,ML);
    system("pause");
    return 0;
}