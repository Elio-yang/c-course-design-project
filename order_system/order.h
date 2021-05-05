typedef struct dish
{
    char name[50];
    char type[100];
    float price;
    int available_number;
    int personalization_availble; //how many persoalized choice do i have?
    char personalization[20][100];
} dish;

typedef struct order
{
    int index;
    int menu;               //correspond
    char name[50];
    char type[100];
    int number;
    float price;
    int personalization_request;
    char personlization[20][100]; //add space after each personlized choice
    struct order *next;
} order;
typedef enum{
    ORDER,
    STORE,
    HR
}DealType;
int dishes_number; //the amount of the dishes in the menu
int order_number;  //the amount of the dishes of the order list
dish menu[200];
order order_list[200];
extern void update_finance_record(const char,const char,DealType);   //finance interface:update the order record
extern int input_int(int *);        //analize the int input
extern void get_menu();
extern void print_menu(void);
extern void print_order(void);
extern void print_order_interface(void);
extern void add_dishes(void);                  //add a dishes into the oderlist
extern void check(void);                       //check the ordered dishes and conduct some operation
extern void delete_dishes(void);               //delete a dishews
extern void change_order(void);                //change the number or personalization
extern void change_order_number(int);          //change the number of a dishes
extern void change_order_personalization(int); //change the personalization of a dishes
extern int finish(void);                       //quit the system
extern int confirm();                          //confirm user's change delete or exit
