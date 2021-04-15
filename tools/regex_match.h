/*
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/4/15
 */

#ifndef CDESIGN_REGEX_MATCH_H
#define CDESIGN_REGEX_MATCH_H
#include <stdio.h>
#include <regex.h>


#define txt_file_reg  "^.+\\.txt$"

static int match_pattern(const char *target,const char *reg_pattern)
{
        int status;
        const size_t nmatch =1;
        regmatch_t pmatch[1];
        int flag = REG_EXTENDED;

        regex_t reg;
        regcomp(&reg,reg_pattern,flag);
        status= regexec(&reg,target,nmatch,pmatch,0);
        if(status==REG_NOMATCH){
                fprintf(stderr,"Must supply a xxx.txt file!\n");
                return -1;
        }
        regfree(&reg);
        return 0;
}




#endif //CDESIGN_REGEX_MATCH_H
