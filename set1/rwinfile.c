#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/wait.h>

#define FILENAME "textfile.txt"

// Function to convert the content of a file to uppercase
void convert_to_uppercase(const char *filename) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read the file content into memory
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        perror("Memory allocation error");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0';

    // Convert to uppercase
    for (int i = 0; content[i] != '\0'; i++) {
        content[i] = toupper(content[i]);
    }

    // Write back to the file
    rewind(file);
    fwrite(content, 1, file_size, file);
    fclose(file);
    free(content);
}

// Function to display the content of a file
void display_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
}

int main() {
    pid_t pid1, pid2;

    // Open file for writing user input
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }

    printf("Enter text (Ctrl+D to finish):\n");
    char line[256];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        fputs(line, file);
    }
    fclose(file);

    // Create the first child process to convert the file to uppercase
    pid1 = fork();
    if (pid1 < 0) {
        perror("Error creating first child process");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // Child 1: Convert file to uppercase
        convert_to_uppercase(FILENAME);
        exit(EXIT_SUCCESS);
    }

    // Wait for the first child to complete
    waitpid(pid1, NULL, 0);

    // Create the second child process to display the file content
    pid2 = fork();
    if (pid2 < 0) {
        perror("Error creating second child process");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        // Child 2: Display file content
        display_file(FILENAME);
        exit(EXIT_SUCCESS);
    }

    // Wait for the second child to complete
    waitpid(pid2, NULL, 0);

    return 0;
}

