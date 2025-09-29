#include <stdio.h>
#include <stdlib.h>

/* Define structures and global constants, including:
the pcb type, the children linked list type, the maximum number of processes
pcb - process control blocks*/
// '*' usage to point to hold memory addresses rather than an object itself

//Child structure 
typedef struct childNode { // struct's tag - needed for self referencing the for nodes
	int childId;
	struct childNode *next; // struct tag is used here, not pointing to itself, but a new child struct- needed for linked lists
}childNode; //typedef alias

// Process control block structure (really just parent?)
typedef struct pcb {
	int parentId;
	childNode *child; //declares member variable 'child' pointing to object 'childNode'
}pcb;  

pcb *PCB[10]; //set max for pcbs to 10

// Function Lists - 'compiler's blueprintfs' 
void printfHierarchy();
void initiliazeProcessHierarchy();
void spawnChild();
void destroyChildrenHelper();
void destroyChildren();
void exitAndFreeMem();

/***************************************************************/
//PROCEDURE TO printf HIERARCHY OF PROCESSES
void printfHierarchy() {
	/* declare local vars */
	printf("Process lists:\n");
	/* for each process index i from 0 up to (but not including) maximum number of processes*/
	for(int i =0; i < 10; i++){
		if(PCB[i] != NULL){
			printf("Process id: %d\n", i);
			if(i == 0){
				printf("no parent process\n");
			}else{
				printf("parent process: %d\n", PCB[i]->parentId);
			}

			if(PCB[i]->child == NULL){
				printf(" no children processes found.\n");
			}else{
				childNode *currentChild = PCB[i]->child;
				while(currentChild != NULL){
					printf("child process: %d\n", currentChild->childId);
					currentChild = currentChild->next;
				}
			}
		}
	}
		/* if PCB[i] is not NULL{
		} */
			/* printf process id, parent id, list of children processes */
} /* end of procedure */


/***************************************************************/
//PROCEDURE FOR OPTION #1

void initiliazeProcessHierarchy() {
	int choice2;

	//Check if PCB[0] is already initialized 
	if(PCB[0] != NULL){
		printf("A Process hierarchy already exist, choose one of the following:\n");
		printf("1) proceed to reinitialize and destroy current heirarchy\n");
		printf("2) return to main menu\n");
		printf("Enter choice: ");
		scanf("%d", &choice2);
		while(choice2 != 1 && choice2 != 2){
			printf("invalid choice, please pick 1 or 2");
			return;
		}
		if(choice2 == 2){
			printf("Returning to main menu");
			return;
		}else{
			printf("detroying current heirarchy ... \n");
			exitAndFreeMem();
		}
	}

	/* Allocate memory for PCB[0] */
	PCB[0] = (pcb*)malloc(sizeof(pcb)); //reserve memory block on heap, (pcb*) typecast 
	//best practice for ensuring 
	if(PCB[0] == NULL){
		printf("Error: Memory allocation failed creating hierarchy");
		return;
	}
	
	/* Intitialize all other PCB's to NULL */
	PCB[0]->parentId = -1; // -1 indicates no parent for first lineage
	PCB[0]->child = NULL;

	for(int i = 1; i < 10; i++){ // start at 1 b/c 0 is set
		PCB[i] = NULL;
	}

	/* printf hierarchy of processes */
	printf("here is the your heirarchy: \n");
	printfHierarchy();
	return;
} /* end of procedure */

	
/***************************************************************/
//PROCEDURE FOR OPTION #2
void spawnChild() {
	//check for initialization
	if(PCB[0] == NULL){
		printf("Error: Need to initialize the heirachy before process creation\n");
		return;
	}
	/* define local vars */
	int parentIndex;
	int childIndex = -1; //-1 used to indicate no more memory and check if full

	/* prompt for parent process index p */
	printf("enter parent ID: ");
	scanf("%d", &parentIndex);

	/* if PCB[p] is NULL, printf message process does not exist, return */
	if(parentIndex < 0 || parentIndex >= 10 || PCB[parentIndex] == NULL){ //also included excluded range
		printf("this parend Id is either out of range or hasnt yet been created");
		printf("returning to main menu...\n");
		return;
	}
	/* search for first available index q without a parent in a while loop */	
	for(int i = 0; i < 10; i++){
		if(PCB[i] == NULL){
			childIndex = i;
			break;
		}
	}
	/* if maximum number of processes reached, printf message of no more avaiable PCBs */
	if(childIndex == -1){
		printf("maximum number of processes reached, unable to create another");
		return;
	}
	/* allocate memory for new child process, initialize fields */
	PCB[childIndex] = (pcb*)malloc(sizeof(pcb));
	if(PCB[childIndex] == NULL){
		perror("Error:PCB memory allocation failed");
	}
	/* record the parent's index p in PCB[q] */
	PCB[childIndex]->parentId = parentIndex;
	/* initialize the list of children of PCB[q] as empty */
	PCB[childIndex]->child = NULL;
	/* append the node containing the child's index q to the children linked list of PCB[p] */
	childNode *newChildNode = (childNode*)malloc(sizeof(childNode));
	//best practice as always to check if allocation was successful
	if(newChildNode == NULL){
		perror("memory allocation failed for child node");
		free(PCB[childIndex]); //release the memory 
		PCB[childIndex] = NULL; // delete the index
		return;
	}

	newChildNode->childId = childIndex; // set the id to match index
	newChildNode->next = NULL; //linked leist end
	
	if(PCB[parentIndex]->child == NULL){ // new child is first of list
		PCB[parentIndex]->child = newChildNode;
	}else{								// add new child at end of list
		childNode *currentChild = PCB[parentIndex]->child; // create temp child struct to move down list
		while (currentChild->next != NULL){
			currentChild = currentChild->next; // move to next element of list
		}
		currentChild->next = newChildNode;
	}
	/* printf hierarchy of processes */
	printf("successfully spawned new child\n here is current hierarchy:\n");
	printfHierarchy();
	return;
} /* end of procedure */


