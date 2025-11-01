#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char toggleBits(char c) {
    unsigned char mask_2nd = 1 << 1;
    unsigned char mask_5th = 1 << 4;

    c ^= mask_2nd;
    c ^= mask_5th;

    return c;
}

void reverseString(char* str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }
}

void encodeMessage(char message[]) {
    int length = strlen(message);

    reverseString(message);

    for (int i = 0; i < length; i++) {
        message[i] = toggleBits(message[i]);
    }

    printf("Encoded Message: %s\n", message);
}

void decodeMessage(char message[]) {
    int length = strlen(message);

    for (int i = 0; i < length; i++) {
        message[i] = toggleBits(message[i]);
    }

    reverseString(message);

    printf("Decoded Message: %s\n", message);
}

int main() {
    char message[256];
    int choice;

    do {
        printf("\n--- TCS Message Encoding/Decoding ---\n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter Message to Encode: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0';
                encodeMessage(message);
                break;

            case 2:
                decodeMessage(message);
                break;

            case 3:
                printf("Exiting the Program.\n");
                break;
            default:
                printf("Invalid Choice!\n");
        }
    } while (choice != 3);

    return 0;
}