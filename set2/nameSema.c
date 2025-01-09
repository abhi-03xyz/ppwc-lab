#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>

#define TERMS 10


const char *sem_names[] = {"/sem1", "/sem2", "/sem3"};

void calculate_and_print_series(int process_id, sem_t *my_sem, sem_t *next_sem) {
    for (int k = 0; k < TERMS; k++) {
        // Wait for the semaphore to be released
        sem_wait(my_sem);

        // Calculate and print the term in the series
        int result = 3 * k + process_id;
        printf("%d ", result);
        fflush(stdout);

        // Release the semaphore for the next process
        sem_post(next_sem);
    }
    exit(0);
}

int main() {
    pid_t pid[3];
    sem_t *sems[3];

    // Initialize semaphores
    for (int i = 0; i < 3; i++) {
        sems[i] = sem_open(sem_names[i], O_CREAT | O_EXCL, 0644, i == 0 ? 1 : 0); // Only sem1 is initialized to 1
        if (sems[i] == SEM_FAILED) {
            perror("Semaphore initialization failed");
            for (int j = 0; j < i; j++) sem_unlink(sem_names[j]); // Cleanup
            exit(1);
        }
    }

    // Spawn child processes
    for (int i = 0; i < 3; i++) {
        pid[i] = fork();
        if (pid[i] < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid[i] == 0) {
            // Child process
            calculate_and_print_series(i + 1, sems[i], sems[(i + 1) % 3]);
        }
    }

    // Wait for all child processes to finish
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    // Cleanup semaphores
    for (int i = 0; i < 3; i++) {
        sem_close(sems[i]);
        sem_unlink(sem_names[i]);
    }

    printf("\nAll processes finished.\n");
    return 0;
}