/***************************************************************/
//RECURSIVE PROCEDURE TO DESTROY CHILDREN PROCESSES
void destroyChildrenHelper(childNode *node) {
	/* declare local vars */
	int nodesChild = node->childId;
	/* check if end of linked list--if so return */
	if(node == NULL){
		return;
	}
	/* else call self on next node in linked list */
	destroyChildrenHelper(node->next); // prevents losing head
		/* set variable q to current node's process index field */
		/* call self on children of PCB[q] */ 	
		/* free memory of PCB[q] and set PCB[q] to NULL*/
		/* free memory of paramter and set to NULL */
	return;
} /* end of procedure */


/***************************************************************/
// PROCEDURE FOR OPTION #3
void destroyChildren() {
	/* declare local vars */
	int parentIndex;
	/* prompt for process index p */
	printf("enter id of process to destroy its childrens: ");
	scanf("%d", &parentIndex);

	if( parentIndex < 0 || parentIndex >= 10 || PCB[parentIndex] == NULL){
		perror("that id is either out of range or does not exist, returning to main menu\n");
		return;
	}
	/* call recursive procedure to destroy children of PCB[p] */
	printf("you've chosen infanticide of PCB[%d]", parentIndex);
	destroyChildrenHelper(PCB[parentIndex]->child);
	/* reset children of PCB[p] to NULL */
	PCB[parentIndex]->child = NULL;
	/* printf hierarchy of processes */

	printf(" many small graves were dug\n printfing remaining heirarchy: \n");
	printfHierarchy();
	return;
} /* end of procedure */


/***************************************************************/
//PROCEDURE FOR OPTION #4
void exitAndFreeMem() { 
	/* if PCB[0] is non null)*/
	if(PCB[0] != NULL && PCB[0]->child != NULL){
		destroyChildrenHelper(PCB[0]->child);
		PCB[0]->child = NULL;
	} 
		/* if children of PCB[0] is not null */
			/* call recursive procedure to destroy children of PCB[0] */
	if (PCB[0] != NULL){
		free(PCB[0]);
		PCB[0] = NULL;
	}
	/* free memory of all PCB's */
	
	return;
} /* end of procedure */


/***************************************************************/
int main() {
    printf(" Welcome to Project 1, \n Objective: Simulate process creation and destruction when implementing linked lists");
	/* declare local vars */
    int choice; 
	/* while user has not chosen to quit */
		/* printf menu of options */
    do{
        printf("\n=====Menu=====\n");
        printf("1. Initialize process hierarchy\n");
        printf("2. Create new child \n");
        printf("3. Destroy all childrens 1 \n");
        printf("4. Exit and free memory \n");
        printf("Select an option 1-4: ");
        
        scanf("%d", &choice);   //get user input 

        switch(choice){
            case 1: 
                printf("you've selected to initialize hierarchy...\n\n");
                initiliazeProcessHierarchy();
                break;
            case 2: 
                printf("you've selected to spawn a child\n");
                spawnChild();
                //maybe put if statement that checks to see if new child created
                break;
            case 3:
                printf("you've selected to destroy all the children...");
                //put function 3 here
                printf("...children are gone");
                break;
            case 4:
                printf("you've selected to be done, goodbye for now, all childrens and their parents will now perish");
                exitAndFreeMem();
                exit(0);
            default:
                printf("choose again\n");
                break;
        }
    } while (choice !=4);
    return 0;
		/* prompt for menu selection */
		/* call appropriate procedure based on choice--use switch statement or series of if, else if, else statements */	
	 //return 1; /* indicates success */
} /* end of procedure */