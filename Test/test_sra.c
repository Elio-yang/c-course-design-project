/*
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/4/20
 */
#include "../tools/rsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
        struct public_key_class pub[1]={
                {
                        .modulus=1302169711,
                        .exponent=131073
                }
        };
        struct private_key_class priv[1]={
                {
                        .modulus=1302169711,
                        .exponent=533053217
                }
        };
//        rsa_gen_keys(pub,priv,PRIME_SOURCE_FILE);
        char message[]="882323";
        int i;
        printf("Original:\n");
        for(i=0; i < strlen(message); i++){
                printf("%lld\n", (long long)message[i]);
        }

        long long *encrypted = rsa_encrypt(message, sizeof(message), pub);
        if (!encrypted){
                fprintf(stderr, "Error in encryption!\n");
                return 1;
        }
        printf("Encrypted:\n");
        for(i=0; i < strlen(message); i++){
                printf("%lld\n", (long long)encrypted[i]);
        }

        char *decrypted = rsa_decrypt(encrypted, 8*sizeof(message), priv);
        if (!decrypted){
                fprintf(stderr, "Error in decryption!\n");
                return 1;
        }
        printf("Decrypted:\n");
        for(i=0; i < strlen(message); i++){
                printf("%lld\n", (long long)decrypted[i]);
        }

        printf("\n");
        free(encrypted);
        free(decrypted);
        return 0;


}
