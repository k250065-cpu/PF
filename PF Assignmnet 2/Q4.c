#include <stdio.h>

#define MAX 5

void push(int stack[], int *top, int maxSize) {
    if (*top == maxSize - 1) {
        printf("Stack Overflow!\n");
    } else {
        int valueToPush;
        printf("Enter Value to Push: ");
        scanf("%d", &valueToPush);
        (*top)++;
        stack[*top] = valueToPush;
        printf("Pushed %d onto the Stack.\n", valueToPush);
    }
}

void pop(int stack[], int *top) {
    if (*top == -1) {
        printf("Stack is Empty!\n");
    } else {
        int valueToPop = stack[*top];
        (*top)--;
        printf("Popped %d from the Stack.\n", valueToPop);
    }
}

void peek(int stack[], int top) {
    if (top == -1) {
        printf("Stack is Empty!\n");
    } else {
        printf("Top Element is: %d\n", stack[top]);
    }
}

void display(int stack[], int top) {
    if (top == -1) {
        printf("Stack is Empty!\n");
    } else {
        printf("Stack Elements (top to bottom):\n");
        for (int i = top; i >= 0; i--) {
            printf("%d\n", stack[i]);
        }
    }
}

int main() {
    int stack[MAX];
    int top = -1;
    int choice;

    do {
        printf("\n===== STACK MENU =====\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. PEEK\n");
        printf("4. DISPLAY\n");
        printf("5. EXIT\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                push(stack, &top, MAX);
                break;
            case 2:
                pop(stack, &top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                printf("Exiting Program...\n");
                break;
            default:
                printf("Invalid Choice!\n");
        }
    } while (choice != 5);

    return 0;
}