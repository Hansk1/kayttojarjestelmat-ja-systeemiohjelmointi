#include <stdio.h>
#include <string.h>
#include <stdlib.h>



//Rle(Run Lenght Encoding) function:
void unzip(char *filename) {
    FILE *file;


    //Open the file and check for errors:
    if ((file = fopen(filename, "rb")) == NULL) {
        fprintf(stdout, "my-zip: cannot open file\n");
        exit(1);
    }

    int count;
    char character;

    //Read the binary file and print the decompressed data to stdout:
    while (fread(&count, sizeof(count), 1, file) == 1) {
        fread(&character, sizeof(character), 1, file);
        for (int i = 0; i < count; i++) {
            putchar(character);
        }
    }
    fclose(file);
    
}


//Main function:
int main(int argc, char *argv[]) {
    //Check that there is a input file/files:
    if (argc == 1) {
        fprintf(stdout, "wunzip: file1 [file2 ...]\n");
        return(1);
    } 

    //unzip the data:
    for (int i = 1; i < argc; i++) {
        unzip(argv[i]);
    }

    return(0);
}
