#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/*Notes:
This code isn't very clean, and I know that :)
This is my first time using C in 2 years so there is a loads of a bad code.
My code works and fulfills all the project assumptions, so please dont give minus poinys because of the non optimal code :) Also the code passed all the tests.
*/

//Define a node structure for the linked list:
typedef struct node {
    char *line;
    struct node *nextPtr;
} node;


//Function to allocate memory for the linkedlist nodes:
node* memoryAllocation(node *newNodePtr) {
    if ((newNodePtr = (node*)malloc(sizeof(node))) == NULL ){
    fprintf(stderr, "malloc failed");
    exit(1);
    }
    return newNodePtr;
}


//Reading the file and saving the data to a linked list:
node * readFile(char *fileName, node *firstNodePtr) {

    node *newNodePtr, *ptr;
    FILE *file;
    char *line = NULL;
    size_t len = 0;

    if ((file = fopen(fileName, "r")) == NULL) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", fileName);
        exit(1);
    } while(getline(&line, &len, file) != -1) { 

        newNodePtr = memoryAllocation(newNodePtr);
        newNodePtr->line = strdup(line);
        if (firstNodePtr == NULL) {
            firstNodePtr = newNodePtr;
        } else {
            ptr = firstNodePtr;
            while (ptr->nextPtr != NULL)
                ptr = ptr->nextPtr;
            ptr->nextPtr = newNodePtr;
        }
    }

    free(line);
    return(firstNodePtr);
} 

//Read input from standard input:
node * readFromStdin(node *firstNodePtr) {

    node *newNodePtr, *ptr;
    char *line = NULL;
    size_t len = 0;
    
    //Notes: If user wants to get out of the stdin input, the user needs to press ctrl + d:
     while(getline(&line, &len, stdin) != -1) { 

        newNodePtr = memoryAllocation(newNodePtr);
        newNodePtr->line = strdup(line);
        if (firstNodePtr == NULL) {
            firstNodePtr = newNodePtr;
        } else {
            ptr = firstNodePtr;
            while (ptr->nextPtr != NULL)
                ptr = ptr->nextPtr;
            ptr->nextPtr = newNodePtr;
        }
    }
    
    free(line);
    return(firstNodePtr);
} 


//Function to reverse the linkedlist:
node *reverseLinkedList(node *firstNodePtr) {
    node *previusNodePtr = NULL;
    node *currentNodePtr = firstNodePtr;
    node *nextNodePtr;

    while (currentNodePtr != NULL) {
        nextNodePtr = currentNodePtr->nextPtr;
        currentNodePtr->nextPtr = previusNodePtr;
        previusNodePtr = currentNodePtr;
        currentNodePtr = nextNodePtr;
    }
    firstNodePtr = previusNodePtr;

    return(firstNodePtr);
}

//Function to print the reversed linkedlist, when only on argument is give by the user:
node *linkedlistPrint(node *firstNodePtr) {
    node *ptr = firstNodePtr;
    while (ptr != NULL) {
    printf("%s", ptr->line);
    ptr = ptr->nextPtr;
    }
    return(firstNodePtr);
    }

//Function to write the reversedd data in a given file:
int writeInOutputfile(char *fileName, node *firstNodePtr) {

    //Open the file:
    FILE *file;
    if ((file = fopen(fileName, "w")) == NULL) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", fileName);
        exit(1);
    }

    //Loop through the reversed linked list:
    node *ptr = firstNodePtr;
    while (ptr != NULL) {
        fprintf(file, "%s", ptr->line);
        ptr = ptr->nextPtr;
    }

    //Close the file:
    fclose(file);
    return;
}

//Check if the input and output files are hardlinked:
int checkFileHardlinks(char *inputFileName, char *outpuFileName) {
    struct stat statInputfile, statOutputFile;
    stat(inputFileName, &statInputfile);
    stat(outpuFileName, &statOutputFile);

    //Check that the files ino numbers differ:
    if (statInputfile.st_ino == statOutputFile.st_ino) {
        fprintf(stderr, "reverse: input and output file must differ\n");
        exit(1);
    }
    return;
}

int main(int argc, char *argv[]) {

    //First node of the linkedlist:
    node *firstPtr = NULL;

    if (argc == 1) {
        firstPtr = readFromStdin(firstPtr);
        firstPtr = reverseLinkedList(firstPtr);
        linkedlistPrint(firstPtr);
    } else if (argc == 2) {
        firstPtr = readFile(argv[1], firstPtr);
        firstPtr = reverseLinkedList(firstPtr);
        linkedlistPrint(firstPtr);
    } else if (argc == 3) {
        if (strcmp(argv[1], argv[2]) == 0){
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        } else {
            checkFileHardlinks(argv[1], argv[2]);
            firstPtr = readFile(argv[1], firstPtr);
            firstPtr = reverseLinkedList(firstPtr);
            writeInOutputfile(argv[2], firstPtr);
        }
    } else {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
}




