#include "time.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"

typedef unsigned char byte;

char *bytes_to_hex(byte *bytes, int len);

byte addition(byte a, byte b);

byte time_x(byte a);

byte multiply(byte a, byte b);

byte power(byte a, byte b);

byte inverse(byte a);

byte divide(byte a, byte b);

byte *hex_to_bytes(const char *hex);

byte *shamir_decrypt(byte **shares, int secret_size, int required_shares);

char *shamir_gen_keys(char *secret, byte secret_size, byte total_shares, byte required_shares);

byte **shamir_split(byte secret_number, byte * x_arr, byte secret_size, byte required_shares, byte total_shares);

byte *random_bytes(byte total_shares);

byte **coefficient_polynomial(const byte *x_arr, byte secret_size, byte secret_number, byte required_shares, byte total_shares);

byte *coefficients(byte secret_number, byte required_shares);

byte interpolate(byte *x_decryp, byte *y_decryp, int k);

char *bytes_to_hex(byte *bytes, int len){
    char *hex = malloc(len * 2 + 1);
    for(int i=0; i<len; ++i){
        sprintf(hex + i*2, "%02x", bytes[i]);
    }
    return hex;
}

byte *hex_to_bytes(const char *hex){
    byte *bytes = malloc(strlen(hex) / 2);
    for(int i=0; i<strlen(hex) / 2; ++i){
        strncpy(bytes + i, hex + i*2, 2);
        bytes[i] = (byte)strtol(bytes + i, NULL, 16);
    }
    return bytes;
}

byte *random_bytes(byte total_shares){
    byte *bytes = malloc(total_shares);
    for(int i=0; i<total_shares; ++i){
        bytes[i] = rand() % 256;
    }
    return bytes;
}

byte *shamir_decrypt(byte **shares, int secret_size, int required_shares){
    byte *secret=malloc(secret_size*sizeof(byte));

    for(int i=0;i<secret_size;++i){
        byte *x_dec = (byte *)malloc(required_shares*sizeof(byte));
        byte *y_dec = (byte *)malloc(required_shares*sizeof(byte));
        for(int j=0;j<required_shares;++j){
            x_dec[j] = shares[j][0];
            y_dec[j] = shares[j][i+1];

            secret[i-1] = interpolate(x_dec, y_dec, required_shares);
        }
    }
    return secret;
}

char *shamir_gen_keys(char *secret, byte secret_size, byte total_shares, byte required_shares){
    byte **shares, *x_arr=random_bytes(total_shares),d=0, check[secret_size-1], combined[secret_size][total_shares][2];
    char *keys = (char *)malloc(total_shares * (secret_size * 2 + 1) + 1);

    for(int i=0;i<secret_size;++i){
        d=secret[i];
        shares=shamir_split(d, x_arr, secret_size, required_shares, total_shares);
        for(int j=0;j<total_shares;++j){
            combined[i][j][0]=shares[j][0];
            combined[i][j][1]=shares[j][1];
        }
    }

    for(int i=0;i<total_shares; ++i){
        for(int j=0;j<secret_size;++j){
            if(i==0){
                check[i]=combined[i][j][0];
                check[i+1]=combined[i][j][1];
            } else{
                check[i+1]=combined[i][j][1];
            }
            strcat(keys, bytes_to_hex(check, secret_size+1));
            strcat(keys, " ");
        }
    }
    return keys;
}

byte **shamir_split(byte secret_number, byte * x_arr, byte secret_size, byte required_shares, byte total_shares){
    byte **shares=coefficient_polynomial(x_arr, secret_size, secret_number, required_shares, total_shares);
    return shares;
}

byte **coefficient_polynomial(const byte *x_arr, byte secret_size, byte secret_number, byte required_shares, byte total_shares){
    byte **shares=malloc(total_shares*sizeof(byte *));
    byte *coefficients_matrix=coefficients(secret_number, required_shares);

    for(int i=0; i<total_shares;++i){
        shares[i]=malloc(sizeof(byte)*(secret_size+1));
        byte x=x_arr[i], y=0;

        for(int j=0;j<required_shares;++j){
            y=addition(y, multiply(power(x, required_shares-j-1), coefficients_matrix[j]));

            shares[i][0]=x;
            shares[i][1]=y;
        }
        return shares;
    }
}

byte *coefficients(byte secret_number, byte required_shares){
    byte *matrix=malloc(required_shares*sizeof(byte));

    for(int i=0;i<required_shares;++i){
        matrix[i]=(rand() % 256) % (secret_number+1);

        if(i==required_shares-1){
            matrix[i]=secret_number;
        }
    }
    return matrix;
}

byte interpolate(byte *x_decryp, byte *y_decryp, int k){

    byte y=0;

    for(int j=0;j<k;++j){
        byte prod=0x01;
        for(int i=0;i<k;++i){
            if(i!=j){
                prod=multiply(prod, divide(x_decryp[i], addition(x_decryp[i], x_decryp[j])));
            }
        }
        y=addition(y, multiply(prod, y_decryp[j]));
    }
    return y;
}


byte addition(byte a, byte b){
    return a ^ b;
}

byte time_x(byte a){
    return (a << 1) ^ (a >> 7);
}

byte multiply(byte a, byte b){
    byte result = 0;
    for(int i=0; i<8; ++i){
        if(b & (1 << i)){
            result ^= a;
        }
        a = time_x(a);
    }
    return result;
}

byte power(byte a, byte b){
    byte result = 1;
    for(int i=0; i<8; ++i){
        if(b & (1 << i)){
            result = multiply(result, a);
        }
        a = time_x(a);
    }
    return result;
}

byte inverse(byte a){
    return power(a, 0xFF);
}

byte divide(byte a, byte b){
    return multiply(a, inverse(b));
}