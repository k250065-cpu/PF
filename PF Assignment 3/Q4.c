#include <stdio.h>
#include <string.h>

struct Book {
    int id;
    int popularity;
    int lastAccess;
    int used;
};

int main() {
    int capacity, Q;
    printf("Enter Shelf Capacity and Number of Operations:\n");
    scanf("%d %d", &capacity, &Q);

    struct Book shelf[capacity];

    for (int i = 0; i < capacity; i++)
        shelf[i].used = 0;

    int timer = 0;

    while (Q--) {
        char op[10];
        scanf("%s", op);

        if (strcmp(op, "ADD") == 0) {
            int id, score;
            scanf("%d %d", &id, &score);
            timer++;

            int found = -1;

            for (int i = 0; i < capacity; i++) {
                if (shelf[i].used && shelf[i].id == id) {
                    found = i;
                    break;
                }
            }

            if (found != -1) {
                shelf[found].popularity = score;
                shelf[found].lastAccess = timer;
                printf("Updated Book ID %d with New Popularity %d\n", id, score);
            } 
            else {
                int empty = -1;
                for (int i = 0; i < capacity; i++) {
                    if (!shelf[i].used) {
                        empty = i;
                        break;
                    }
                }

                if (empty != -1) {
                    shelf[empty].used = 1;
                    shelf[empty].id = id;
                    shelf[empty].popularity = score;
                    shelf[empty].lastAccess = timer;
                    printf("Added New Book ID %d with Popularity %d\n", id, score);
                }
                else {
                    int least = 0;
                    for (int i = 1; i < capacity; i++) {
                        if (shelf[i].lastAccess < shelf[least].lastAccess)
                            least = i;
                    }

                    printf("Shelf Full! Removing Least Recently Accessed Book ID %d\n",
                           shelf[least].id);

                    shelf[least].id = id;
                    shelf[least].popularity = score;
                    shelf[least].lastAccess = timer;

                    printf("Added New Book ID %d with Popularity %d\n", id, score);
                }
            }
        }

        else if (strcmp(op, "ACCESS") == 0) {
            int id;
            scanf("%d", &id);
            timer++;

            int found = -1;

            for (int i = 0; i < capacity; i++) {
                if (shelf[i].used && shelf[i].id == id) {
                    found = i;
                    break;
                }
            }

            if (found == -1) {
                printf("ACCESS %d   -1 (Book Not Found)\n", id);
            } 
            else {
                shelf[found].lastAccess = timer;
                printf("ACCESS %d  Popularity = %d\n", id, shelf[found].popularity);
            }
        }
    }
    return 0;
}