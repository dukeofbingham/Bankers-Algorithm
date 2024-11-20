#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PROCESSES 100
#define MAX_RESOURCES 100

int n, m;
int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

void read_input() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    char line[256];
    // Read n and m
    while (fgets(line, sizeof(line), file)) {
        if (line[0] != '#' && line[0] != '\n') {
            sscanf(line, "%d %d", &n, &m);
            break;
        }
    }

    // Read total resources (we'll use this to calculate available later)
    int total_resources[MAX_RESOURCES];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] != '#' && line[0] != '\n') {
            char *token = strtok(line, " ");
            for (int i = 0; i < m; i++) {
                total_resources[i] = atoi(token);
                token = strtok(NULL, " ");
            }
            break;
        }
    }

    // Read Allocation and Max matrices
    for (int i = 0; i < n; i++) {
        while (fgets(line, sizeof(line), file)) {
            if (line[0] != '#' && line[0] != '\n') {
                char *token = strtok(line, " ");
                for (int j = 0; j < m; j++) {
                    allocation[i][j] = atoi(token);
                    token = strtok(NULL, " ");
                }
                for (int j = 0; j < m; j++) {
                    max[i][j] = atoi(token);
                    token = strtok(NULL, " ");
                }
                break;
            }
        }
    }

    // Read Available resources
    while (fgets(line, sizeof(line), file)) {
        if (line[0] != '#' && line[0] != '\n') {
            char *token = strtok(line, " ");
            for (int i = 0; i < m; i++) {
                available[i] = atoi(token);
                token = strtok(NULL, " ");
            }
            break;
        }
    }

    fclose(file);

    // Calculate need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
            if (need[i][j] < 0) {
                printf("Error: Max[%d][%d] is less than Allocation[%d][%d].\n", i, j, i, j);
                exit(1);
            }
        }
    }

    // // Debug prints
    // printf("Number of processes: %d\n", n);
    // printf("Number of resources: %d\n", m);
    
    // printf("Available resources: ");
    // for (int i = 0; i < m; i++) {
    //     printf("%d ", available[i]);
    // }
    // printf("\n");

    // printf("Allocation matrix:\n");
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         printf("%d ", allocation[i][j]);
    //     }
    //     printf("\n");
    // }

    // printf("Max matrix:\n");
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         printf("%d ", max[i][j]);
    //     }
    //     printf("\n");
    // }

    // printf("Need matrix:\n");
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         printf("%d ", need[i][j]);
    //     }
    //     printf("\n");
    // }
}

bool is_safe_state(int safe_sequence[]) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};

    for (int i = 0; i < m; i++)
        work[i] = available[i];

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];
                    finish[i] = true;
                    safe_sequence[count] = i;
                    count++;
                    found = true;
                    break;
                }
            }
        }
        if (!found)
            return false;
    }
    return true;
}

int main() {
    read_input();

    int safe_sequence[MAX_PROCESSES];
    if (is_safe_state(safe_sequence)) {
        printf("The system is in a safe state.\n");
        printf("Safe sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d", safe_sequence[i]);
            if (i < n - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("The system is not in a safe state.\n");
    }

    return 0;
}