// Shamir Secret Sharing Algorithm
#include "header.h"

int main(int argc, char *argv[]){
    if(strcmp(argv[1], "encrypt") == 0){
        char secret[32], *keys;
        //byte *shares, *shares_enc;
        int n, k;
        printf("Enter secret to be encrypted: ");
        scanf("%s", secret);
        printf("Enter number of total required shares: ");
        scanf("%d", &n);
        printf("Enter number of essential shares: ");
        scanf("%d", &k);
        //shares = (byte *)malloc(n * 32);
        //shares_enc = (byte *)malloc(k * 32);
        byte secret_len = strlen(secret);

        keys = shamir_gen_keys(secret, secret_len, n, k);
        printf("\nKeys: %s\n", keys);
    } else if(strcmp(argv[1], "decrypt") == 0){
        int secret_size=strlen(argv[2]) - 1, required_shares=argc - 2;
        byte **shares = malloc(required_shares * sizeof(byte *));

        for(int i=0; i<required_shares;++i){
            shares[i]=hex_to_bytes(argv[i+2]);
        }
        byte *decrypted_secret = shamir_decrypt(shares, secret_size, required_shares);

        printf("\nDecrypted secret: %s\n", decrypted_secret);
    } else {
        printf("Invalid command\n");
    }
    return 0;
}