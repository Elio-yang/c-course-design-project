/*
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/4/20
 */
#include "../tools/rsa.h"
#include "../human_resource_system/hr_repl.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main()
{
        struct public_key_class pub[1]={
                {
                        .modulus=5340489799,
                        .exponent=131073
                }
        };

        int cnt=0;
        passwd:
        cnt++;
        if(cnt>=5){

               int status= get_response("Please give another try after 5 minutes or EXIT system?");
               if(status==-2){
                       exit(2);
               }
                sleep(60*5);
        }
        printf("Please enter a 8-bit passwd : \n");
        char passwd[255];
        get_passwd(passwd,255);
        size_t idx= strlen(passwd);
        if(idx !=8){
                printf(RED"Wrong password.\n"NONE);
                goto passwd;
        }

        char *message= passwd;
        int i;
        long long *encrypted = rsa_encrypt(message, sizeof(message), pub);
        if (!encrypted){
                fprintf(stderr, "Error in encryption!\n");
                _exit(EXIT_FAILURE);
        }
        long long keys[]={
                (long long)1483281149,
                (long long)1483281149,
                (long long)544443352,
                (long long)3232991069,
                (long long)544443352,
                (long long)268350751,
                (long long)542371566,
                (long long)5245340233
        };
        for(i=0;i< strlen(message) && i<8;i++){
                if(keys[i]!=encrypted[i]){
                        printf(RED"Wrong password.\n"NONE);
                        goto passwd;
                }
        }
        free(encrypted);
        _exit(0);
}
