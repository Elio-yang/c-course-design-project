/*
 * implementation of hr system
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/4/12
 */

#include "hr_sys.h"
#include "../tools/regex_match.h"

hr_list *HR_LIST;
comp_list *COMP_LIST;
uint32_t init_hr_cnt;

static int cmp_up_name(const void *A, const void *B) {
        return strcmp(((Staff *) A)->name, ((Staff *) B)->name);
}

static int cmp_d_name(const void *A, const void *B) {
        return strcmp(((Staff *) B)->name, ((Staff *) A)->name);
}

static int cmp_up_pid(const void *A, const void *B) {
        return strcmp(((Staff *) A)->pid, ((Staff *) B)->pid);
}

static int cmp_d_pid(const void *A, const void *B) {
        return strcmp(((Staff *) B)->pid, ((Staff *) A)->pid);
}

static int cmp_up_wid(const void *A, const void *B) {
        return strcmp(((Staff *) A)->wid, ((Staff *) B)->wid);
}

static int cmp_d_wid(const void *A, const void *B) {
        return strcmp(((Staff *) B)->wid, ((Staff *) A)->wid);
}

static int cmp_up_date(const void *A, const void *B) {
        return strcmp(((Staff *) A)->hire_time, ((Staff *) B)->hire_time);
}

static int cmp_d_date(const void *A, const void *B) {
        return strcmp(((Staff *) B)->hire_time, ((Staff *) A)->hire_time);
}

static int cmp_up_sal(const void *A, const void *B) {
        return strcmp(((Staff *) A)->salary, ((Staff *) B)->salary);
}

static int cmp_d_sal(const void *A, const void *B) {
        return strcmp(((Staff *) B)->salary, ((Staff *) A)->salary);
}

/* used to pass to sort */
static int (*cmp_table[][2])(const void *, const void *) ={
        {cmp_up_name, cmp_d_name},
        {cmp_up_pid,  cmp_d_pid},
        {cmp_up_wid,  cmp_d_wid},
        {cmp_up_date, cmp_d_date},
        {cmp_up_sal,  cmp_d_sal}
};


/*-----------------------------------setter & getter---------------------------------------*/
void set_name(Staff *staff, const char *name) {
        memset(staff->name, 0, sizeof(staff->name));
        strcpy(staff->name, name);
}

void set_hire_time(Staff *staff, const char *time) {
        memset(staff->hire_time, 0, sizeof(staff->hire_time));
        strcpy(staff->hire_time, time);
}

void set_gender(Staff *staff, const char *gender) {
        if (strcmp(gender, "MALE") == 0) {
                staff->gender = MALE;
        } else if (strcmp(gender, "FEMALE") == 0) {
                staff->gender = FEMALE;
        } else {
                fprintf(stderr, "human resource info : %s gender error\n", staff->name);
                exit(0);
        }

}

