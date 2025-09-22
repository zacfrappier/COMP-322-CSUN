#ifndef __ADDRESS_BOOK_H__
#define __ADDRESS_BOOK_H__
/* .h are header files
    header files used to declare data structures, and definitions */
    
/* TODO: Add your structures here */ 
/* create anonymous structure that is called with Person my_person */
/*  typedef allows calling by name 
    Name at end after object declaration creates anonymous structure */

typedef struct {
    char name[50];
    int age;
    char phone[20];
} Person;

typedef struct {
    Person* people;
    int count;
} Address_book;

/* Function declarations. Do not modify! Implement those functions in address_book.c */
void print_person(const Person* person);
void print_address_book(const Address_book* address_book);

Address_book* create_address_book(void);
void destroy_address_book(Address_book* address_book);

#endif /* __ADDRESS_BOOK_H__ */