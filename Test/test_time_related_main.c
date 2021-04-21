//
// Created by elio on 2021/4/4.
//

#include "../tools/time_related.h"
#include <stdio.h>
int main()
{
        FormatTime *systime = current_sys_time();
        printf("%s\n",systime->whole_time);
        printf("%s\n", format_time(systime));
        return 0;

}
