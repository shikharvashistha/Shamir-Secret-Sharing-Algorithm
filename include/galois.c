#include "galois.h"

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