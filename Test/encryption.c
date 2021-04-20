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
                set_tty_mode(SAVE);
                set_cr_nbuf();
                set_no_echo();
                set_nodelay();
                int res=get_response("Please give another try after 5 minutes or EXIT system?");
                set_tty_mode(RECOVERY);
                sleep(60*5);
        }
        printf("Please enter your passwd : ");
        set_tty_mode(SAVE);
        set_no_echo();
        InputBuffer *input = new_input_buffer();
        read_input(input);
        set_tty_mode(RECOVERY);
        if(input->input_len >25){
                fprintf(stderr,"Password must be no more than 6 bits.\n");
                goto passwd;
        }
        if(input->input_len <8){
                printf(RED"Wrong password.\n"NONE);
                goto passwd;
        }
        char *message= input->buf;
        int i;
        long long *encrypted = rsa_encrypt(message, sizeof(message), pub);
        if (!encrypted){
                fprintf(stderr, "Error in encryption!\n");
                _exit(EXIT_FAILURE);
        }
        printf("Your keys :\n");
        for(i=0; i < strlen(message); i++){
                printf("%lld\n", (long long)encrypted[i]);
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

        for(i=0;i< strlen(message);i++){
                if(keys[i]!=encrypted[i]){
                        printf(RED"Wrong password.\n"NONE);
                        goto passwd;
                }
        }
        free(encrypted);
        return 0;
}
