/*
Zachary Frappier 
Comp 322 Prof Ebrahimi
Lab 3
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Declare dynamic arrays/vectors and global variables
int placeholder = INT_MIN;   //just used for things i GraphNeed to change later
#define MAX_VERTICES 5 // 5x5 matrix

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

/*
resources 2 x r matrix OR vector

available 2 x r matrix OR vector

GraphAllocated p x r matrix 

GraphNeed p x r matrix

*/
int *resources;
int *available;
int size = 5;

resources =(int *)malloc(size * sizeof(int));
resources =(MAX_VERTICES *)malloc(MAX_VERTICES * sizeof(MAX_VERTICES));

typedef struct GraphAllocated{
	int n;
	int adj_matrix[MAX_VERTICES][MAX_VERTICES];
}GraphAllocated;

void initialize_graph(GraphAllocated* g, int vertices){
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

void initialize_graph(GraphNeed* g, int vertices){
    g->n = vertices;
    for (int i = 0; i < g->n; i++){
        for(int j = 0; j < g->n; j++){
            g->adj_matrix[i][j] = 0; //no edges
        }
    }
}


//*********************************************************
void print_vector(int *vector, char *title) {
	// declare local variables 
	// for loop j: print each resource index 
    for (int j; j < placeholder; j++){

    }
	// for loop j: print value of vector[j] 
        for (int j; j < placeholder; j++){

    }
	return;
}

//*************************************************************
void print_matrix(int *matrix, char *title) { 
	// declare local variables 
	// for loop j: print each resource index 
	// for each process i: 
		// for each resource j: 
			// print value of matrix[i,j]
	return;
}


//**************************************************************
void claim_graph() {
	// declare local variables 
	// prompt for number of resources 
	// allocate memory for vectors 
	// for each resource, prompt for number of units, set resource and available vectors indices
	// prompt for number of processes
	// allocate memory for arrays
	// for each process, for each resource, prompt for maximum number of units requested by process, update maxclaim and GraphNeed arrays  
	// for each process, for each resource, prompt for number of resource units GraphAllocated to process 
	// print resource vector, available vector, maxclaim array, GraphAllocated array, GraphNeed array 
	return;
}


//**************************************************************
void request_resources() {
	// declare local variables
	// prompt for process, resource, and number of units requested
	// if enough units available and request is less than GraphNeed
		// reduce number of available units
		// increase number of GraphAllocated units
		// reduce number of GraphNeeded units
		// print updated available, GraphAllocated, and GraphNeed vectors/matrices
	// else
		//print message that request was denied
	return;
}


//**************************************************************
void release_resources() {
	// declare local variables
	// prompt for process, resource, and number of units requested
	// if enough units GraphAllocated
		// increase number of available units
		// reduce number of GraphAllocated units
		// increase number of GraphNeeded units
		// print updated available, GraphAllocated, and GraphNeed vectors/matrices
	// else
		//print message that release cannot be performed
	return;
}


//******************************************************************
void safe_check() {

	// declare local variables
	// while not all processes are processed
		// for each process  
			// if process has not been processed yet 	 
				// print message comparing GraphNeed vector with available vector
				// for each resource 
					// check for safe processing by comparing process' GraphNeed vector to available vector 
	      			// if each resource is available 
					// print message that process can be processed
					// update number of available units of resource 
					// for each resource 
						//free all resources GraphAllocated to process 
						// increment number of sequenced processes 
				// else print message that process cannot be processed
	//if (no process was processed in the final round of the for-loop)
		// print message of deadlock among processes not processed
	// else print safe sequence of processes
	return;
}


//******************************************************************
void exit_free_mem() {
	// check if vectors/array are not NULL--if so, free each vector/array 	);
	return;
}


//*************************************************************
int main() {
	


    printf("This is Lab 3, showing hdeadlock avoidance through bankers algorithm\n");

	// declare local vars 
    int choice;
	// while user has not chosen to quit 
    do{
        printf("--- Menu --- \n");
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
	 return 1; // indicates success 
} // end of procedure 