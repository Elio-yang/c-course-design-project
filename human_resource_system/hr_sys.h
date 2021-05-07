/* declarations of hr system related
 * human_resource_system/hr_sys.h
 * @author Yang Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/3/19
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
#include <stdbool.h>
#include "../tools/print_color.h"
#include "../tools/process_bar.h"
#include "../tools/time_related.h"
#include "../tools/quick_sort.h"
#include "hr_repl.h"
#include <pthread.h>
#include <sys/wait.h>
#include <errno.h>

#define UNIX
//#define filename "hr.txt"
// recd length in hr.txt
#define hr_info_len 71
#define comp_info_len  301
#define maxcomlen 255
#define get_head(List) ((List)->head->next)
#define get_pid(staff) ((staff)->pid)
#define get_wid(staff) ((staff)->wid)
#define get_salary(staff) ((staff)->salary)
#define get_name(staff) ((staff)->name)
/*-----------------------------------basic defs---------------------------------------*/

/* all positions(RANK) */
typedef enum {
        BOSS = 0,
        MANAGER,
        BARTENDER,
        COOK,
        CLEANER,
        CASHIER,
        WAREHOUSEMAN,
        FINANCE
} Position;

typedef enum {
        MALE,
        FEMALE
} Gender;

/* used to sort */
typedef enum {
        NAME=0,
        PID,
        WID,
        DATE,
        SALARY
}Field;

typedef struct complain {
        char name[32];
        FormatTime time;
        char info[255];
        struct complain *next;
} Complaint_record;

typedef struct COMP_INFO {
        int fd;
        uint32_t cnt;
        int dirty;
        Complaint_record *head;
        char filename[255];
} comp_list;
/* privilege level*/
typedef enum {
        SUPERUSER = 0,
        ADMIN = 2,
        USERS = 3
} PL;
/* information of a staff */
typedef struct staff {
        char name[32];
        char hire_time[32];
        Gender gender;
        /* 职位 */
        Position rank;
        /* manage privilege level*/
        PL MPL;
        /* personal id  */
        char pid[15];
        /* working id  */
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
        char filename[255];
} hr_list;
//all human resource information
extern hr_list *HR_LIST;
extern comp_list *COMP_LIST;

/*-----------------------------------setter & getter---------------------------------------*/
extern  void set_name(Staff *staff, const char *name);

extern  void set_hire_time(Staff *staff, const char *time);

extern  void set_gender(Staff *staff, const char *gender);

extern  void set_rank(Staff *staff, const char *rank);

extern  void set_pid(Staff *staff, const char *pid);

extern  void set_wid(Staff *staff, const char *wid);

extern  void set_salary(Staff *staff, const char *salary);
/* 0 for success &-1 for failure */
extern  int set_mpl(Staff *staff, const char *mpl);

extern  Complaint_record *build_recd(FormatTime *ft, const char *info);

extern  void _add_complaint_recd(Staff *staff, Complaint_record *recd);

extern  Staff *staff_init(Staff *staff, char info[hr_info_len]);

extern  Complaint_record *comp_init(Complaint_record*comp,char info[comp_info_len]);


extern  char *get_time(Staff *staff);

extern  char *get_gender(Staff *staff);

extern  char *get_rank(Staff *staff);

extern  char *get_mpl(Staff *staff);
/*-----------------------------------APIs----------------------------------------------*/
__attribute__((unused)) extern  bool switch_to_hr_sys(Staff *staff);

extern  void load_hr_file(const char*filename);

extern  void load_comp_file(const char *filename);

extern  void sys_init();

__attribute__((unused)) extern  void get_authority();

extern  void print_worker_info(Staff *staff);

extern  bool passwd_check(const char *passwd);

extern Staff *query_by_wid(const char *id);

extern void show_a_query_info(Staff *staff);


extern Staff *query_by_name(const char *name);

extern Staff *query_by_pid (const char *pid);

extern  void select_header_all();

extern  void print_f_select_all(Staff *staff);

extern  void select_header_gender();

extern  void print_f_select_gender(Staff *staff);

extern  void select_header_rank();

extern  void print_f_select_rank(Staff *staff);

extern  void select_by_gender(Gender gender);

extern  void select_by_rank(Position rank);

extern  void select_name();

extern  void select_gender();

extern  void select_pid();

extern  void select_wid();

extern  void select_date();

extern  void select_rank();

extern  void select_all();

extern void sort_by(Field field,int direction);

extern void _insert_worker(Staff *staff);

extern void insert_worker(
        const char* name,
        const char* date,
        const char* gender,
        const char* rank,
        const char* mpl,
        const char* pid,
        const char* wid,
        const char* salary
);

extern void _remove_worker(Staff *staff);

__attribute__((unused)) extern bool remove_worker(const char *wid);

extern void flush_disk();

extern void free_hr_list();

extern void exit_hr_sys();

extern void sync_hr_sys();

extern void add_complaint(const char*wid,const char *info);

#endif
