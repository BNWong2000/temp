#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 256


int handleCompressedSegment(FILE *file){
    u_int32_t num;
    char character;
    if (fread(&num, sizeof(u_int32_t), 1, file) < 1) {
        return 1;
    }
    if (fread(&character, sizeof(char), 1, file) < 1) {
        return 1;
    }
    for (int i = 0; i < num; i++) {
        printf("%c", character);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (NULL == file) {
            printf("wunzip: cannot open file\n");
            exit(1);
        }
        while (handleCompressedSegment(file) == 0) { }

        fclose(file);
    }

    return 0;
}
