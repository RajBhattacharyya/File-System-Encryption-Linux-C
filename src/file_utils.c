#include <stdio.h>
#include <stdlib.h>  // For exit()
#include <errno.h>   // For errno
#include <string.h>  // For strerror
#include "file_utils.h"

// Check if a file exists
int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return 1;  // File exists
    }
    return 0;  // File does not exist
}

// Get the size of a file in bytes
long get_file_size(const char *filename) {
    FILE *file = fopen(filename, "rb");  // Open file in binary mode
    if (!file) {
        printf("Error: Could not open file %s: %s\n", filename, strerror(errno));
        return -1;  // Return -1 to indicate error
    }

    fseek(file, 0, SEEK_END);  // Move to the end of the file
    long size = ftell(file);    // Get the current position (size)
    fclose(file);               // Close the file
    return size;                // Return file size
}

// Safely open a file, terminating the program if it fails
FILE* safe_open_file(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);  // Open file with specified mode
    if (!file) {
        printf("Error: Could not open file %s: %s\n", filename, strerror(errno));
        exit(EXIT_FAILURE);  // Use EXIT_FAILURE for clearer intent
    }
    return file;  // Return the opened file pointer
}
