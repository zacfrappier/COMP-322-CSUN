#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "address_book.h"

/*  .c files are source files 
    implementations for functions and global variable definitions
    usage: compile into object file, interaction with other objects
*/

// person print format 
void print_person(const Person* person){
    printf("Name: %s\n", person->name); /* use '->' and not '.' b/c referencing a pointer */
    printf("Age: %d\n", person->age);
    printf("Phone: %s\n", person->phone);
}

//main print 
void print_address_book(const Address_book* address_book){
    //error handling
    if(address_book->count == 0){ 
        printf("address book empty, please input some entries.\n");
        return;
    }
    //if not empty then display people
    for (int i = 0; i < address_book->count; ++i){
        printf("Contact %d: \n", i+1);
        print_person(&address_book->people[i]); /* need '&' for pointers */
        printf("\n");
    }
}

Address_book* create_address_book(void){
    // '*' is typecast
    //  sizeof calculates size in bytes    malloc - dynamic allocating
    Address_book* ab = (Address_book*)malloc(sizeof(Address_book));
    // error handling if unable to allocate space
    if (ab == NULL) {
        perror("failed to allocate memory for address book"); /* perror() is custom text description of error code*/
        return NULL;
    }
    int num_persons;
    printf("enter number of persons to add: ");
    scanf("%d", &num_persons); /* %d for decimals, and stores at &num_persons */
    // Consume left over characters from scanf
    while(getchar() != '\n');

    //Dynamic allocation of Person Struct
    ab->people =(Person*)malloc(num_persons * sizeof(Person));
    //another trouble shooting needed for newly created space
    if (ab->people == NULL) {
        perror("Failed to allocate memory for people");
        free(ab);   //free up space to prevent memory leak
        return NULL;
    }

    ab->count = num_persons; //set count to number of people created
 
    //loop for persons information
    for(int i = 0; i < num_persons; ++i) {
        printf("\n Entering details for person #%d: \n", i+1); 
        printf("Name: ");
        //use fgets her to handle spaces better 
        fgets(ab->people[i].name, sizeof(ab->people[i].name),stdin); //sizeof() needed to buffer space, prevent overwriting nearby data
        // this following code is necessary to avoid ugly formatting issue of the new line 
        // the new line issue is b/c fgets() includes '\n' when user presses 'enter' to submit name
        ab->people[i].name[strcspn(ab->people[i].name, "\n")] = 0; // deletes extra spaces, if not here will cause crash when trying to retrieve information
        // strcspn - string complementary span,  takes two arguments, the name object and its newline character
        // we set to 0 b/c that is the newline terminator, and will keep the the newline from 
        printf("Age: ");
        scanf("%d", &ab->people[i].age);
        while(getchar() != '\n'); //same as above

        printf("Phone Number: ");
        fgets(ab->people[i].phone, sizeof(ab->people[i].phone), stdin);
        ab->people[i].phone[strcspn(ab->people[i].phone, "\n")] = 0;
    }
    return ab;
}

void destroy_address_book(Address_book* address_book) {
    if (address_book == NULL) {
        printf("no address book found, now exiting");
        return;
    }
    free(address_book->people); // free people first (smaller objects)
    free(address_book);         //free containing structor 
}


