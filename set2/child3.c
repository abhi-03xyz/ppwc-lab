#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_SIZE 256

void count_words(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("File opening failed");
        exit(1);
    }
    int words = 0;
    char buffer[MAX_SIZE];
    while (fscanf(file, "%s", buffer) != EOF) {
        words++;
    }
    fclose(file);
    printf("Word count: %d\n", words);
}

void count_lines(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("File opening failed");
        exit(1);
    }
    int lines = 0;
    char buffer[MAX_SIZE];
    while (fgets(buffer, MAX_SIZE, file)) {
        lines++;
    }
    fclose(file);
    printf("Line count: %d\n", lines);
}

void count_characters(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("File opening failed");
        exit(1);
    }
    int characters = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        characters++;
    }
    fclose(file);
    printf("Character count: %d\n", characters);
}

int main() {
    const char *filename = "sample.txt";  
    pid_t pid1, pid2, pid3;

    
    if ((pid1 = fork()) == 0) {
        count_words(filename);
        exit(0);
    }

    
    if ((pid2 = fork()) == 0) {
        count_lines(filename);
        exit(0);
    }

    
    if ((pid3 = fork()) == 0) {
        count_characters(filename);
        exit(0);
    }

    
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    printf("All child processes finished. Results displayed above.\n");
    return 0;
}

