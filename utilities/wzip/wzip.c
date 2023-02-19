#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 256

void writeCompressedSegment(u_int32_t num, char character) {
    // printf("%d - %c .", num, character);
    fwrite(&num, sizeof(u_int32_t), 1, stdout);
    fwrite(&character, sizeof(char), 1, stdout);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    char buffer[BUFF_SIZE];
    char currChar;
    u_int32_t currCount = 0;
    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (NULL == file) {
            printf("wzip: cannot open file\n");
            exit(1);
        }
        int num_read;
        while((num_read = fread(buffer, sizeof(char), BUFF_SIZE, file)) > 0) {
            for (int i = 0; i < num_read; i++) {

                if (currCount == 0) {
                    currChar = buffer[i];
                    currCount = 1;
                } else if (currChar == buffer[i]) {
                    currCount++;
                } else {
                    writeCompressedSegment(currCount, currChar);
                    currChar = buffer[i];
                    currCount = 1;
                }
            }
        }
        

        fclose(file);
    }
    writeCompressedSegment(currCount, currChar);

    return 0;
}
