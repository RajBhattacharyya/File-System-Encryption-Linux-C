#include <openssl/evp.h>
#include <openssl/rand.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encryption.h"

void encrypt_file(const char *in_filename, const char *out_filename, unsigned char *key, unsigned char *iv) {
    FILE *in_file = fopen(in_filename, "rb");
    FILE *out_file = fopen(out_filename, "wb");

    if (!in_file || !out_file) {
        printf("File error: Could not open files.\n");
        exit(1);
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    unsigned char buffer[1024];
    unsigned char ciphertext[1024 + EVP_MAX_BLOCK_LENGTH];
    int len, ciphertext_len;

    while ((len = fread(buffer, 1, 1024, in_file)) > 0) {
        EVP_EncryptUpdate(ctx, ciphertext, &ciphertext_len, buffer, len);
        fwrite(ciphertext, 1, ciphertext_len, out_file);
    }

    EVP_EncryptFinal_ex(ctx, ciphertext, &ciphertext_len);
    fwrite(ciphertext, 1, ciphertext_len, out_file);

    EVP_CIPHER_CTX_free(ctx);
    fclose(in_file);
    fclose(out_file);
}

void derive_key_from_password(const char *password, unsigned char *key, unsigned char *iv) {
    const EVP_MD *digest = EVP_sha256();
    unsigned char salt[] = "random_salt";  // Can be a fixed or generated salt
    EVP_BytesToKey(EVP_aes_256_cbc(), digest, salt, (unsigned char *)password, strlen(password), 1, key, iv);
}
