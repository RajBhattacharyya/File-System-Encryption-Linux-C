#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>

// Function to check if a file exists
// Parameters: file name
// Returns: 1 if the file exists, 0 otherwise
int file_exists(const char *filename);

// Function to get the size of a file
// Parameters: file name
// Returns: size of the file in bytes, or -1 if file does not exist
long get_file_size(const char *filename);

// Function to safely open a file
// Parameters: file name, mode
// Returns: pointer to the opened file
FILE* safe_open_file(const char *filename, const char *mode);

#endif
