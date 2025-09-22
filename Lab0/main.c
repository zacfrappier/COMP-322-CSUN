#include <stdio.h>
#include "address_book.h"

int main() {
    printf("Welcome to an address book that doesnt contain any actual addresses.\n made by Zachary Frappier");
    Address_book* my_address_book = NULL; //initialize a
    int choice;

    do{
        printf("\n ===== Menu =====\n");
        printf("plz select option 1-4\n");
        printf("1. create address book\n");
        printf("2. view address book \n");
        printf("3. Delete address book\n");
        printf("4. Exit\n");
        printf("enter your choice\n");
        
        //need following if to check input
        if(scanf("%d", &choice) != 1){
            printf("invalid option, choose 1-4");
            while(getchar() != 'n'); // this stops the infinite loop issue i had
            continue;
        }
        while (getchar() != '\n');

        switch (choice){
            case 1:
                // Option 1: Create a new address book.
                if (my_address_book != NULL) {
                    printf("An address book already exists. Please delete it first.\n");
                } else {
                    my_address_book = create_address_book();
                    if (my_address_book != NULL) {
                        printf("Address book created successfully.\n");
                    }
                }
                break;
            case 2:
                // Option 2: View the address book.
                if (my_address_book == NULL) {
                    printf("No address book exists. Please create one first.\n");
                } else {
                    printf("\n");
                    print_address_book(my_address_book);
                }
                break;
            case 3:
                // Option 3: Delete the address book.
                if (my_address_book == NULL) {
                    printf("No address book to delete.\n");
                } else {
                    destroy_address_book(my_address_book);
                    my_address_book = NULL; // Set the pointer to NULL after freeing.
                    printf("Address book deleted.\n");
                }
                break;
            case 4:
                // Option 4: Exit the program.
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number from 1 to 4.\n");
                break;
        }
    } while(choice != 4);

    //Final Cleanup in case user forgot =/ (frowny face)
    if(my_address_book != NULL){
        destroy_address_book(my_address_book);
        printf("u forgot to clean ur space. LAZY \n");
    }
    return 0;
}