/*
 * @author Yang Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/3/19
 * 酒吧人力资源信息模块
  1. 【增加】增加一条员工信息，可以从文件读入职员表，也可以终端输入一条员工信息。
  2. 【修改】更改一条员工信息（即更改各个字段）。
  3. 【删除】删除一条员工信息。
  4. 【查询】能根据员工信息表的各个字段，检索查询并以适当的格式打印出该员工的信息。并对于异常能够给予处理（如员工不存在等）。也能查询某员工的其他信息字段。
  5. 【排序】能够按照各个字段进行排序输出。
  6. 【投诉】增加某员工的一条投诉信息。
  7. 【打印】能打印所有的人员信息。
  8. 【永久化】能把最新的员工信息，从内存输出存储到磁盘文件上。
 *
 *
 *
 */
#ifndef HR_SYS_H
#define HR_SYS_H

#include <stdint.h>
#include <features.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tools/print_color.h"
#include "tools/process_bar.h"
#include "tools/time_related.h"

#define _UNIX
#define INLINE __always_inline
#define filename "hr.txt"
// recd lenth in hr.txt
#define infolen 71
#define get_head(List) ((List)->head->next)
#define get_pid(staff) ((staff)->pid)
#define get_wid(staff) ((staff)->wid)
#define get_salary(staff) ((staff)->salary)
#define get_name(staff) ((staff)->name)
/*-----------------------------------basic defs---------------------------------------*/

/*所有员工的职位*/
typedef enum {
        BOSS = 0,
        MANAGER,
        BARTENDER,/*调酒师*/
        COOK,
        CLEANER,/*保洁*/
        CASHIER,/*收银*/
        WAREHOUSEMAN,/*仓库管理员*/
        FINANCE/*财务*/
} Position;
/* 性别*/
typedef enum {
        MALE,
        FEMALE
} Gender;
/*投诉记录*/
typedef struct complain {
        char name[32];
        FormatTime time;
        char info[255];
        struct complain *next;
} Complaint_record;

typedef struct COMP_INFO{
        int fd;
        uint32_t cnt;
        int dirty;
        Complaint_record *head;

}comp_list;
/* privilege level*/
typedef enum {
        SUPERUSER=0,
        ADMIN=2,
        USERS=3
}PL;
/*一个员工的信息*/
typedef struct staff {
        char name[32];
        char hire_time[32];
        Gender gender;
        /* 职位 */
        Position rank;
        /* manage privilege level*/
        PL MPL;
        /* personal id 身份证 */
        char pid[15];
        /* working id 工号 */
        char wid[7];
        char salary[15];
        struct staff *next;
} Staff;

typedef struct HR_INFO {
        /* file descriptor of hr.txt */
        int fd;
        Staff *head;
        uint32_t cnt;
        /* dirty bit */
        int dirty;
} hr_list;
//all human resource information
hr_list *HR_LIST;
comp_list *COMP_LIST;

/*-----------------------------------setter & getter---------------------------------------*/
INLINE void set_name(Staff *staff, const char *name)
{
        memset(staff->name, 0, sizeof(staff->name));
        strcpy(staff->name, name);
}

INLINE void set_hire_time(Staff *staff, const char *time)
{
        memset(staff->hire_time, 0, sizeof(staff->hire_time));
        strcpy(staff->hire_time, time);
}

INLINE void set_gender(Staff *staff, const char *gender)
{
        if (strcmp(gender, "MALE") == 0) {
                staff->gender = MALE;
        } else if (strcmp(gender, "FEMALE") == 0) {
                staff->gender = FEMALE;
        } else {
                fprintf(stderr, "human resource info : %s gender error\n", staff->name);
                exit(0);
        }

}
INLINE void set_rank(Staff *staff, const char *rank)
{
        if (strcmp(rank, "0") == 0) {
                staff->rank = BOSS;
        } else if (strcmp(rank, "1") == 0) {
                staff->rank = MANAGER;
        } else if (strcmp(rank, "2") == 0) {
                staff->rank = BARTENDER;
        } else if (strcmp(rank, "3") == 0) {
                staff->rank = COOK;
        } else if (strcmp(rank, "4") == 0) {
                staff->rank = CLEANER;
        } else if (strcmp(rank, "5") == 0) {
                staff->rank = CASHIER;
        } else if (strcmp(rank, "6") == 0) {
                staff->rank = WAREHOUSEMAN;
        } else if (strcmp(rank, "7") == 0) {
                staff->rank = FINANCE;
        } else {
                fprintf(stderr, "human resource info : %s rank error\n", staff->name);
                exit(0);
        }
}

