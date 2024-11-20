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
    // Skip comments and blank lines, then read n, m
    while (fgets(line, sizeof(line), file)) {
        if (line[0] != '#' && line[0] != '\n') {
            sscanf(line, "%d %d", &n, &m);
            break;
        }
    }

    // Read total resources
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

    // Read Allocation and Max matrices
    for (int i = 0; i < n; i++) {
        while (fgets(line, sizeof(line), file)) {
            if (line[0] != '#' && line[0] != '\n') {
                int *alloc = allocation[i];
                int *max_res = max[i];
                char *token = strtok(line, " ");
                for (int j = 0; j < m; j++) {
                    alloc[j] = atoi(token); // Allocation values
                    token = strtok(NULL, " ");
                }
                for (int j = 0; j < m; j++) {
                    max_res[j] = atoi(token); // Max values
                    token = strtok(NULL, " ");
                }
                break;
            }
        }

        // // Debugging: Print the parsed values
        // printf("Process %d - Allocation: ", i);
        // for (int j = 0; j < m; j++) {
        //     printf("%d ", allocation[i][j]);
        // }
        // printf("| Max: ");
        // for (int j = 0; j < m; j++) {
        //     printf("%d ", max[i][j]);
        // }
        // printf("\n");
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
                    safe_sequence[count++] = i;
                    found = true;
                }
            }
        }
        if (!found)
            return false;
    }
    return true;
}

int main() {
    read_input(); // Read input from data.txt and populate matrices

    int safe_sequence[MAX_PROCESSES];
    if (is_safe_state(safe_sequence)) {
        // If system is in a safe state
        printf("The system is in a safe state.\n");
        printf("Safe sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d", safe_sequence[i]);
            if (i < n - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        // If system is not in a safe state
        printf("The system is not in a safe state.\n");
    }

    return 0;
}
