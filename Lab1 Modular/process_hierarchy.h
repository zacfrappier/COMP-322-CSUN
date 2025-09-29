// The Interface
// describes how to use this process management program

#ifndef PROCESS_HIERARCHY_H        //ifndef - if not defined, conditional compilation 
#define PROCESS_HEIRARCHY_H

#include <stdio.h>
#include <stdlib.h>

// --- Global Structures ---
#define MAX_PROC 10 //define allows compiler to know value and assign size before running program to process
                    // also good for single point of change

// --- Data Sructures ---
typedef struct childNode {
    int childId;
    struct childNode *next;
}childNode;

typedef struct pcb {
    int parentId;
    childNode *child;
}pcb;

extern pcb *PCB[MAX_PROC];  //extern tells compiler that variable exists but is allocated elsewhere
                            // needed because it is a global variable elsewhere, if not here in header, it will be treated like local variable elsewhere and cause issue

// --- List of functions ---
void printHierarchy();
void initializeProcessHierarchy();
void spawnChild();
void destroyChildrenHelper();
void destroyChildren();
void exitAndFreeMem();

#endif // ends the ifndef for compilation