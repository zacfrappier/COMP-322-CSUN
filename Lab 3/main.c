/*
Zachary Frappier 
Comp 322 Prof Ebrahimi
Lab 3
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Declare dynamic arrays/vectors and global variables
int placeholder = INT_MIN;   //just used for things i GraphNeed to change later
#define MAX_VERTICES 5 // 5x5 matrix
int size = 5;   // might use this if other method doesnt work
/*
resources 2 x r matrix OR vector
available 2 x r matrix OR vector
GraphAllocated p x r matrix 
GraphNeed p x r matrix
*/

int *resources = NULL; //vector / array
int *available = NULL; //
int **allocated = NULL; // double ** used for matrix
int **max_claim = NULL;
int **need = NULL;

//initialize resource and process
int num_resources = 0;
int num_processes = 0;

//                   REFERENCE CODE
//make graph
typedef struct GraphType {
    int n; // number of vertices 
    int adj_matrix[MAX_VERTICES][MAX_VERTICES]; // m x n 
} GraphType;

//initialize graph values to 0
void initialize_graph(GraphType* g, int vertices){
    g->n = vertices;
    for (int i = 0; i < g->n; i++){
        for(int j = 0; j < g->n; j++){
            g->adj_matrix[i][j] = 0; //no edges
        }
    }
}

typedef struct GraphAllocated{
	int n;
	int adj_matrix[MAX_VERTICES][MAX_VERTICES];
}GraphAllocated;

void initialize_graph2(GraphAllocated* g, int vertices){
    g->n = vertices;
    for (int i = 0; i < g->n; i++){
        for(int j = 0; j < g->n; j++){
            g->adj_matrix[i][j] = 0; //no edges
        }
    }
}

typedef struct GraphNeed{
	int n;
	int adj_matrix[MAX_VERTICES][MAX_VERTICES];
}GraphNeed;

void initialize_graph3(GraphNeed* g, int vertices){
    g->n = vertices;
    for (int i = 0; i < g->n; i++){
        for(int j = 0; j < g->n; j++){
            g->adj_matrix[i][j] = 0; //no edges
        }
    }
}

///       END REFERENCE CODE
//*********************************************************
void print_vector(int *vector, int vector_type) { // vector_type 0: resources, 1: available
	// declare local variables 
	// for loop j: print each resource index
	// 1 or 0 to determine  vector type
	if(vector_type == 0){
		printf("Resources: ");
	} else {
		printf("Available: ");
	}

	for (int j = 0; j < num_resources; j++){
		printf(" r%d", j); // printf the r0- rn
	}
	printf("\n    ");
		for (int j = 0; j < num_resources; j++){
		printf("%3d", vector[j]); // prints amount
	}
	printf("\n");
}

//*************************************************************
void print_matrix(int **matrix, int matrix_type) {// 0: max_claim 1: allocated 2: need ** for matrices (pointers for and column)
	// declare local variables 
	if(matrix_type == 0){
		printf("Max Claim:");
	}else if(matrix_type == 1){
		printf("Allocated:");
	}else{
		printf("Need:");
	}
	// for loop j: print each resource index 
	for(int j = 0; j < num_resources; j++){ // prints r0 - rn (resource number)
		printf(" r%d", j);
	}
	printf("\n");
	// for each process i: 
		// for each resource j: 
			// print value of matrix[i,j]	
	for(int i = 0; i < num_processes; i++){ // prints p0-pn (process number), and need resources for each
		printf("p%d", i);
		for(int j = 0; j < num_resources; j++){
			printf("%3d", matrix[i][j]);
		}
		printf("\n");
	}
}


