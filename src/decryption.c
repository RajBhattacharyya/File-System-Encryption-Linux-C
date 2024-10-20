#include <openssl/evp.h>
#include <stdio.h>
#include <stdlib.h>
#include "decryption.h"

void decrypt_file(const char *in_filename, const char *out_filename, unsigned char *key, unsigned char *iv) {
    FILE *in_file = fopen(in_filename, "rb");
    FILE *out_file = fopen(out_filename, "wb");

    if (!in_file || !out_file) {
        printf("File error: Could not open files.\n");
        exit(1);
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    unsigned char buffer[1024];
    unsigned char plaintext[1024 + EVP_MAX_BLOCK_LENGTH];
    int len, plaintext_len;

    while ((len = fread(buffer, 1, 1024, in_file)) > 0) {
        EVP_DecryptUpdate(ctx, plaintext, &plaintext_len, buffer, len);
        fwrite(plaintext, 1, plaintext_len, out_file);
    }

    EVP_DecryptFinal_ex(ctx, plaintext, &plaintext_len);
    fwrite(plaintext, 1, plaintext_len, out_file);

    EVP_CIPHER_CTX_free(ctx);
    fclose(in_file);
    fclose(out_file);
}
