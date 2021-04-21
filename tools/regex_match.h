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
#define SELECT_GENDER_REG "^[ ]*select[ ]+GENDER[ ]+(MALE|FEMALE|\\*)[ ]*$"
#define SELECT_RANK_REG   "^[ ]*select[ ]+RANK[ ]+(BOSS|MANAGER|BARTENDER|COOK|CLEANER|CASHIER|WAREHOUSEMAN|FINANCE|\\*)[ ]*$"
#define SELECT_DATE_REG   "^[ ]*select[ ]+DATE[ ]*$"
#define QUERY_REG         "^[ ]*query[ ]+(\\d{6}|\\d{14}|[a-zA-Z]+)[ ]*$"
#define SORT_REG          "^[ ]*sort[ ]+by[ ]+(NAME|PID|WID|DATE|SALARY)[ ]+(-d|-i)[ ]*$"
#define DELETE_REG        "^[ ]*delete[ ]+(\\d{6}|\\d{14}|[a-zA-Z]+)[ ]*$"
#define INSERT_INFO_REG
#define INSERT_COM_REG




static int regex_match_with(const char *target, const char *reg_pattern)
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
