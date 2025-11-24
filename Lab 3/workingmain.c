#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Global variables
int *resources = NULL;      // Resource vector
int *available = NULL;      // Available vector
int **max_claim = NULL;     // Max claim matrix
int **allocated = NULL;     // Allocated matrix
int **need = NULL;          // Need matrix
int num_resources = 0;      // Number of resources
int num_processes = 0;      // Number of processes

//*********************************************************
void print_vector(int *vector, char *title) {
    printf("%s:", title);
    for (int j = 0; j < num_resources; j++) {
        printf(" r%d", j);
    }
    printf("\n");
    
    printf("     ");
    for (int j = 0; j < num_resources; j++) {
        printf("%3d", vector[j]);
    }
    printf("\n");
}

//*************************************************************
void print_matrix(int **matrix, char *title) {
    printf("%s:", title);
    for (int j = 0; j < num_resources; j++) {
        printf(" r%d", j);
    }
    printf("\n");
    
    for (int i = 0; i < num_processes; i++) {
        printf("p%d  ", i);
        for (int j = 0; j < num_resources; j++) {
            printf("%3d", matrix[i][j]);
        }
        printf("\n");
    }
}

//**************************************************************
void claim_graph() {
    // Free any existing memory
    exit_free_mem();
    
    // Prompt for number of resources
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);
    
    // Allocate memory for resource and available vectors
    resources = (int *)malloc(num_resources * sizeof(int));
    available = (int *)malloc(num_resources * sizeof(int));
    
    // Prompt for number of units for each resource
    printf("Enter number of units for resources (r0 to r%d): ", num_resources - 1);
    for (int j = 0; j < num_resources; j++) {
        scanf("%d", &resources[j]);
        available[j] = resources[j]; // Initially all resources are available
    }
    
    // Prompt for number of processes
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    
    // Allocate memory for matrices
    max_claim = (int **)malloc(num_processes * sizeof(int *));
    allocated = (int **)malloc(num_processes * sizeof(int *));
    need = (int **)malloc(num_processes * sizeof(int *));
    
    for (int i = 0; i < num_processes; i++) {
        max_claim[i] = (int *)malloc(num_resources * sizeof(int));
        allocated[i] = (int *)malloc(num_resources * sizeof(int));
        need[i] = (int *)malloc(num_resources * sizeof(int));
    }
    
    // Prompt for maximum claims for each process
    for (int i = 0; i < num_processes; i++) {
        printf("Enter maximum number of units process p%d will claim from each resource (r0 to r%d): ", 
               i, num_resources - 1);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &max_claim[i][j]);
        }
    }
    
    // Prompt for currently allocated resources for each process
    for (int i = 0; i < num_processes; i++) {
        printf("Enter number of units of each resource (r0 to r%d) currently allocated to process p%d: ", 
               num_resources - 1, i);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocated[i][j]);
            available[j] -= allocated[i][j]; // Reduce available by allocated
            need[i][j] = max_claim[i][j] - allocated[i][j]; // Calculate need
        }
    }
    
    // Print all vectors and matrices
    print_vector(resources, "Resources");
    print_vector(available, "Available");
    print_matrix(max_claim, "Max Claim");
    print_matrix(allocated, "Allocated");
    print_matrix(need, "Need");
}

//**************************************************************
void request_resources() {
    int process, resource, units;
    
    // Prompt for process, resource, and units
    printf("Enter requesting process: p");
    scanf("%d", &process);
    printf("Enter requested resource: r");
    scanf("%d", &resource);
    printf("Enter number of units process p%d is requesting from resource r%d: ", process, resource);
    scanf("%d", &units);
    
    // Check if request is valid
    if (process < 0 || process >= num_processes || resource < 0 || resource >= num_resources) {
        printf("Invalid process or resource!\n");
        return;
    }
    
    // Check if request exceeds need
    if (units > need[process][resource]) {
        printf("Error: Process has exceeded its maximum claim!\n");
        return;
    }
    
    // Check if enough units are available
    if (units > available[resource]) {
        printf("Resources not available. Process must wait.\n");
        return;
    }
    
    // Grant the request
    available[resource] -= units;
    allocated[process][resource] += units;
    need[process][resource] -= units;
    
    // Print updated vectors and matrices
    print_vector(available, "Available");
    print_matrix(allocated, "Allocated");
    print_matrix(need, "Need");
}

//**************************************************************
void release_resources() {
    int process, resource, units;
    
    // Prompt for process, resource, and units
    printf("Enter releasing processor: p");
    scanf("%d", &process);
    printf("Enter released resource: r");
    scanf("%d", &resource);
    printf("Enter number of units process p%d is releasing from resource r%d: ", process, resource);
    scanf("%d", &units);
    
    // Check if release is valid
    if (process < 0 || process >= num_processes || resource < 0 || resource >= num_resources) {
        printf("Invalid process or resource!\n");
        return;
    }
    
    // Check if enough units are allocated to release
    if (units > allocated[process][resource]) {
        printf("Error: Process does not have that many units allocated!\n");
        return;
    }
    
    // Release the resources
    available[resource] += units;
    allocated[process][resource] -= units;
    need[process][resource] += units;
    
    // Print updated vectors and matrices
    print_vector(available, "Available");
    print_matrix(allocated, "Allocated");
    print_matrix(need, "Need");
}

