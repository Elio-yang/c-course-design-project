/*
 * for_cpp/financial.cpp
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/5/5
 */

#include "financial.h"
#include "../for_cpp/quick_sort.h"

F_list *FI_LIST;
#define FI_INFO_LEN 71

void print_fisys_info()
{
        char *buf = ordinary_time();
        printf(""
               "*--------------------------------------------------------*\n"
               "| FI-system version  %s                 |\n"
               "| MIT License                                            |\n"
               "| https://github.com/Elio-yang/C-Course-Design           |\n"
               "| Copyright (c) 2021 Elio-yang  alone-yue jakiejoe       |\n"
               "*--------------------------------------------------------*\n"
               "<Enter> for usage hints.\n", buf);

}

void init_fi_sys()
{
        int fd= open(FINANCE_FILE,O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
        if (fd == -1) {
                fprintf(stderr, "File %s open failed.\n", FINANCE_FILE);
                exit(EXIT_FAILURE);
        }
        FI_LIST=(F_list*) malloc(sizeof(*FI_LIST));
        FI_LIST->fd=fd;
        FI_LIST->cnt=0;
        FI_LIST->dirty=0;
        FI_LIST->head=(Fi_node*) malloc(sizeof(Fi_node));

        char info[FI_INFO_LEN];
        Fi_node *ptr=FI_LIST->head;
        ptr->next=NULL;
        while(read(fd,info,FI_INFO_LEN)){
                DealType t;
                info[FI_INFO_LEN-1]='\0';

                Fi_node *node = (Fi_node*) malloc(sizeof(*node));
                char *name=strtok(info," ");
                char *price= strtok(NULL," ");
                char *type = strtok(NULL," ");
                if(strcmp(type,"0")==0){
                        t=ORDER;
                }
                else if(strcmp(type,"1")==0){
                        t=INPUT;
                }
                else if(strcmp(type,"2")==0){
                        t=HR;
                }
                char *time = strtok(NULL," ");

                strcpy(node->name,name);
                strcpy(node->price,price);
                node->type=t;
                strcpy(node->time,time);
                node->next=NULL;
                Fi_node *next=ptr->next;
                ptr->next=node;
                node->next=next;
                ptr=FI_LIST->head;
                ++FI_LIST->cnt;
        }

}

void update_finance_record(const char *name, const char *price, DealType type)
{
        Fi_node *node=(Fi_node*) malloc(sizeof(*node));

        char buf[32];
        time_t this_time = time(NULL);
        struct tm *t=localtime(&this_time);
        strftime(buf,32,"%Y%m%d%H%M%S",t);

        const char *time = buf;
        strcpy(node->time,time);
        strcpy(node->name,name);
        strcpy(node->price,price);
        node->type=type;

        Fi_node *head = FI_LIST->head;
        node->next=head->next;
        head->next=node;
        ++FI_LIST->cnt;
        FI_LIST->dirty=1;
}

void flush_fi_disk()
{
        if(FI_LIST->dirty==0){
                return;
        }
        close(FI_LIST->fd);
        FI_LIST->fd=-1;
        int fd;
        char cmd[100];
        int l = 0;
        char *filename = FINANCE_FILE;
        l += sprintf(cmd + l, "%s ", "rm");
        l += sprintf(cmd + l, "%s", filename);
        system(cmd);

        fd = open(filename, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
        if(fd==-1){
                fprintf(stderr, "File %s open failed, human resource system init failed\n",filename );
                exit(EXIT_FAILURE);
        }
        Fi_node *node=FI_LIST->head->next;
        while(node!=NULL){
                int len=0;
                char info[FI_INFO_LEN];
                char *name=node->name;
                char *price= node->price;
                int t=(int)node->type;
                char *time=node->time;

                len+= sprintf(info+len,"%s ",name);
                len+= sprintf(info+len,"%s ",price);
                len += sprintf(info+len,"%d ",t);
                len+= sprintf(info+len,"%s ",time);

                if (strlen(info) < (FI_INFO_LEN - 1)) {
                        int diff = FI_INFO_LEN - 1 - strlen(info);
                        char buf[diff + 1];
                        for (int i = 0; i < diff; i++) {
                                buf[i] = ' ';
                        }
                        buf[diff] = '\0';
                        len += sprintf(info + len, "%s", buf);
                        info[FI_INFO_LEN - 1] = '\n';
                }
                write(fd,info,FI_INFO_LEN);
                node=node->next;
        }
}

void print_financial_recd()
{
        Fi_node *p;
        for (int i = 0; i < 3; i++)
        {
                p = FI_LIST->head->next;
                if (i == 0)
                        printf(BOLD"--------------------ORDER_FINANCIAL_RECORD------------------------\n"NONE);
                if (i == 1)
                        printf(BOLD"--------------------WAREHOUSE_FINANCIAL_RECORD--------------------\n"NONE);
                if (i == 2)
                        printf(BOLD"--------------------HR_FINANCIAL_RECORD---------------------------\n"NONE);

                while (p != NULL)
                {
                        if (p->type == i)
                                printf("| %-20s%-12s%-8s                       |\n", p->time, p->name, p->price);
                        p = p->next;
                }
                printf("|----------------------------------------------------------------|\n");
        }
}
void query_from(const char *id1,const char *id2)
{
        Fi_node* t=FI_LIST->head->next;
        int cnt=1;
        int flag=0;
        while(t!=NULL){
                if(strcmp(t->time,id1)>=0&&strcmp(t->time,id2)<=0) {
                        printf("Record %-3d :%-15s %-8s %-8s %d\n", cnt++, t->time, t->name, t->price, t->type);
                        flag = 1;
                }
                t=t->next;
        }
        if(flag==0){
                printf(RED"Not Found\n" NONE);
        }

}

//时间作为订单号 用时间查询 时间是这个格式 20210404220834  年月日时分秒
void query_finance(const char *id)
{
        Fi_node* t=FI_LIST->head->next;
        int cnt=1;
        int flag=0;
        while(t!=NULL){
                if(strcmp(t->time,id)==0) {
                        printf("Record %-3d :%-15s %-8s %-8s %d\n", cnt++, t->time, t->name, t->price, t->type);
                        flag = 1;
                }
                t=t->next;
        }
        if(flag==0){
                printf(RED"Not Found\n" NONE);
        }

}

static int cmp_up_name(const void *A, const void *B) {
        return strcmp(((Fi_node *) A)->name, ((Fi_node *) B)->name);
}

static int cmp_d_name(const void *A, const void *B) {
        return strcmp(((Fi_node *) B)->name, ((Fi_node *) A)->name);
}

static int cmp_up_time(const void *A, const void *B) {
        return strcmp(((Fi_node *) A)->time, ((Fi_node *) B)->time);
}

static int cmp_d_time(const void *A, const void *B) {
        return strcmp(((Fi_node *) B)->time, ((Fi_node *) A)->time);
}

static int cmp_up_price(const void *A, const void *B) {
        return strcmp(((Fi_node *) A)->price, ((Fi_node *) B)->price);
}

static int cmp_d_price(const void *A, const void *B) {
        return strcmp(((Fi_node *) B)->price, ((Fi_node *) A)->price);
}
// 0 for a upper case
static int (*cmp_table[][2])(const void *, const void *) ={
        {cmp_up_name, cmp_d_name},
        {cmp_up_time,  cmp_d_time},
        {cmp_up_price,  cmp_d_price},
};

void sort_data_by(DealType type, int choice,int direction)
{

        //先搞一个Fi_node的数组，把链表输入到数组里
        //按哪个字段排序（choice: 0是名字 1是订单号 2是价格
        // 写三个cmp函数(qsort的那种）
        //直接调用sort() 排序这个在tools/quick_sort.h 里面 用法跟 qsort一致
        // 不太清楚可以看 human_resource_system/hr_sys.c 629行 函数 void sort_by(Field field, int direction)的方法
        if (type == 0)
                printf(BOLD"[>>>>>>Sorted by name<<<<<<]\n" NONE);
        else if (type == 1)
                printf(BOLD"[>>Sorted by order number<<]\n" NONE);
        else if (type == 2)
                printf(BOLD"[>>>>>>Sorted by price<<<<<]\n" NONE);

        if (type == ORDER)
                printf(BOLD"--------------------ORDER_FINANCIAL_RECORD------------------------\n"NONE);
        else if (type == INPUT)
                printf(BOLD"--------------------WAREHOUSE_FINANCIAL_RECORD--------------------\n"NONE);
        else if (type == HR)
                printf(BOLD"--------------------HR_FINANCIAL_RECORD---------------------------\n"NONE);



        Fi_node record[FI_LIST->cnt];
        Fi_node *p = FI_LIST->head->next;
        int num = 0;
        while (p != NULL)
        {
                if (p->type == type)
                        record[num++] = *p;
                p = p->next;
        }
        int (*cmp)(const void*, const void*)=cmp_table[choice][direction];
        sort(record, num, sizeof(Fi_node), cmp);
        for (int i = 0; i < num; i++)
                printf("| %-20s%-12s%-8s                       |\n", record[i].time, record[i].name, record[i].price);
        printf("|----------------------------------------------------------------|\n");

}

double double_price(char price[])
{
        int len = strlen(price);
        double count = 0;
        for (int i = 0; i < len; i++)
        {
                count *= 10;
                count += price[i];
        }
        return count;
}

//统计总的收入，支出，总利润
// HR INPUT 的为支出
// ORDER 的为收入
// 分三行打印即可
void statistic()
{
        double income = 0, expend = 0, profit = 0;
        Fi_node *p = FI_LIST->head->next;
        while (p != NULL)
        {
                if (p->type == 0){
                        income += atof(p->price);
                }
                else
                        expend += atof(p->price);
                p = p->next;
        }
        profit = income - expend;
        printf(BOLD"+--------------------Statistic--------------------+\n"NONE);
        printf("|The total income is %-10.2lf yuan              |\n", income);
        printf("|The total expend is %-10.2lf yuan              |\n", expend);
        printf("|The total profit is %-10.2lf yuan              |\n", profit);
        printf("+-------------------------------------------------+\n");
}


