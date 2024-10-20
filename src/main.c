#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>  // For generating random IVs
#include "encryption.h"
#include "decryption.h"
#include "file_utils.h"

int main() {
    const char *input_file = "test_file.txt";
    const char *encrypted_file = "test_file.enc";
    const char *decrypted_file = "test_file_dec.txt";
    unsigned char key[32];  // Example key (AES-256 requires a 256-bit key)
    unsigned char iv[16];    // Initialization vector (IV)

    // Generate a random key (you can replace this with your key handling method)
    if (!RAND_bytes(key, sizeof(key))) {
        fprintf(stderr, "Could not generate random key\n");
        return 1;  // Exit if key generation fails
    }

    // Generate a random IV
    if (!RAND_bytes(iv, sizeof(iv))) {
        fprintf(stderr, "Could not generate random IV\n");
        return 1;  // Exit if IV generation fails
    }

    // Check if the input file exists
    if (!file_exists(input_file)) {
        printf("Input file does not exist.\n");
        return 1;
    }

    // Encrypt the file
    encrypt_file(input_file, encrypted_file, key, iv);  // Call without check

    printf("File encrypted successfully: %s\n", encrypted_file);

    // Decrypt the file
    decrypt_file(encrypted_file, decrypted_file, key, iv);  // Call without check

    printf("File decrypted successfully: %s\n", decrypted_file);

    // Optionally verify the content
    FILE *original = fopen(input_file, "r");
    FILE *decrypted = fopen(decrypted_file, "r");

    char original_content[256];
    char decrypted_content[256];

    fgets(original_content, sizeof(original_content), original);
    fgets(decrypted_content, sizeof(decrypted_content), decrypted);

    if (strcmp(original_content, decrypted_content) == 0) {
        printf("Content verification successful: The files match!\n");
    } else {
        printf("Content verification failed: The files do not match!\n");
    }

    fclose(original);
    fclose(decrypted);

    return 0;
}