//**************************************************************
void claim_graph() {
    // Free any existing memory
    //exit_free_mem(); // this doesnt work? 
    
    // Prompt for number of resources
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);  // FIX: was num_processes
    
    // Allocate memory for vectors
    resources = (int *)malloc(num_resources * sizeof(int));
    available = (int *)malloc(num_resources * sizeof(int));
    
    // Prompt for units
    printf("Enter number of units for resources (r0 to r%d, seperate amounts with space): ", num_resources - 1);
    for (int j = 0; j < num_resources; j++){  // FIX: removed nested loop
        scanf("%d", &resources[j]);
        available[j] = resources[j];
    }
    
    // Prompt for number of processes
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    
    // Allocate memory for matrices
    max_claim = (int **)malloc(num_processes * sizeof(int *));
    allocated = (int **)malloc(num_processes * sizeof(int *));
    need = (int **)malloc(num_processes * sizeof(int *));
    
    //Allocate memory for each row
    for (int i = 0; i < num_processes; i++){
        max_claim[i] = (int *)malloc(num_resources * sizeof(int));
        allocated[i] = (int *)malloc(num_resources * sizeof(int));
        need[i] = (int *)malloc(num_resources * sizeof(int));
    }
    
    // Add prompts for max_claim
    for (int i = 0; i < num_processes; i++){
        printf("Enter maximum number of units process p%d will claim from each resource (r0 to r%d, seperate amounts with space): ", 
               i, num_resources - 1);
        for (int j = 0; j < num_resources; j++){  // FIX: was num_processes
            scanf("%d", &max_claim[i][j]);
        }
    }
    
    // Prompt for allocated resources
    for (int i = 0; i < num_processes; i++){
        printf("Enter number of units of each resource (r0 to r%d) currently allocated to process p%d, seperate amounts with space: ", 
               num_resources - 1, i);
        for (int j = 0; j < num_resources; j++){  // FIX: was num_processes
            scanf("%d", &allocated[i][j]);
            available[j] -= allocated[i][j];
            need[i][j] = max_claim[i][j] - allocated[i][j];
        }
    }
    
    // Print everything
    print_vector(resources, 0);
    print_vector(available, 1);
    print_matrix(max_claim, 0);
    print_matrix(allocated, 1);
    print_matrix(need, 2);
}


//**************************************************************
void request_resources() {
	// declare local variables
	int process, resource, units;
	// prompt for process, resource, and number of units requested
    printf("Enter requesting process: p");
	scanf("%d", &process);
    printf("Enter requesting resource: r");
	scanf("%d", &resource);
    printf("Enter number of resource process p%d is requesting from resource r%d, seperate amounts with space", process, resources);
	scanf("%d", &units);
	// if enough units available and request is less than GraphNeed
	if (process < 0 || process >= num_processes || resource < 0 || resource >= num_resources){
		printf("invalid number of process or resource requested\n");
		return;
	}
	if(units > need[process][resource]){
		printf("Error: Process has exceeded maximum available resource (claim)\n");
		return;
	}
	if(units > available[resource]){
		printf("resources not available.");
		return;
	}
		// reduce number of available units
		available[resource] -= units;
		// increase number of GraphAllocated units
		allocated[process][resource] += units;
		// reduce number of GraphNeeded units
		need[process][resource] -= units;

		// print updated available, GraphAllocated, and GraphNeed vectors/matrices
		print_vector(available, 1);
		print_matrix(allocated, 1);
		print_matrix(need, 2);
	// else
		//print message that request was denied
}


//**************************************************************
void release_resources() {
	// declare local variables
	int process, resource, units;

	// prompt for process, resource, and number of units requested
	printf("Enter releasing processor: p");
	scanf("%d", &process);
	printf("Enter resource to be released: r");
	scanf("%d", &resource);
	printf("Enter amount process p%d will release from resource r%d,seperate amounts with space: ", process, resource);
	scanf("%d", &units);
	
	//safety check 
	if (process <0 || process >= num_processes || resource < 0 || resource >= num_resources){
		printf("Error: you've entered incorrect number for process or resource that is out of bounds");
		return;
	}
	// if enough units GraphAllocated
	if(units > allocated[process][resource]){
		printf("Error: no units are available to allocate\n");
		return;
	}else{
		// increase number of available units
		available[resource] += units;
		// reduce number of GraphAllocated units
		allocated[process][resource] -= units;
		// increase number of GraphNeeded units
		need[process][resource] += units;
		// print updated available, GraphAllocated, and GraphNeed vectors/matrices
		print_vector(available, 1);
		print_matrix(allocated, 1);
		print_matrix(need, 2);
	}
}


