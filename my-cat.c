#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Function to open a file and read it to stdout:
void readFile(char *fileName) {
    FILE *file;

    //Open the file and check for errors:
    if ((file = fopen(fileName, "r")) == NULL) {
        fprintf(stdout, "wcat: cannot open file\n");
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;

    //Print the file line by line to stdout:
    while(getline(&line, &len, file) != -1) {
        fprintf(stdout, "%s", line);
    }

    //Free the line buffer:
    free(line);

    //Close the file:
    fclose(file);

    return;
}


int main(int argc, char *argv[]) {
    if (argc == 1) {
        return(0);
    }

    int argIndex = 1;
    while(argIndex <= argc - 1) {
        readFile(argv[argIndex]);
        argIndex ++;
    };
    return(0);
}
