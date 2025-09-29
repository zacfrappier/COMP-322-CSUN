#include "process_hierarchy.h" 

// --- Global variables ---
pcb *PCB[MAX_PROC];

// --- Procedures ---

void printHierarchy() {
    /* declare local vars */
	printf("Process lists:\n");
	
	for(int i =0; i < MAX_PROC; i++){
		if(PCB[i] != NULL){
			printf("\nProcess id: %d\n", i);
			if(i == 0){
				printf("no parent process\n");
			}else{
				printf("parent process: %d\n", PCB[i]->parentId);
			}

			if(PCB[i]->child == NULL){
				printf("no children processes found.\n");
			}else{
				childNode *currentChild = PCB[i]->child;
				while(currentChild != NULL){
					printf("child process: %d\n", currentChild->childId);
					currentChild = currentChild->next;
				}
			}
		}
	}
}

void initiliazeProcessHierarchy() {
	int choice2;

	//Check if PCB[0] is already initialized 
	if(PCB[0] != NULL){
		printf("A Process hierarchy already exist, choose one of the following:\n");
		printf("1) proceed to reinitialize and destroy current heirarchy\n");
		printf("2) return to main menu\n\n");
		printf("Enter choice: ");
		scanf("%d", &choice2);
		while(choice2 != 1 && choice2 != 2){
			printf("invalid choice, please pick 1 or 2");
			return;
		}
		if(choice2 == 2){
			printf("Returning to main menu\n");
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

	for(int i = 1; i < MAX_PROC; i++){ // start at 1 b/c 0 is set
		PCB[i] = NULL;
	}

	/* printf hierarchy of processes */
	printf("here is the your heirarchy: \n");
	printHierarchy();
	return;
}

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
	if(parentIndex < 0 || parentIndex >= MAX_PROC || PCB[parentIndex] == NULL){ //also included excluded range
		printf("this parend Id is either out of range or hasnt yet been created\n");
        printf("list of current hierarchy: \n");
        printHierarchy(); // remind the dumb user what process they already created
		printf("\nreturning to main menu...\n\n");
		return;
	}
	/* search for first available index q without a parent in a while loop */	
	for(int i = 0; i < MAX_PROC; i++){
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
		free(PCB[childIndex]); //release the memory in heap and memory address
		PCB[childIndex] = NULL; // delete the now invalid index
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
	printHierarchy();
	return;
}

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
}

void destroyChildren() {
	/* declare local vars */
	int parentIndex;
	/* prompt for process index p */
	printf("enter id of process to destroy its childrens: ");
	scanf("%d", &parentIndex);

	if( parentIndex < 0 || parentIndex >= MAX_PROC || PCB[parentIndex] == NULL){
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
	printHierarchy();
	return;
}

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
}