//******************************************************************
void safe_check() {
	// declare local variables
	int *work = (int *)malloc(num_resources * sizeof(int));
	bool *finish = (bool *)malloc(num_processes * sizeof(bool));
	int *safe_sequence = (int *)malloc(num_processes * sizeof(int));
	int count = 0;
	int pass = 0; 
	//initialize 
	for(int j = 0; j < num_resources; j++){
		work[j] = available[j];
	}
	for( int i = 0; i < num_processes; i++){
		finish[i] = false; 
	}
	// while not all processes are processed
	while (count < num_processes){
		bool found = false;
		// for each process
		for (int i = 0; i < num_processes; i++){
			// if process has not been processed yet 
			if (!finish[i]){
				// print message comparing GraphNeed vector with available vector
				printf("Comparing Graphneed with available vector: <");
				// for each resource 
				for(int j = 0; j < num_resources; j++){
					printf(" %d", need[i][j]);
				}
				printf(" > <= <");
				for(int j = 0; j < num_resources; j++){
					printf(" %d", work[j]);
				}
				printf(" > : ");
					// check for safe processing by comparing process' GraphNeed vector to available vector 
					bool can_proceed = true;
					for (int j = 0; j < num_resources; j++){
						if (need[i][j] > work[j]){
							can_proceed = false;
							break;
						}
					}
	      			// if each resource is available
					if(can_proceed){
						printf("Process p%d can be processed\n", i); // print message that process can be processed
						// update number of available units of resource
						for (int j = 0; j < num_resources; j++){
							work[j] += allocated[i][j];
						} 

						safe_sequence[count++] = i;
						finish[i] = true; 
						found = true;
					} else{
						// else print message that process cannot be processed
						printf("process p%d cannot be sequenced\n", i);
					}
			}
		}
		if(!found){
			printf("Deadlock is present in system. \n");
			// print message of deadlock among processes not processed
			printf("Processes currently in deadlock:");
			for(int i = 0; i < num_processes; i++){
				if(!finish[i]){
					printf("p%d", i);
				}
			}
			printf("\n");
			//free local memory
			free(work);
			free(finish);
			free(safe_sequence);
			return;
		}
		pass++;
	}			
	//if (no process was processed in the final round of the for-loop)
	// else print safe sequence of processes
	printf("Safe sequence of processes:");
	for(int i = 0; i < num_processes; i++){
		printf(" p %d", safe_sequence[i]);
	}
	printf("\n");
	//free local memory
	free(work);
	free(finish);
	free(safe_sequence);
}


//******************************************************************
void exit_free_mem() {
	// check if vectors/array are not NULL--if so, free each vector/array 	);
	// to be checked : VECTORS available, resources,  MATRICIES allocated, max_claim, need
	//VECTORS
// Free vectors
    if (resources != NULL) {
        free(resources);
        resources = NULL;
    }
    
    if (available != NULL) {
        free(available);
        available = NULL;
    }
    
    // Free max_claim matrix
    if (max_claim != NULL) {
        for (int i = 0; i < num_processes; i++) {
            if (max_claim[i] != NULL) {
                free(max_claim[i]);
            }
        }
        free(max_claim);
        max_claim = NULL;
    }
    
    // Free allocated matrix
    if (allocated != NULL) {
        for (int i = 0; i < num_processes; i++) {
            if (allocated[i] != NULL) {
                free(allocated[i]);  // FIX: was free(allocated)
            }
        }
        free(allocated);
        allocated = NULL;
    }
    
    // Free need matrix
    if (need != NULL) {
        for (int i = 0; i < num_processes; i++) {
            if (need[i] != NULL) {
                free(need[i]);
            }
        }
        free(need);
        need = NULL;
    }
	return;
}


//*************************************************************
int main() {
	
    printf("This is Lab 3, showing hdeadlock avoidance through bankers algorithm\n");

	// declare local vars 
    int choice;
	// while user has not chosen to quit 
    do{
        printf("---- Menu (Banker's Algorithm) ---- \n");
        printf("1) Enter Claim graph (GraphNeed) \n"); 
        printf("2) Request resource (request)\n"); 
        printf("3) Release resource (allocation)\n"); 
        printf("4) Determine safe sequence\n"); 
        printf("5) free memory and Exit\n"); 
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("you've selected to enter claim graph of resources GraphNeeded\n");
                claim_graph();
                break;
            case 2:
                printf("you've selected to request resources\n");
                request_resources();
                break;
            case 3:
                printf("you've selected to enter claim graph of resources GraphNeeded\n");
                release_resources();
                break;
            case 4:
                printf("you've selected to enter claim graph of resources GraphNeeded\n");
                safe_check();
                break;
            case 5:
                printf("you've selected to enter claim graph of resources GraphNeeded\n");
                exit_free_mem();
                break;
            default:
                printf(" invalid choice, please select 1-5\n");
                break;
        }
    }while(choice != 5);
		// print menu of options 
		// prompt for menu selection 
		// call appropriate procedure based on choice--use switch statement or series of if, else if, else statements 	
	 // while loop 
	 return 0; // indicates success 
} // end of procedure 