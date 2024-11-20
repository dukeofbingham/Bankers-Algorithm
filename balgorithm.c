#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100
#define MAX_RESOURCES 100

int n, m; // n = number of processes, m = number of resources
int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

void read_input() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fscanf(file, "%d %d", &n, &m);

    int total_resources[MAX_RESOURCES];
    for (int i = 0; i < m; i++)
        fscanf(file, "%d", &total_resources[i]);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            fscanf(file, "%d", &allocation[i][j]);
        for (int j = 0; j < m; j++)
            fscanf(file, "%d", &max[i][j]);
    }

    for (int i = 0; i < m; i++)
        fscanf(file, "%d", &available[i]);

    fclose(file);

    // Calculate need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];
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
        for (int i = 0; i < n; i++)
            printf("P%d ", safe_sequence[i]);
        printf("\n");
    } else {
        printf("The system is not in a safe state.\n");
    }

    return 0;
} 