CC = gcc
CFLAGS = -Wall -g -I/usr/include/openssl -I./include
LDFLAGS = -L/usr/lib -lssl -lcrypto
TARGET = encryption_program

# Directories for source, object files, and includes
SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./include

# Default target to build the program
all: $(OBJ_DIR) $(TARGET)

# Create the obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Link all object files to create the executable
$(TARGET): $(OBJ_DIR)/main.o $(OBJ_DIR)/encryption.o $(OBJ_DIR)/decryption.o $(OBJ_DIR)/file_utils.o
	$(CC) -o $(TARGET) $(OBJ_DIR)/main.o $(OBJ_DIR)/encryption.o $(OBJ_DIR)/decryption.o $(OBJ_DIR)/file_utils.o $(LDFLAGS)

# Compile main.c
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/encryption.h $(INC_DIR)/decryption.h $(INC_DIR)/file_utils.h
	$(CC) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o $(CFLAGS)

# Compile encryption.c
$(OBJ_DIR)/encryption.o: $(SRC_DIR)/encryption.c $(INC_DIR)/encryption.h
	$(CC) -c $(SRC_DIR)/encryption.c -o $(OBJ_DIR)/encryption.o $(CFLAGS)

# Compile decryption.c
$(OBJ_DIR)/decryption.o: $(SRC_DIR)/decryption.c $(INC_DIR)/decryption.h
	$(CC) -c $(SRC_DIR)/decryption.c -o $(OBJ_DIR)/decryption.o $(CFLAGS)

# Compile file_utils.c
$(OBJ_DIR)/file_utils.o: $(SRC_DIR)/file_utils.c $(INC_DIR)/file_utils.h
	$(CC) -c $(SRC_DIR)/file_utils.c -o $(OBJ_DIR)/file_utils.o $(CFLAGS)

# Clean up object files and the executable
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)
