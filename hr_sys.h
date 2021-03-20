/*
 * 酒吧人力资源信息模块
 */

#ifndef HR_SYS_H
#define HR_SYS_H

#include <stdint.h>
#include <features.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define __always_inline inline __attribute__((always_inline))
#define __noinline __attribute__((noinline))
#define __noreturn __attribute__((noreturn))
#define INLINE __always_inline
#define filename "hr.txt"
#define infolen 58

/*-----------------------------------basic defs---------------------------------------*/

/*所有员工的职位*/
typedef enum {
        BOSS = 0,
        MANAGER,
        /*调酒师*/
        BARTENDER,
        COOK,
        /*保洁*/
        CLEANER,
        /*收银*/
        CASHIER,
        /*仓库管理员*/
        WAREHOUSEMAN,
        /*财务*/
        FINANCE
} Position;
/* 性别*/
typedef enum {
        MALE,
        FEMALE
} Gender;
/*投诉记录*/
typedef struct complain {
        char time[32];
        char info[255];
        struct complain *next;
} Complaint_record;
/*一个员工的信息*/
typedef struct staff {
        char name[32];
        char hire_time[32];
        Gender gender;
        /* 职位 */
        Position rank;
        /* personal id 身份证 */
        char pid[15];
        /* working id 工号 */
        char wid[7];
        char salary[15];

        struct staff *next;
        /* 投诉信息 */
        Complaint_record *recd_list;
} Staff;

typedef struct HR_INFO {
        /* file descriptor of hr.txt */
        int fd;
        Staff *head;
        uint8_t cnt;
        /* dirty bit */
        int dirty;
} hr_list;
//all human resource information
hr_list *HR_LIST;
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

INLINE void set_gendef(Staff *staff, const char *gender)
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

INLINE Complaint_record *build_recd(const char *time, const char *info);

INLINE void add_complaint_recd(Staff *staff, Complaint_record *recd);

INLINE Staff *staff_init(Staff *staff, char info[infolen])
{

        char *name = strtok(info, " ");
        char *hire_time = strtok(NULL, " ");
        char *gender = strtok(NULL, " ");
        char *rank = strtok(NULL, " ");
        char *pid = strtok(NULL, " ");
        char *wid = strtok(NULL, " ");
        char *salary = strtok(NULL, "\r\n");

        set_name(staff, name);
        set_hire_time(staff, hire_time);
        set_gendef(staff, gender);
        set_rank(staff, rank);
        set_pid(staff, pid);
        set_wid(staff, wid);
        set_salary(staff, salary);

        return staff;

}

char *get_time(Staff *staff)
{
        char *t = (char *) malloc(sizeof(char) * 32);
        int time = atoi(staff->hire_time);
        int year = time / 10000;
        itoa(year, t, 10);
        t[4] = '-';
        t[7] = '-';
        int month = (time % 10000) / 100;
        if (month >= 10) {
                itoa(month, t + 5, 10);
        } else {
                t[5] = '0';
                t[6] = month + '0';
        }
        int day = time % 100;
        if (day >= 0) {
                itoa(day, t + 8, 10);
        } else {
                t[8] = '0';
                t[9] = day + '0';
        }
        t[10] = '\0';
        return t;

}

char *get_gender(Staff *staff)
{
        if (staff->gender == MALE) {
                return "Male";
        } else {
                return "Female";
        }
}

char *get_rank(Staff *staff)
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

char *get_pid(Staff *staff)
{
        return staff->pid;
}

char *get_wid(Staff *staff)
{
        return staff->wid;
}

char *get_salary(Staff *staff)
{
        return staff->salary;
}
/*-----------------------------------APIs----------------------------------------------*/

void load_hr_file()
{
        int fd = open(filename, O_RDWR | O_CREAT);
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
                info[infolen - 2] = '\0';
                info[infolen - 1] = '\0';
                Staff *staff = (Staff *) malloc(sizeof(*staff));
                staff = staff_init(staff, info);
                staff->next = NULL;
                staff->recd_list=NULL;
                Staff *next = ptr->next;
                ptr->next = staff;
                staff->next = next;
                ptr = HR_LIST->head;
                ++HR_LIST->cnt;
        }
}

void hr_sys_init()
{
        load_hr_file();
        printf("*----------------------------------------------------*\n"
               "|  Human resource system successfully initialized.   |\n"
               "*----------------------------------------------------*\n\n");
}

void print_worker_info(Staff *staff)
{
        printf("+----------------------------------------------------+\n"
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

Staff *query_by_wid(uint32_t wid)
{
        char id[7];
        itoa(wid, id, 10);
        Staff *head = HR_LIST->head->next;
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
        Staff *head =HR_LIST->head->next;
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


void print_f_select(Staff *staff)
{
        printf("|  NAME      :\t%-20s                 |\n"
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

void select_all()
{
        Staff *head=HR_LIST->head->next;
        printf("+----------------------------------------------------+\n");
        while (head!=NULL){
                print_f_select(head);
                head=head->next;
        }

}

void sort_by_name(const char *name);
void sort_by_pid(const char *pid);
void sort_by_salary(const char *salary);


void insert_worker();
void remove_worker();


void flush_disk();



void add_complaint(Complaint_record *recd);

#endif
