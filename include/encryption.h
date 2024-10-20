#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <openssl/evp.h>

// Function to encrypt a file using AES-256
// Parameters: input file, output file, encryption key, initialization vector
void encrypt_file(const char *in_filename, const char *out_filename, unsigned char *key, unsigned char *iv);

// Function to derive encryption key and IV from a password
// Parameters: password, derived key buffer, derived iv buffer
void derive_key_from_password(const char *password, unsigned char *key, unsigned char *iv);

#endif
