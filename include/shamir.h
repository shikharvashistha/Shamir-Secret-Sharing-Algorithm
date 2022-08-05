#include "galois.h"

byte *hex_to_bytes(const char *hex);

byte *shamir_decrypt(byte **shares, int secret_size, int required_shares);

char *shamir_gen_keys(char *secret, byte secret_size, byte total_shares, byte required_shares);

byte **shamir_split(byte secret_number, byte * x_arr, byte secret_size, byte required_shares, byte total_shares);

byte *random_bytes(byte total_shares);

byte **coefficient_polynomial(const byte *x_arr, byte secret_size, byte secret_number, byte required_shares, byte total_shares);

byte *coefficients(byte secret_number, byte required_shares);

byte interpolate(byte *x_decryp, byte *y_decryp, int k);
