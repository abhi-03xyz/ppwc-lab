#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <semaphore.h>

#define SEMAPHORE_NAME "/print_semaphore"

void print_PID() {
    int PID = getpid();
    char str[100];

    sprintf(str, "My process id is %d\n", PID);

    for (int i = 0; i < strlen(str); i++) {
        fprintf(stderr, "%c", str[i]);
        sleep(1); // Simulate the delay for printing each character
    }
}

int main() {
    sem_t *sem = sem_open(SEMAPHORE_NAME, O_CREAT, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid;
    for (int i = 0; i < 3; i++) {
        pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            sem_wait(sem); // Acquire semaphore
            print_PID();
            sem_post(sem); // Release semaphore
            exit(EXIT_SUCCESS);
        }
    }

    // Parent process waits for all children to complete
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    // Close and unlink the semaphore
    sem_close(sem);
    sem_unlink(SEMAPHORE_NAME);

    return 0;
}

