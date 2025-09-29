#include "process_hierarchy.h"

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
        printf("4. Exit and free memory \n\n");
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
}