INLINE void set_pid(Staff *staff, const char *pid)
{
        memset(staff->pid, 0, sizeof(staff->pid));
        strcpy(staff->pid, pid);
}

INLINE void set_wid(Staff *staff, const char *wid)
{
        memset(staff->wid, 0, sizeof(staff->wid));
        strcpy(staff->wid, wid);
}

INLINE void set_salary(Staff *staff, const char *salary)
{
        memset(staff->salary, 0, sizeof(staff->salary));
        strcpy(staff->salary, salary);
}

/* 0 for success &-1 for failure */
INLINE int set_mpl(Staff *staff, const char *mpl)
{
        uint pl= atoi(mpl);
        switch (pl){
                case 0: {
                        staff->MPL = SUPERUSER;
                        break;
                }
                case 2:{
                        staff->MPL = ADMIN;
                        break;
                }
                case 3:{
                        staff->MPL = USERS;
                        break;
                }
                default:{
                        fprintf(stderr,"Wrong privilege code.");
                        return -1;
                }
        }
        return 0;
}
INLINE Complaint_record *build_recd(FormatTime *ft, const char *info)
{
        Complaint_record *recd =(Complaint_record*)malloc(sizeof(*recd));
        memcpy(&recd->time,ft, sizeof(*ft));
        strcpy(recd->info,info);
        recd->next=NULL;
}

INLINE void _add_complaint_recd(Staff *staff, Complaint_record *recd);

INLINE Staff *staff_init(Staff *staff, char info[infolen])
{

        char *name = strtok(info, " ");
        char *hire_time = strtok(NULL, " ");
        char *gender = strtok(NULL, " ");
        char *rank = strtok(NULL, " ");
        char *mpl = strtok(NULL," ");
        char *pid = strtok(NULL, " ");
        char *wid = strtok(NULL, " ");
        char *salary = strtok(NULL, "\r");

        set_name(staff, name);
        set_hire_time(staff, hire_time);
        set_gender(staff, gender);
        set_rank(staff, rank);
        set_mpl(staff,mpl);
        set_pid(staff, pid);
        set_wid(staff, wid);
        set_salary(staff, salary);

        return staff;

}


INLINE char *get_time(Staff *staff)
{
        char *t = (char *) malloc(sizeof(char) * 32);
        int time = atoi(staff->hire_time);
        int year = time / 10000;
        sprintf(t,"%d",year);
        t[4] = '-';
        t[7] = '-';
        int month = (time % 10000) / 100;
        if (month >= 10) {
                sprintf(t+5,"%d",month);
        } else {
                t[5] = '0';
                t[6] = month + '0';
        }
        int day = time % 100;
        if (day >= 0) {
                sprintf(t+8,"%d",day);
        } else {
                t[8] = '0';
                t[9] = day + '0';
        }
        t[10] = '\0';
        return t;

}

INLINE char *get_gender(Staff *staff)
{
        if (staff->gender == MALE) {
                return "Male";
        } else {
                return "Female";
        }
}

INLINE char *get_rank(Staff *staff)
{
        switch (staff->rank) {

                case BOSS:
                        return "BOSS";
                case MANAGER:
                        return "MANAGER";
                case BARTENDER:
                        return "BARTENDER";
                case COOK:
                        return "COOK";
                case CLEANER:
                        return "CLEANER";
                case CASHIER:
                        return "CASHIER";
                case WAREHOUSEMAN:
                        return "WAREHOUSEMAN";
                case FINANCE:
                        return "FINANCE";
        }
}