//******************************************************************
void safe_check() {
    int *work = (int *)malloc(num_resources * sizeof(int));
    bool *finish = (bool *)malloc(num_processes * sizeof(bool));
    int *safe_sequence = (int *)malloc(num_processes * sizeof(int));
    int count = 0;
    
    // Initialize work = available
    for (int j = 0; j < num_resources; j++) {
        work[j] = available[j];
    }
    
    // Initialize finish array to false
    for (int i = 0; i < num_processes; i++) {
        finish[i] = false;
    }
    
    // Find safe sequence
    int pass = 0;
    while (count < num_processes) {
        bool found = false;
        
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                // Print comparison
                printf("Comparing: <");
                for (int j = 0; j < num_resources; j++) {
                    printf(" %d", need[i][j]);
                }
                printf(" > <= <");
                for (int j = 0; j < num_resources; j++) {
                    printf(" %d", work[j]);
                }
                printf(" > : ");
                
                // Check if process can be satisfied
                bool can_proceed = true;
                for (int j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_proceed = false;
                        break;
                    }
                }
                
                if (can_proceed) {
                    printf("Process p%d can be sequenced\n", i);
                    
                    // Add allocated resources back to work
                    for (int j = 0; j < num_resources; j++) {
                        work[j] += allocated[i][j];
                    }
                    
                    safe_sequence[count++] = i;
                    finish[i] = true;
                    found = true;
                } else {
                    printf("Process p%d cannot be sequenced\n", i);
                }
            }
        }
        
        // If no process was found in this pass, we have a deadlock
        if (!found) {
            printf("System is in deadlock! No safe sequence exists.\n");
            printf("Deadlocked processes:");
            for (int i = 0; i < num_processes; i++) {
                if (!finish[i]) {
                    printf(" p%d", i);
                }
            }
            printf("\n");
            free(work);
            free(finish);
            free(safe_sequence);
            return;
        }
        
        pass++;
    }
    
    // Print safe sequence
    printf("Safe sequence of processes:");
    for (int i = 0; i < num_processes; i++) {
        printf(" p%d", safe_sequence[i]);
    }
    printf("\n");
    
    // Free temporary memory
    free(work);
    free(finish);
    free(safe_sequence);
}

//******************************************************************
void exit_free_mem() {
    // Free all allocated memory
    if (resources != NULL) {
        free(resources);
        resources = NULL;
    }
    
    if (available != NULL) {
        free(available);
        available = NULL;
    }
    
    if (max_claim != NULL) {
        for (int i = 0; i < num_processes; i++) {
            if (max_claim[i] != NULL) {
                free(max_claim[i]);
            }
        }
        free(max_claim);
        max_claim = NULL;
    }
    
    if (allocated != NULL) {
        for (int i = 0; i < num_processes; i++) {
            if (allocated[i] != NULL) {
                free(allocated[i]);
            }
        }
        free(allocated);
        allocated = NULL;
    }
    
    if (need != NULL) {
        for (int i = 0; i < num_processes; i++) {
            if (need[i] != NULL) {
                free(need[i]);
            }
        }
        free(need);
        need = NULL;
    }
}

//*************************************************************
int main() {
    printf("Banker's Algorithm\n");
    printf("------------------\n");
    
    int choice;
    
    // Menu loop
    do {
        printf("1) Enter claim graph\n");
        printf("2) Request resource\n");
        printf("3) Release resource\n");
        printf("4) Determine safe sequence\n");
        printf("5) Quit program\n");
        printf("Enter selection: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                claim_graph();
                break;
            case 2:
                if (num_processes == 0 || num_resources == 0) {
                    printf("Please enter claim graph first!\n");
                } else {
                    request_resources();
                }
                break;
            case 3:
                if (num_processes == 0 || num_resources == 0) {
                    printf("Please enter claim graph first!\n");
                } else {
                    release_resources();
                }
                break;
            case 4:
                if (num_processes == 0 || num_resources == 0) {
                    printf("Please enter claim graph first!\n");
                } else {
                    safe_check();
                }
                break;
            case 5:
                printf("Quitting program...\n");
                exit_free_mem();
                break;
            default:
                printf("Invalid choice, please select 1-5\n");
                break;
        }
        
        if (choice != 5) {
            printf("Banker's Algorithm\n");
            printf("------------------\n");
        }
        
    } while(choice != 5);
    
    return 0;
}