#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Function to open a file and read it to stdout:
void readFile(char *searchTerm, char *fileName) {
    FILE *file;

    //Open the file and check for errors:
    if ((file = fopen(fileName, "r")) == NULL) {
        fprintf(stdout, "wgrep: cannot open file\n");
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;

    //Analyse the file line by line:
    while(getline(&line, &len, file) != -1) {
        if(strstr(line, searchTerm)) {
            fprintf(stdout, "%s", line);
        }
    }

    //Free the line buffer:
    free(line);

    //Close the file:
    fclose(file);

    return;
}

//Function to read data from standard input:
void readFromStdin(char *searchTerm) {
    char *line = NULL;
    size_t len = 0;
    
    //Get line from standard input and if the line contains the search term -> print the line to stdout:
    while(getline(&line, &len, stdin) != -1) { 
        if(strstr(line, searchTerm)) {
            fprintf(stdout, "%s", line);
        }
    }
    
    //Free the line buffer:
    free(line);

    return;
}

//Main function:
int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stdout, "wgrep: searchterm [file ...]\n");
        return(1);
    } else if (argc == 2) {
        readFromStdin(argv[1]);
        return(0);
    }


    int argIndex = 2;
    while(argIndex <= argc - 1) {
        readFile(argv[1], argv[argIndex]);
        
        argIndex ++;
        if(argIndex < argc) {
            printf("\n");
        }
    };

    return(0);
}
