#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int contains_word (const char *line, const char *word) {
    if (NULL != strstr(line, word)) {
        return 1;
    }
    return 0;
}

void wgrep_file(FILE *file, const char *word) {
    if (NULL == file) {
        exit(1);
    }

    int c;
    char *line = NULL;
    size_t n = 0;
    while ((c = getline(&line, &n, file)) != -1) {
        if (contains_word(line, word)) {
            fprintf(stdout, "%s", line);
        }
    }
    free(line);
}

void wgrep(const char *file_name, const char *word) {
    FILE *file = fopen(file_name, "r");

    if (NULL == file) {
        fprintf(stdout, "wgrep: cannot open file\n");
        exit(1);
    }
    
    wgrep_file(file, word);

    fclose(file);
}

int main (int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stdout, "wgrep: searchterm [file ...]\n");
        exit(1);
    }
    const char *word = argv[1];

    if (argc == 2) {
        wgrep_file(stdin, word);
    }

    for(int i = 2; i < argc; i++) {
        wgrep(argv[i], word);
    }

    return 0;
}
