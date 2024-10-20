#ifndef DECRYPTION_H
#define DECRYPTION_H

#include <openssl/evp.h>

// Function to decrypt a file using AES-256
// Parameters: input file, output file, decryption key, initialization vector
void decrypt_file(const char *in_filename, const char *out_filename, unsigned char *key, unsigned char *iv);

#endif