void set_rank(Staff *staff, const char *rank) {
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

void set_pid(Staff *staff, const char *pid) {
        memset(staff->pid, 0, sizeof(staff->pid));
        strcpy(staff->pid, pid);
}

void set_wid(Staff *staff, const char *wid) {
        memset(staff->wid, 0, sizeof(staff->wid));
        strcpy(staff->wid, wid);
}

void set_salary(Staff *staff, const char *salary) {
        memset(staff->salary, 0, sizeof(staff->salary));
        strcpy(staff->salary, salary);
}

/* 0 for success &-1 for failure */
int set_mpl(Staff *staff, const char *mpl) {
        uint pl = atoi(mpl);
        switch (pl) {
                case 0: {
                        staff->MPL = SUPERUSER;
                        break;
                }
                case 2: {
                        staff->MPL = ADMIN;
                        break;
                }
                case 3: {
                        staff->MPL = USERS;
                        break;
                }
                default: {
                        fprintf(stderr, "Wrong privilege code.\n");
                        return -1;
                }
        }
        return 0;
}

Staff *staff_init(Staff *staff, char info[hr_info_len]) {

        char *name = strtok(info, " ");
        char *hire_time = strtok(NULL, " ");
        char *gender = strtok(NULL, " ");
        char *rank = strtok(NULL, " ");
        char *mpl = strtok(NULL, " ");
        char *pid = strtok(NULL, " ");
        char *wid = strtok(NULL, " ");
        char *salary = strtok(NULL, " ");

        set_name(staff, name);
        set_hire_time(staff, hire_time);
        set_gender(staff, gender);
        set_rank(staff, rank);
        set_mpl(staff, mpl);
        set_pid(staff, pid);
        set_wid(staff, wid);
        set_salary(staff, salary);

        return staff;

}

Complaint_record *comp_init(Complaint_record *comp, char info[comp_info_len]) {
        char *name = strtok(info, " ");
        char *time = strtok(NULL, " ");
        char *mesg = strtok(NULL, " ");
        strcpy(comp->name, name);
        strcpy(comp->time.whole_time, time);
        strcpy(comp->info, mesg);
        return comp;
}

char *get_time(Staff *staff) {
        char *t = (char *) malloc(sizeof(char) * 32);
        int time = atoi(staff->hire_time);
        int year = time / 10000;
        sprintf(t, "%d", year);
        t[4] = '-';
        t[7] = '-';
        int month = (time % 10000) / 100;
        if (month >= 10) {
                sprintf(t + 5, "%d", month);
        } else {
                t[5] = '0';
                t[6] = month + '0';
        }
        int day = time % 100;
        if (day >= 0) {
                sprintf(t + 8, "%d", day);
        } else {
                t[8] = '0';
                t[9] = day + '0';
        }
        t[10] = '\0';
        return t;

}

char *get_gender(Staff *staff) {
        if (staff->gender == MALE) {
                return "MALE";
        } else {
                return "FEMALE";
        }
}

char *get_rank(Staff *staff) {
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

char *get_mpl(Staff *staff) {
        switch (staff->MPL) {
                case SUPERUSER: {
                        return "SUPERUSER";
                }
                case ADMIN: {
                        return "ADMIN";
                }
                case USERS: {
                        return "USERS";
                }
        }
}

/*-----------------------------------APIs----------------------------------------------*/
__attribute__((unused))  bool switch_to_hr_sys(Staff *staff) {
        if (staff->MPL == USERS) {
                fprintf(stderr, "privilege level not enough.\n");
                return false;
        } else {
                printf("%s switched to human resource system.\n", staff->name);
                return true;
        }

}

void load_hr_file(const char *filename) {
#ifdef UNIX
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
        HR_LIST->dirty = 0;
        strcpy(HR_LIST->filename, filename);

        Staff *ptr = HR_LIST->head;
        ptr->next = NULL;

        char info[hr_info_len];
        // the last two ch is \0d \0a --->\r\n
        while (read(fd, info, hr_info_len)) {
                info[hr_info_len - 1] = '\0';
                Staff *staff = (Staff *) malloc(sizeof(*staff));
                staff = staff_init(staff, info);
                staff->next = NULL;
                Staff *next = ptr->next;
                ptr->next = staff;
                staff->next = next;
                ptr = HR_LIST->head;
                ++HR_LIST->cnt;
        }
        init_hr_cnt = HR_LIST->cnt;
}

void load_comp_file(const char *filename) {
#ifdef UNIX
        int fd = open(filename, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
#endif
#ifdef MINGW
        int fd = open(filename, O_RDWR | O_CREAT);
#endif

        if (fd == -1) {
                fprintf(stderr, "File %s open failed.\n", filename);
                exit(EXIT_FAILURE);
        }
        COMP_LIST = (comp_list *) malloc(sizeof(*COMP_LIST));
        COMP_LIST->fd = fd;
        COMP_LIST->head = (Complaint_record *) malloc(sizeof(Complaint_record));
        COMP_LIST->cnt = 0;
        COMP_LIST->dirty = 0;
        strcpy(COMP_LIST->filename, filename);
        Complaint_record *ptr = COMP_LIST->head;
        ptr->next = NULL;

        char info[comp_info_len];
        // the last two ch is \0d \0a --->\r\n
        while (read(fd, info, comp_info_len)) {
                info[comp_info_len - 1] = '\0';
                Complaint_record *comp = (Complaint_record *) malloc(sizeof(*comp));
                comp = comp_init(comp, info);
                comp->next = NULL;
                Complaint_record *next = ptr->next;
                ptr->next = comp;
                comp->next = next;
                ptr = COMP_LIST->head;
                ++COMP_LIST->cnt;
        }
}

void sys_init() {
        InputBuffer *file_input = new_input_buffer();

        label1:
        printf("hr_filename > :");
        read_input(file_input);
        int flag1 = regex_match_with(file_input->buf, TXT_FILE_REG);
        int flag2;
        char *relname2;
        if (flag1 == -1) {
                fprintf(stderr, "Please input a correct xxx.txt file without any special characters.\n");
                goto label1;

        }
        char *relname1 = strtok(file_input->buf, " ");
        load_hr_file(relname1);

        label2:
        printf("comp_filename > :");
        read_input(file_input);
        flag2 = regex_match_with(file_input->buf, TXT_FILE_REG);
        if (flag2 == -1) {
                fprintf(stderr, "Please input a correct xxx.txt file without any special characters.\n");
                goto label2;

        }
        relname2 = strtok(file_input->buf, " ");
        load_comp_file(relname2);

        usleep(1000 * 1000);
        printf(BOLD"*----------------------------------------------------*\n"NONE
               BOLD"|  "BLINK UNDERLINE"Human resource system successfully initialized!"NONE"   |\n"NONE
               BOLD"*----------------------------------------------------*\n\n"NONE);
}

pthread_mutex_t REPL_LOCK = PTHREAD_MUTEX_INITIALIZER;

__attribute__((unused)) extern void get_authority() {
        sys_init();
        int status;
        pthread_mutex_lock(&REPL_LOCK);
        if (!fork()) {
                char *const argv[] = {
                        "login",
                        NULL
                };
                execv("/tmp/tmp.pIdETgMIBR/cmake-build-debug-remote-host/../bin/login", argv);
        }
        wait(&status);
        if (status == 2) {
                exit_hr_sys();
        } else {
                pthread_mutex_unlock(&REPL_LOCK);
        }
}

void print_worker_info(Staff *staff) {
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
               staff->name, get_time(staff), get_gender(staff), get_rank(staff), get_mpl(staff), get_pid(staff),
               get_wid(staff), get_salary(staff));
}

Staff *query_by_wid(const char *id) {

        Staff *head = get_head(HR_LIST);
        while (head != NULL) {
                if (strcmp(head->wid, id) == 0) {
                        printf("Staff with wid : "BOLD"%s"NONE" found.\n", id);
                        return head;
                }
                head = head->next;
        }
        printf("Staff with wid : "BOLD"%s"NONE" not found\n", id);
        return NULL;

}

Staff *query_by_pid(const char *pid) {
        Staff *head = get_head(HR_LIST);
        while (head != NULL) {
                if (strcmp(head->pid, pid) == 0) {
                        printf("Staff with pid : "BOLD"%s"NONE" found.\n", pid);
                        return head;
                }
                head = head->next;
        }
        printf("Staff with pid : "BOLD"%s"NONE" not found\n", pid);
        return NULL;
}

void show_a_query_info(Staff *staff) {
        select_header_all();
        print_f_select_all(staff);
        printf("+----------+----------------+---------+--------------+-----------------+----------+--------------+\n");
}

Staff *query_by_name(const char *name) {
        Staff *head = get_head(HR_LIST);
        while (head != NULL) {
                if (strcmp(name, head->name) == 0) {
                        printf("Staff with name : "BOLD"%s"NONE" found.\n", name);
                        return head;
                }
                head = head->next;
        }
        printf("Staff with name : " BOLD "%s" NONE " not found.\n", name);
        return NULL;
}

void select_header_all() {
        printf(""
               "+----------+----------------+---------+--------------+-----------------+----------+--------------+\n"
               "| Name     | Hire time      | Gender  | Rank         | Pid             | Wid      | Salary       |\n"
               "+----------+----------------+---------+--------------+-----------------+----------+--------------+\n"
        );

}

void print_f_select_all(Staff *staff) {
        char *name = staff->name;
        char *time = get_time(staff);
        char *gender = get_gender(staff);
        char *rank = get_rank(staff);
        char *pid = get_pid(staff);
        char *wid = get_wid(staff);
        char *salary = get_salary(staff);
        printf(""
               "| %-9s| %-15s| %-8s| %-13s| %-16s| %-9s| %-13s|\n",
               name, time, gender, rank, pid, wid, salary);
}

void select_header_gender() {
        printf(""
               "+----------+---------+\n"
               "| Name     | Gender  |\n"
               "+----------+---------+\n"
        );
}

void print_f_select_gender(Staff *staff) {
        printf("| %-9s| %-8s|\n",
               staff->name, get_gender(staff));
}

void select_header_rank() {
        printf(""
               "+----------+--------------+\n"
               "| Name     | Rank         |\n"
               "+----------+--------------+\n"
        );
}

void print_f_select_rank(Staff *staff) {
        printf("| %-9s| %-13s|\n",
               staff->name, get_rank(staff));
}

void select_by_gender(Gender gender) {
        Staff *head = HR_LIST->head->next;
        select_header_gender();
        while (head != NULL) {
                if (head->gender == gender) {
                        print_f_select_gender(head);
                }
                head = head->next;
        }
        printf("+----------+---------+\n");
}

void select_by_rank(Position rank) {
        Staff *head = HR_LIST->head->next;
        select_header_rank();
        while (head != NULL) {
                if (head->rank == rank) {
                        print_f_select_rank(head);
                }
                head = head->next;
        }
        printf("+----------+--------------+\n");
}

void select_name() {
        printf(""
               "+----------+\n"
               "| Name     |\n"
               "+----------+\n"
        );
        Staff *head = HR_LIST->head->next;
        while (head != NULL) {
                printf("| %-9s|\n", head->name);
                head = head->next;
        }
        printf("+----------+\n");
}

void select_gender() {
        printf(""
               "+----------+---------+\n"
               "| Name     | Gender  |\n"
               "+----------+---------+\n"
        );
        Staff *head = HR_LIST->head->next;
        while (head != NULL) {
                printf("| %-9s| %-8s|\n", head->name, get_gender(head));
                head = head->next;
        }
        printf("+----------+---------+\n");
}

void select_pid() {
        printf(""
               "+----------+-----------------+\n"
               "| Name     | Pid             |\n"
               "+----------+-----------------+\n"
        );
        Staff *head = HR_LIST->head->next;
        while (head != NULL) {
                printf("| %-9s| %-16s|\n", head->name, get_pid(head));
                head = head->next;
        }
        printf("+----------+-----------------+\n");
}

void select_wid() {
        printf(""
               "+----------+----------+\n"
               "| Name     | Wid      |\n"
               "+----------+----------+\n"
        );
        Staff *head = HR_LIST->head->next;
        while (head != NULL) {
                printf("| %-9s| %-9s|\n", head->name, get_wid(head));
                head = head->next;
        }
        printf("+----------+----------+\n");
}

void select_date() {
        printf(""
               "+----------+----------------+\n"
               "| Name     | Hire time      |\n"
               "+----------+----------------+\n"
        );
        Staff *head = HR_LIST->head->next;
        while (head != NULL) {
                printf("| %-9s| %-15s|\n", head->name, get_time(head));
                head = head->next;
        }
        printf("+----------+----------------+\n");
}

void select_rank() {
        printf(""
               "+----------+--------------+\n"
               "| Name     | Rank         |\n"
               "+----------+--------------+\n"
        );
        Staff *head = HR_LIST->head->next;
        while (head != NULL) {
                printf("| %-9s| %-13s|\n", head->name, get_rank(head));
                head = head->next;
        }
        printf("+----------+--------------+\n");
}

void select_all() {
        Staff *head = HR_LIST->head->next;
        select_header_all();
        while (head != NULL) {
                print_f_select_all(head);
                head = head->next;
        }
        printf("+----------+----------------+---------+--------------+-----------------+----------+--------------+\n");
}

/*
 * sort the information by field and print them
 * direction: 0 for an increase order (-i)
 * */
void sort_by(Field field, int direction) {
        int (*cmp)(const void *, const void *) =cmp_table[field][direction];
        select_header_all();
        Staff array[HR_LIST->cnt];
        Staff *pf = get_head(HR_LIST);
        for (int i = 0; i < HR_LIST->cnt; i++) {
                array[i] = *pf;
                pf = pf->next;
        }
        sort(array, HR_LIST->cnt, sizeof(Staff), cmp);
        for (int i = 0; i < HR_LIST->cnt; i++) {
                Staff staff = array[i];
                printf(""
                       "| %-9s| %-15s| %-8s| %-13s| %-16s| %-9s| %-13s|\n",
                       staff.name, get_time(&staff), get_gender(&staff), get_rank(&staff), get_pid(&staff),
                       get_wid(&staff), get_salary(&staff));
        }
        printf("+----------+----------------+---------+--------------+-----------------+----------+--------------+\n");
}

void _insert_worker(Staff *staff) {
        Staff *head = get_head(HR_LIST);
        staff->next = head->next;
        head->next = staff;
        ++HR_LIST->cnt;
        HR_LIST->dirty = 1;
}

void _insert_comp(Complaint_record *comp) {
        Complaint_record *head = get_head(COMP_LIST);
        comp->next = head->next;
        head->next = comp;
        ++COMP_LIST->cnt;
        COMP_LIST->dirty = 1;
}

void insert_worker(
        const char *name,
        const char *date,
        const char *gen,
        const char *ran,
        const char *mpl,
        const char *pid,
        const char *wid,
        const char *salary
) {
        Staff *staff = (Staff *) malloc(sizeof(*staff));

        Gender gender;
        if (strcmp(gen, "MALE") == 0) {
                gender = MALE;
        } else if (strcmp(gen, "FEMALE") == 0) {
                gender = FEMALE;
        }


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
        }

        int pl = atoi(mpl);
        switch (pl) {
                case SUPERUSER: {
                        staff->MPL = SUPERUSER;
                        break;
                }
                case ADMIN: {
                        staff->MPL = ADMIN;
                        break;
                }
                case USERS: {
                        staff->MPL = USERS;
                        break;
                }
        }


        strcpy(staff->name, name);
        strcpy(staff->hire_time, date);
        staff->gender = gender;
        strcpy(staff->pid, pid);
        strcpy(staff->wid, wid);
        strcpy(staff->salary, salary);
        printf("inserted Staff information:\n");
        show_a_query_info(staff);
        _insert_worker(staff);

}

void _remove_worker(Staff *staff) {
        if (staff == NULL) {
                return;
        }
        Staff *head = HR_LIST->head;
        Staff *prev = head;
        Staff *pfirst = head->next;
        while (pfirst != NULL) {
                if (strcmp(pfirst->wid, staff->wid) == 0) {
                        break;
                }
                prev = pfirst;
                pfirst = pfirst->next;
        }
        //head is this element
        prev->next = staff->next;
        staff->next = NULL;
        free(staff);
        HR_LIST->dirty = 1;
        --HR_LIST->cnt;
}

__attribute__((unused)) bool remove_worker(const char *wid) {
        if (HR_LIST->cnt == 0 ||
            (HR_LIST->cnt == 1 && strcmp(wid, HR_LIST->head->next->wid) != 0)) {
                fprintf(stderr, "Remove error no worker.\n");
                return false;
        }
        Staff *this = query_by_wid(wid);
        if (this != NULL) {
                _remove_worker(this);
                return true;
        } else {
                printf("No such worker with wid : %s\n", wid);
                return false;
        }
}

void flush_disk() {

        // not modified
        if (HR_LIST->dirty == 0) {
                return;
        }
        int hr_fd = HR_LIST->fd;
        close(hr_fd);
        HR_LIST->fd = -1;

        char cmd[100];
        int l = 0;
        char *hrfilename = HR_LIST->filename;
        l += sprintf(cmd + l, "%s ", "rm");
        l += sprintf(cmd + l, "%s", hrfilename);
        system(cmd);
#ifdef UNIX
        hr_fd = open(hrfilename, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
#endif
#ifdef MINGW
        hr_fd = open(hrfilename, O_RDWR | O_CREAT);
#endif
        if (hr_fd == -1) {
                fprintf(stderr, "File %s open failed, human resource system init failed\n", hrfilename);
                exit(EXIT_FAILURE);
        }
        Staff *staff = get_head(HR_LIST);
        while (staff != NULL) {
                int len = 0;
                char info[hr_info_len];
                char *name = get_name(staff);
                char *hire_time = staff->hire_time;
                char *gender = get_gender(staff);
                int rank = staff->rank;
                int mpl = staff->MPL;
                char *pid = get_pid(staff);
                char *wid = get_wid(staff);
                char *salary = get_salary(staff);
                len += sprintf(info + len, "%s ", name);
                len += sprintf(info + len, "%s ", hire_time);
                len += sprintf(info + len, "%s ", gender);
                len += sprintf(info + len, "%d ", rank);
                len += sprintf(info + len, "%d ", mpl);
                len += sprintf(info + len, "%s ", pid);
                len += sprintf(info + len, "%s ", wid);
                len += sprintf(info + len, "%s ", salary);
                if (strlen(info) < (hr_info_len - 1)) {
                        int diff = hr_info_len - 1 - strlen(info);
                        char buf[diff + 1];
                        for (int i = 0; i < diff; i++) {
                                buf[i] = ' ';
                        }
                        buf[diff] = '\0';
                        len += sprintf(info + len, "%s", buf);
                        info[hr_info_len - 1] = '\n';
                }
                write(hr_fd, info, hr_info_len);
                staff = staff->next;
        }

        if (COMP_LIST->dirty == 0) {
                return;
        }
        int comp_fd = COMP_LIST->fd;
        close(comp_fd);
        char *compfilename = COMP_LIST->filename;
        l = 0;
        l += sprintf(cmd + l, "%s ", "rm");
        l += sprintf(cmd + l, "%s", compfilename);
        system(cmd);

#ifdef UNIX
        comp_fd = open(compfilename, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
#endif
#ifdef MINGW
        comp_fd = open(compfilename, O_RDWR | O_CREAT);
#endif
        if (comp_fd == -1) {
                fprintf(stderr, "File %s open failed, human resource system init failed\n", compfilename);
                exit(EXIT_FAILURE);
        }
        Complaint_record *rcd = get_head(COMP_LIST);
        while (rcd != NULL) {
                int len = 0;
                char info_c[comp_info_len];
                char *name = get_name(rcd);
                char *time = rcd->time.whole_time;
                char *mesg = rcd->info;
                len += sprintf(info_c + len, "%s ", name);
                len += sprintf(info_c + len, "%s ", time);
                len += sprintf(info_c + len, "%s ", mesg);
                if (strlen(info_c) < (comp_info_len - 1)) {
                        int diff = comp_info_len - 1 - strlen(info_c);
                        char buf[diff + 1];
                        for (int i = 0; i < diff; i++) {
                                buf[i] = ' ';
                        }
                        buf[diff] = '\0';
                        len += sprintf(info_c + len, "%s", buf);
                        info_c[comp_info_len - 1] = '\n';
                }
                write(hr_fd, info_c, comp_info_len);
                rcd = rcd->next;
        }
        COMP_LIST->fd = -1;


}

void free_hr_list() {
        Staff *ptr = HR_LIST->head;
        while (ptr->next != NULL) {
                Staff *staff = ptr->next;
                _remove_worker(staff);
        }
}

// called when exit the hr sys
void exit_hr_sys() {
        flush_disk();
        free_hr_list();
        printf(BOLD"*----------------------------------------------------*\n"NONE
               BOLD"|  "BLINK UNDERLINE"Human resource system successfully exited!       "NONE" |\n"NONE
               BOLD"*----------------------------------------------------*\n\n"NONE);
        exit(0);
}

void sync_hr_sys() {
        flush_disk();
}

void add_complaint(const char *wid, const char *info) {
        Complaint_record *rcd = (Complaint_record *) malloc(sizeof(*rcd));
        Staff *staff = query_by_wid(wid);
        strcpy(rcd->name, staff->name);
        FormatTime *ft = current_sys_time();
        char *time_now = ft->whole_time;
        strcpy(rcd->time.whole_time, time_now);
        strcpy(rcd->info, info);
        _insert_comp(rcd);
}

