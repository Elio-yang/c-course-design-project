/* declarations of hr system related
 * @author Yang Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/3/19

  酒吧人力资源信息模块
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
#include <stdbool.h>
#include "../tools/print_color.h"
#include "../tools/process_bar.h"
#include "../tools/time_related.h"
#include "../tools/quick_sort.h"
#include "hr_repl.h"
#include <pthread.h>
#include <sys/wait.h>

#define UNIX
#define INLINE inline
//#define filename "hr.txt"
// recd length in hr.txt
#define infolen 71
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
} hr_list;
//all human resource information
extern hr_list *HR_LIST;
extern comp_list *COMP_LIST;

/*-----------------------------------setter & getter---------------------------------------*/
extern INLINE void set_name(Staff *staff, const char *name);

extern INLINE void set_hire_time(Staff *staff, const char *time);

extern INLINE void set_gender(Staff *staff, const char *gender);

extern INLINE void set_rank(Staff *staff, const char *rank);

extern INLINE void set_pid(Staff *staff, const char *pid);

extern INLINE void set_wid(Staff *staff, const char *wid);

extern INLINE void set_salary(Staff *staff, const char *salary);
/* 0 for success &-1 for failure */
extern INLINE int set_mpl(Staff *staff, const char *mpl);

extern INLINE Complaint_record *build_recd(FormatTime *ft, const char *info);

extern INLINE void _add_complaint_recd(Staff *staff, Complaint_record *recd);

extern INLINE Staff *staff_init(Staff *staff, char info[infolen]);

extern INLINE char *get_time(Staff *staff);

extern INLINE char *get_gender(Staff *staff);

extern INLINE char *get_rank(Staff *staff);

extern INLINE char *get_mpl(Staff *staff);
/*-----------------------------------APIs----------------------------------------------*/
extern INLINE bool switch_to_hr_sys(Staff *staff);

extern INLINE void load_hr_file(const char*filename);

extern INLINE void sys_init();

__attribute__((unused)) extern INLINE void get_authority();

extern INLINE void print_worker_info(Staff *staff);

extern INLINE bool passwd_check(const char *passwd);

extern Staff *query_by_wid(const char *id);

extern void show_a_query_info(Staff *staff);


extern Staff *query_by_name(const char *name);

extern Staff *query_by_pid (const char *pid);

extern INLINE void select_header_all();

extern INLINE void print_f_select_all(Staff *staff);

extern INLINE void select_header_gender();

extern INLINE void print_f_select_gender(Staff *staff);

extern INLINE void select_header_rank();

extern INLINE void print_f_select_rank(Staff *staff);

extern INLINE void select_by_gender(Gender gender);

extern INLINE void select_by_rank(Position rank);

extern INLINE void select_name();

extern INLINE void select_gender();

extern INLINE void select_pid();

extern INLINE void select_wid();

extern INLINE void select_date();

extern INLINE void select_rank();

extern INLINE void select_all();

extern void sort_by(Field field,int direction);

extern void _insert_worker(Staff *staff);

extern void insert_worker();

extern void _remove_worker(Staff *staff);

__attribute__((unused)) extern bool remove_worker(const char *wid);

extern void flush_disk();

extern void free_hr_list();

extern void exit_hr_sys();

extern void sync_hr_sys();

extern void add_complaint(Complaint_record *recd);

#endif
