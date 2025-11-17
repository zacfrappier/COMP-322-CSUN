/*
Zachary Frappier 
Comp 322 Prof Ebrahimi
Lab 3
*/
#include <stdio.h>
#include <stdlib.h>

// Declare dynamic arrays/vectors and global variables
int placeholder = INT_MIN;   //just used for things i need to change later
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

allocated p x r matrix 

need p x r matrix

*/



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
	// for each process, for each resource, prompt for maximum number of units requested by process, update maxclaim and need arrays  
	// for each process, for each resource, prompt for number of resource units allocated to process 
	// print resource vector, available vector, maxclaim array, allocated array, need array 
	return;
}


//**************************************************************
void request_resources() {
	// declare local variables
	// prompt for process, resource, and number of units requested
	// if enough units available and request is less than need
		// reduce number of available units
		// increase number of allocated units
		// reduce number of needed units
		// print updated available, allocated, and need vectors/matrices
	// else
		//print message that request was denied
	return;
}


//**************************************************************
void release_resources() {
	// declare local variables
	// prompt for process, resource, and number of units requested
	// if enough units allocated
		// increase number of available units
		// reduce number of allocated units
		// increase number of needed units
		// print updated available, allocated, and need vectors/matrices
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
				// print message comparing need vector with available vector
				// for each resource 
					// check for safe processing by comparing process' need vector to available vector 
	      			// if each resource is available 
					// print message that process can be processed
					// update number of available units of resource 
					// for each resource 
						//free all resources allocated to process 
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
        printf("1) Enter Claim graph (need) \n"); 
        printf("2) Request resource (request)\n"); 
        printf("3) Release resource (allocation)\n"); 
        printf("4) Determine safe sequence\n"); 
        printf("5) free memory and Exit\n"); 
        scanf("%d", &choice);

        switch(choice){
            case 1:
                prtinf("you've selected to enter claim graph of resources needed\n");
                claim_graph();
                break;
            case 2:
                prtinf("you've selected to request resources\n");
                request_resources();
                break;
            case 3:
                prtinf("you've selected to enter claim graph of resources needed\n");
                release_resources();
                break;
            case 4:
                prtinf("you've selected to enter claim graph of resources needed\n");
                safe_check();
                break;
            case 5:
                prtinf("you've selected to enter claim graph of resources needed\n");
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