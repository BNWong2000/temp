#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct LinkedList {
    struct LinkedList* next;
    char *word;
};

typedef struct LinkedList LinkedList;

void *myMalloc(const size_t size) {
    void *result = malloc(size);
    if (result == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    return result;
}

LinkedList *createNode(){
    LinkedList *newNode = (LinkedList *) myMalloc(sizeof(LinkedList));
    newNode->word = NULL;
    newNode->next = NULL;
    return newNode;
}

void destroyList(LinkedList *head) {
    LinkedList *temp;
    while (head != NULL) {
        temp = head->next;
        free(head->word);
        free(head);
        head = temp;
    }
}

/**
 * Returns the head of the reversed list. 
 */ 
LinkedList *reverse(LinkedList *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    LinkedList *curr = head->next;
    head->next = NULL;
    while(curr != NULL) {
        LinkedList *temp = curr->next;
        curr->next = head;
        head = curr;
        curr = temp;
    }
    
    return head;
}

void printList(FILE *output, LinkedList *list) {
    while(list != NULL) {
        fprintf(output, "%s", list->word);
        list = list->next;
    }
}

LinkedList *getInput(FILE *input) {
    int c;
    size_t n = 0;
    LinkedList *head = createNode();
    LinkedList *temp = head;
    LinkedList *temp2 = temp;
    while ((c = getline(&(temp->word), &n, input)) != -1) {
        temp->next = createNode();
        temp2 = temp;
	temp = temp->next;
    }
    free(temp->word);
    free(temp);
    temp2->next = NULL;
    return head;
}


int main(int argc, char *argv[]) {
    FILE *input_file = stdin;
    FILE *output_file = stdout;
    if (argc == 2) {
        input_file = fopen(argv[1], "r");
    } else if (argc == 3) {
        int n1 = strlen(argv[1]);
        int n2 = strlen(argv[2]);
        int n = n1 < n2 ? n2 : n1;
        if (strncmp(argv[1], argv[2], n) == 0) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }

        input_file = fopen(argv[1], "r");
        output_file = fopen(argv[2], "w");
    } else if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return 1;
    }
    if (input_file == NULL) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
        return 1;
    }
    if (output_file == NULL) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
        return 1;
    }

    if (argc == 3) {
        struct stat *fileInfo1 = malloc(sizeof(struct stat));
        struct stat *fileInfo2 = malloc(sizeof(struct stat));
        lstat(argv[1], fileInfo1);
        lstat(argv[2], fileInfo2);
        if (fileInfo1->st_ino == fileInfo2->st_ino) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }
        free(fileInfo1);
        free(fileInfo2);
    }
    LinkedList *result = getInput(input_file);
    
    result = reverse(result);
    printList(output_file, result);
    destroyList(result);
    
    if (argc == 2) {
        fclose(input_file);
    } else if (argc == 3) {
        fclose(input_file);
        fclose(output_file);
    }

    return 0;
}
