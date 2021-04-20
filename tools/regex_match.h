/*
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/4/15
 */

#ifndef CDESIGN_REGEX_MATCH_H
#define CDESIGN_REGEX_MATCH_H

#include <stdio.h>
#include <regex.h>



#define TXT_FILE_REG      "^[a-zA-Z0-9_\\.]+\\.txt[ ]*$"
#define SELECT_All_REG    "^[ ]*select[ ]+\\*[ ]*$"
#define SELECT_NAME_REG   "^[ ]*select[ ]+NAME[ ]*$"
#define SELECT_PID_REG    "^[ ]*select[ ]+PID[ ]*$"
#define SELECT_WID_REG    "^[ ]*select[ ]+WID[ ]*$"
#define SELECT_GENDER_REG "^[ ]*select[ ]+GENDER[ ]+(MALE|FEMALE)[ ]*$"
#define SELECT_RANK_REG   "^[ ]*select[ ]+RANK[ ]+(BOSS|MANAGER|BARTENDER|COOK|CLEANER|CASHIER|WAREHOUSEMAN|FINANCE|\\*)[ ]*$"
#define SELECT_DATE_REG   "^[ ]*select[ ]+DATE[ ]*$"
#define QUERY             "^[ ]*query[ ]+(\\d{6}|\\d{14}|[a-zA-Z]+)[ ]*$"
#define SORT              "^[ ]*sort\s+by\s+(NAME|PID|WID|DATE|SALARY)[ ]*(-d|-i){0,1}$"
#define DELETE            "^[ ]*delete[ ]+(\\d{6}|\\d{14}|[a-zA-Z]+)[ ]*$"
#define INSERT_INFO
#define INSERT_COM




static int match_pattern(const char *target, const char *reg_pattern)
{
        int status;
        const size_t nmatch = 1;
        regmatch_t pmatch[1];
        int flag = REG_EXTENDED;

        regex_t reg;
        regcomp(&reg, reg_pattern, flag);
        status = regexec(&reg, target, nmatch, pmatch, 0);
        if (status == REG_NOMATCH) {
                return -1;
        }
        regfree(&reg);
        return 0;
}


#endif //CDESIGN_REGEX_MATCH_H