INLINE char *get_mpl(Staff *staff)
{
        switch (staff->MPL) {
                case SUPERUSER:{
                        return "SUPERUSER";
                }
                case ADMIN:{
                        return "ADMIN";
                }
                case USERS:{
                        return "USERS";
                }
        }
}

/*-----------------------------------APIs----------------------------------------------*/

INLINE void load_hr_file()
{
#ifdef _UNIX
        int fd = open(filename, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
#endif
#ifdef MINGW
        int fd = open(filename, O_RDWR | O_CREAT);
#endif
        if (fd == -1) {
                fprintf(stderr, "File %s open failed, human resource system init failed\n", filename);
                exit(EXIT_FAILURE);
        }
        HR_LIST = (hr_list *) malloc(sizeof(*HR_LIST));
        HR_LIST->fd = fd;
        HR_LIST->head = (Staff *) malloc(sizeof(Staff));
        HR_LIST->cnt = 0;
        HR_LIST->dirty=0;

        Staff *ptr = HR_LIST->head;
        ptr->next = NULL;

        char info[infolen];
        // the last two ch is \0d \0a --->\r\n
        while (read(fd, info, infolen)) {
                info[infolen - 1] = '\0';
                Staff *staff = (Staff *) malloc(sizeof(*staff));
                staff = staff_init(staff, info);
                staff->next = NULL;
                Staff *next = ptr->next;
                ptr->next = staff;
                staff->next = next;
                ptr = HR_LIST->head;
                ++HR_LIST->cnt;
        }
}

INLINE void hr_sys_init()
{
        //process_bar("loading hr system.");
        load_hr_file();
        usleep(1000*1000);
        printf(BOLD"*----------------------------------------------------*\n"NONE
               BOLD"|  "BLINK UNDERLINE"Human resource system successfully initialized!"NONE"   |\n"NONE
               BOLD"*----------------------------------------------------*\n\n"NONE );
}

INLINE void print_worker_info(Staff *staff)
{
        printf(""
               "+----------------------------------------------------+\n"
               "|  NAME      :\t%-20s                 |\n"
               "|  HIRE TIME :\t%-20s                 |\n"
               "|  GENDER    :\t%-20s                 |\n"
               "|  RANK      :\t%-20s                 |\n"
               "|  MPL       :\t%-20s                 |\n"
               "|  PID       :\t%-20s                 |\n"
               "|  WID       :\t%-20s                 |\n"
               "|  SALARY    :\t%-20s                 |\n"
               "+----------------------------------------------------+\n",
               staff->name, get_time(staff), get_gender(staff), get_rank(staff),get_mpl(staff),get_pid(staff),
               get_wid(staff), get_salary(staff));
}

Staff *query_by_wid(const char *id)
{

        Staff *head = get_head(HR_LIST);
        while (head != NULL) {
                if (strcmp(head->wid, id) == 0) {
                        printf("worker with id : %s found.\n", id);
                        return head;
                }
                head = head->next;
        }
        printf("worker with id : %s not found\n", id);
        return NULL;

}

Staff *query_by_name(const char *name)
{
        Staff *head =get_head(HR_LIST);
        while (head!=NULL){
                if(strcmp(name,head->name)==0){
                        printf("worker with name : %s found.\n",name);
                        return head;
                }
                head=head->next;
        }
        printf("worker with name : %s not found\n",name);
        return NULL;
}


INLINE void print_f_select_all(Staff *staff)
{
        printf(""
               "|  NAME      :\t%-20s                 |\n"
               "|  HIRE TIME :\t%-20s                 |\n"
               "|  GENDER    :\t%-20s                 |\n"
               "|  RANK      :\t%-20s                 |\n"
               "|  PID       :\t%-20s                 |\n"
               "|  WID       :\t%-20s                 |\n"
               "|  SALARY    :\t%-20s                 |\n"
               "+----------------------------------------------------+\n",
               staff->name, get_time(staff), get_gender(staff), get_rank(staff), get_pid(staff),
               get_wid(staff), get_salary(staff));
}

INLINE void print_f_select_gender(Staff *staff)
{
        printf(""
               "|  NAME      :\t%-20s                 |\n"
               "|  GENDER    :\t%-20s                 |\n"
               "+----------------------------------------------------+\n",
               staff->name, get_gender(staff));
}
INLINE void print_f_select_rank(Staff *staff)
{
        printf(""
               "|  NAME      :\t%-20s                 |\n"
               "|  RANK      :\t%-20s                 |\n"
               "+----------------------------------------------------+\n",
               staff->name,get_rank(staff));
}
INLINE void select_by_gender(Gender gender)
{
        Staff *head = HR_LIST->head->next;
        printf("+----------------------------------------------------+\n");
        while (head!=NULL){
                if(head->gender==gender){
                        print_f_select_gender(head);
                }
                head=head->next;
        }
}
INLINE void select_by_rank(Position rank)
{
        Staff *head = HR_LIST->head->next;
        printf("+----------------------------------------------------+\n");
        while (head!=NULL){
                if(head->rank==rank){
                        print_f_select_rank(head);
                }
                head=head->next;
        }

}
INLINE void select_name()
{

}
INLINE void select_all()
{
        Staff *head=HR_LIST->head->next;
        printf("+----------------------------------------------------+\n");
        while (head!=NULL){
                print_f_select_all(head);
                head=head->next;
        }
}

void sort_by_name(const char *name);
void sort_by_pid(const char *pid);
void sort_by_salary(const char *salary);


void _insert_worker(Staff *staff)
{
        Staff *head=get_head(HR_LIST);
        staff->next=head->next;
        head->next=staff;
        ++HR_LIST->cnt;
        HR_LIST->dirty=1;
}

void insert_worker()
{
        Staff *staff=(Staff*)malloc(sizeof(*staff));

        char name[32];
        char hire_time[32];
        char gen[10];
        char ran[5];
        char mpl[5];
        Gender gender;
        Position rank;
        char pid[15];
        char wid[15];
        char salary[15];

        //TODO finish strict check way && improve input parser && exit way
        printf("Please enter new worker information:\n");
        printf("Name      > ");
        scanf("%s",name);
        fflush(stdin);

        printf("Hire time > ");
        scanf("%s",hire_time);
        fflush(stdin);

GENDER:
        printf("Gender    > ");
        scanf("%s",gen);
        fflush(stdin);


        if(strcmp(gen,"MALE")==0){
                gender=MALE;
        }
        else if(strcmp(gen,"FEMALE")==0){
                gender=FEMALE;
        }
        else{
                fprintf(stderr,"Gender error please re-input.\n");
                goto GENDER;
        }
RANK:
        printf("Rank      > ");
        scanf("%s",ran);
        fflush(stdin);
        if (strcmp(ran, "BOSS") == 0) {
                staff->rank = BOSS;
        } else if (strcmp(ran, "MANAGER") == 0) {
                staff->rank = MANAGER;
        } else if (strcmp(ran, "BARTENDER") == 0) {
                staff->rank = BARTENDER;
        } else if (strcmp(ran, "COOK") == 0) {
                staff->rank = COOK;
        } else if (strcmp(ran, "CLEANER") == 0) {
                staff->rank = CLEANER;
        } else if (strcmp(ran, "CASHIER") == 0) {
                staff->rank = CASHIER;
        } else if (strcmp(ran, "WAREHOUSEMAN") == 0) {
                staff->rank = WAREHOUSEMAN;
        } else if (strcmp(ran, "FINANCE") == 0) {
                staff->rank = FINANCE;
        } else {
                fprintf(stderr, "rank error please re-input.\n");
                goto RANK;
        }
MPL:
        printf("MPL     > ");
        scanf("%s",mpl);
        fflush(stdin);
        int pl = atoi(mpl);
        switch (pl) {
                case SUPERUSER:{
                        staff->MPL=SUPERUSER;
                        break;
                }
                case ADMIN:{
                        staff->MPL=ADMIN;
                        break;
                }
                case USERS:{
                        staff->MPL=USERS;
                        break;
                }
                default:{
                        fprintf(stderr,"mpl error please re-input\n");
                        goto MPL;
                }
        }
PID:
        printf("Pid       > ");
        scanf("%s",pid);
        fflush(stdin);
        if(strlen(pid)!=14 || strncmp(pid,"4023",4)!=0){
                fprintf(stderr,"pid error please re-input.\n");
                goto PID;
        }
WID:
        printf("Wid       > ");
        scanf("%s",wid);
        fflush(stdin);
        if(strlen(wid)!= 6 || atoi(wid)<=0){
                fprintf(stderr,"pid error please re-input.\n");
                goto WID;
        }

        //TODO CHECK
        printf("Salary    > ");
        scanf("%s",salary);


        strcpy(staff->name,name);
        strcpy(staff->hire_time,hire_time);
        staff->gender=gender;
        strcpy(staff->pid,pid);
        strcpy(staff->wid,wid);
        strcpy(staff->salary,salary);
        _insert_worker(staff);
}

void _remove_worker(Staff *staff)
{
        if(staff==NULL){
                return;
        }
        //TODO change to double link list
        Staff *head = HR_LIST->head;
        Staff *prev=head;
        Staff *pfirst=head->next;
        while(pfirst!=NULL){
                if(strcmp(pfirst->wid,staff->wid)==0) {
                        break;
                }
                prev=pfirst;
                pfirst=pfirst->next;
        }
        //head is this element
        prev->next=staff->next;
        staff->next=NULL;
        free(staff);
        --HR_LIST->cnt;
}
bool remove_worker(const char *wid)
{
        if(HR_LIST->cnt==0 ||
                (HR_LIST->cnt==1 && strcmp(wid,HR_LIST->head->next->wid)!=0)){
                fprintf(stderr,"Remove error no worker.\n");
                return false;
        }
        Staff *this = query_by_wid(wid);
        if(this!=NULL){
                _remove_worker(this);
                return true;
        }else{
                printf("No such worker with wid : %s\n",wid);
                return false;
        }
}


void flush_disk()
{
        // not modified
        if(HR_LIST->dirty==0){
                return;
        }
        int fd = HR_LIST->fd;
        lseek(fd,0,SEEK_SET);
        Staff *staff =get_head(HR_LIST);
        while (staff!=NULL){
                int len=0;
                char info[infolen];
                char *name=get_name(staff);
                char *hire_time=get_time(staff);
                char *gender = get_gender(staff);
                int rank =staff->rank;
                char *pid=get_pid(staff);
                char *wid=get_wid(staff);
                char *salary=get_salary(staff);
                len+=sprintf(info+len,"%s ",name);
                len+=sprintf(info+len,"%s ",hire_time);
                len+=sprintf(info+len,"%s ",gender);
                len+=sprintf(info+len,"%d ",rank);
                len+=sprintf(info+len,"%s ",pid);
                len+=sprintf(info+len,"%s ",wid);
                len+=sprintf(info+len,"%s ",salary);
                if(strlen(info)< (infolen -1)){
                        int diff = infolen -1 - strlen(info);
                        char buf[diff+1];
                        for(int i=0;i<diff+1;i++){
                                buf[i]=' ';
                        }
                        buf[diff+1]='\0';
                        len+=sprintf(info+len,"%s",buf);
                        len+=sprintf(info+len,"\r");
                }
                write(fd,info,infolen);
                staff=staff->next;
        }
        HR_LIST->fd = -1;
        close(fd);
}

void free_hr_list()
{
        Staff *ptr = HR_LIST->head;
        while (ptr->next != NULL) {
                Staff *staff = ptr->next;
                _remove_worker(staff);
        }
}

// called when exit the hr sys
void exit_hr_sys()
{
        flush_disk();
        free_hr_list();
        printf(BOLD"*----------------------------------------------------*\n"NONE
               BOLD"|  "BLINK UNDERLINE"Human resource system successfully exited!       "NONE"   |\n"NONE
               BOLD"*----------------------------------------------------*\n\n"NONE );
}

void sync_hr_sys()
{
        flush_disk();
}

void add_complaint(Complaint_record *recd);

#endif
