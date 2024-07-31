#include <stdio.h>
#include <string.h>
#include <stdlib.h>



//Rle(Run Lenght Encoding) function:
void rle() {
    FILE *file;


    //Open the file and check for errors:
    if ((file = fopen("temporaryOutputFile.txt", "r")) == NULL) {
        fprintf(stdout, "my-zip: cannot open file\n");
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    int count = 1;

    //Analyse the file line by line and encode it:
    while(getline(&line, &len, file) != -1) {
        for (int i = 0; i < strlen(line); i++) {
            if (line[i] == line[i + 1]) {
                count ++;
            } else {
                fwrite(&count, sizeof(count), 1, stdout);
                fwrite(&line[i], sizeof(char), 1, stdout);
                count = 1;
            }
        }
    }
    free(line);
    fclose(file);
    
}


//Helper function to create a file with all argument files merged: (I know that this isn't best practice)
FILE * fileMergeHelper(int argc, char * argv[]) {
    
    
    //Create the temporary file:
    FILE *tempFile;

    tempFile = fopen("temporaryOutputFile.txt", "w");



    FILE *file;

    for (int i = 1; i < argc; i++) {
    //Open the file and check for errors:
        if ((file = fopen(argv[i], "r")) == NULL) {
            fprintf(stdout, "my-zip: cannot open file\n");
            exit(1);
        }

        char *line = NULL;
        size_t len = 0;

        //Analyse the file line by line and encode it:
        while(getline(&line, &len, file) != -1) {
            fprintf(tempFile, "%s", line);
        }

        free(line);
        fclose(file);
    }
    fclose(tempFile);
    return(tempFile);
};

//Main function:
int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stdout, "wzip: file1 [file2 ...]\n");
        return(1);
    } 

    //Create temp file:
    fileMergeHelper(argc, argv);

    //Compress the data:
    rle();

    //Remove the temp file:
    remove("temporaryOutputFile.txt");

    return(0);
}
