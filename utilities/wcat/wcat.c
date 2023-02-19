//Hey your code goes here..!
#include <stdio.h>
#include <stdlib.h>

void printError(const char *error_message) {
    fprintf(stdout, "%s", error_message);
}

void wcat(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (NULL == file) {
        printError("wcat: cannot open file\n");
        exit(1);
    }

    char buffer[256];
    while( NULL != fgets(buffer, 256, file)) {
        printf("%s", buffer);
    }

    if(ferror(file)) {
        printError("An error occured reading from the file. exiting.\n");
        fclose(file);
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        exit(0);
    }

    for (int i = 1; i < argc; i++) {
        wcat(argv[i]); 
    }

    return 0;
}
