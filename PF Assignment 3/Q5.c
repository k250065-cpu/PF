#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 2
#define MAX_INPUT 1000

void checkAllocation(void *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Memory Allocation Failed\n");
        exit(1);
    }
}

void insertLine(char ***lines, int *count, int *capacity, int index, const char *text) {

    if (index < 0 || index > *count) {
        printf("Invalid Index\n");
        return;
    }

    if (*count == *capacity) {
        *capacity *= 2;
        *lines = realloc(*lines, (*capacity) * sizeof(char *));
        checkAllocation(*lines);
    }

    memmove(&(*lines)[index + 1], &(*lines)[index], 
            (*count - index) * sizeof(char*));

    (*lines)[index] = malloc(strlen(text) + 1);
    checkAllocation((*lines)[index]);

    strcpy((*lines)[index], text);
    (*count)++;
}

void deleteLine(char ***lines, int *count, int index) {
    if (index < 0 || index >= *count) {
        printf("Invalid Index\n");
        return;
    }

    free((*lines)[index]);

    memmove(&(*lines)[index], &(*lines)[index + 1],
            (*count - index - 1) * sizeof(char*));

    (*count)--;
    printf("Line Deleted\n");
}

void printAllLines(char **lines, int count) {
    printf("\n--- TEXT BUFFER ---\n");
    for (int i = 0; i < count; i++)
        printf("%d: %s\n", i, lines[i]);
    printf("-------------------\n\n");
}

void shrinkToFit(char ***lines, int *capacity, int count) {
    *capacity = count;
    *lines = realloc(*lines, count * sizeof(char*));
    checkAllocation(*lines);
    printf("Shrunk Buffer to Exactly %d Lines\n", count);
}

void freeAll(char ***lines, int *count, int *capacity) {
    for (int i = 0; i < *count; i++)
        free((*lines)[i]);

    free(*lines);

    *lines = NULL;
    *count = 0;
    *capacity = 0;
}

void saveToFile(char **lines, int count, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Could Not Open File for Writing\n");
        return;
    }

    for (int i = 0; i < count; i++)
        fprintf(fp, "%s\n", lines[i]);

    fclose(fp);
    printf("Saved to %s\n", filename);
}

void loadFromFile(char ***lines, int *count, int *capacity, const char *filename) {

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Could Not Open File for Reading\n");
        return;
    }

    freeAll(lines, count, capacity);

    *capacity = INITIAL_CAPACITY;
    *lines = malloc(*capacity * sizeof(char*));
    checkAllocation(*lines);

    *count = 0;

    char buffer[MAX_INPUT];

    while (fgets(buffer, MAX_INPUT, fp)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        insertLine(lines, count, capacity, *count, buffer);
    }

    fclose(fp);
    printf("File Loaded\n");
}

int main() {

    char **lines = malloc(INITIAL_CAPACITY * sizeof(char*));
    checkAllocation(lines);

    int count = 0;
    int capacity = INITIAL_CAPACITY;

    int choice, index;
    char temp[MAX_INPUT];

    while (1) {
        printf("\n=== Minimal Text Editor ===\n");
        printf("1. Insert Line\n");
        printf("2. Delete Line\n");
        printf("3. Print All Lines\n");
        printf("4. Shrink To Fit\n");
        printf("5. Save To File\n");
        printf("6. Load From File\n");
        printf("7. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {

        case 1:
            printf("Enter Index: ");
            scanf("%d", &index);
            getchar();

            printf("Enter Text: ");
            fgets(temp, MAX_INPUT, stdin);
            temp[strcspn(temp, "\n")] = '\0';

            insertLine(&lines, &count, &capacity, index, temp);
            break;

        case 2:
            printf("Enter Index: ");
            scanf("%d", &index);
            deleteLine(&lines, &count, index);
            break;

        case 3:
            printAllLines(lines, count);
            break;

        case 4:
            shrinkToFit(&lines, &capacity, count);
            break;

        case 5:
            printf("Enter File Name: ");
            scanf("%s", temp);
            saveToFile(lines, count, temp);
            break;

        case 6:
            printf("Enter File Name: ");
            scanf("%s", temp);
            loadFromFile(&lines, &count, &capacity, temp);
            break;

        case 7:
            freeAll(&lines, &count, &capacity);
            printf("Exiting Program\n");
            return 0;

        default:
            printf("Invalid Option\n");
        }
    }
    return 0;
}