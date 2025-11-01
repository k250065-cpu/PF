#include <stdio.h>
#include <string.h>

#define NUM 100
#define LENGTH 50

int isbns[NUM], quantities[NUM];
char titles[NUM][LENGTH];
float prices[NUM];

int findBookISBN(int isbn) {
    for (int i = 0; i < NUM; i++) {
        if (isbns[i] == isbn || isbns[i] == 0) {
            return i;
        }
    }
    return -1;
}  

void addNewBook() {
    int isbn, quantity;
    char title[LENGTH];
    float price;

    printf("\nEnter the ISBN of the Book: ");
    scanf("%d", &isbn);

    int check = findBookISBN(isbn);
    if (check != -1 ) {
        printf("Error: Book with ISBN %d Already Exists.\n", isbn);
        return;
    }

    printf("Enter the Title of the Book: ");
    getchar();
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0; 

    printf("Enter the Price of the Book: ");
    scanf("%f", &price);

    printf("Enter the Quantity of the Book: ");
    scanf("%d", &quantity);

    int index = findBookISBN(0);
    if (index != -1) {
        isbns[index] = isbn;
        strncpy(titles[index], title, LENGTH);
        prices[index] = price;
        quantities[index] = quantity;
        printf("Book Added Successfully.\n");
    } else {
        printf("Error: Library is Full.\n");
    }
}

void processSale() {
    int isbn, copiesSold, index;

    printf("\nEnter the ISBN of the Book: ");
    scanf("%d", &isbn);

    index = findBookISBN(isbn);

    if (index == -1) {
        printf("Error: Book with ISBN %d Not Found.\n", isbn);
        return;
    }

    printf("Enter the Number of Copies Sold: ");
    scanf("%d", &copiesSold);

    if (copiesSold > quantities[index]) {
        printf("Error: Not Enough Stock Available.\n");
    } else {
        quantities[index] -= copiesSold;
        printf("Sale Successful. Updated Stock: %d\n", quantities[index]);
    }
}

void stockReport() {
    printf("\n------ Low-Stock Report ------\n");

    int lowStockCount = 0;

    for (int i = 0; i < NUM; i++) {
        if (quantities[i] > 0 && quantities[i] < 5) {
            printf("ISBN: %d\n", isbns[i]);
            printf("Title: %s\n", titles[i]);
            printf("Price: %.2f\n", prices[i]);
            printf("Quantity: %d\n\n", quantities[i]);
            lowStockCount++;
        }
    }

    if (lowStockCount == 0) {
        printf("No Books with Low Stock (less than 5 copies).\n");
    }
}

int main() {
    int choice;

    for (int i = 0; i < NUM; i++) {
        isbns[i] = 0;
        quantities[i] = 0;
    }

    do {
        printf("\n------ LIBRARY BOOK MANAGEMENT SYSTEM ------\n");
        printf("1. Add New Book\n");
        printf("2. Process a Sale\n");
        printf("3. Generate Low-Stock Report\n");
        printf("4. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addNewBook();
                break;
            case 2:
                processSale();
                break;
            case 3:
                stockReport();
                break;
            case 4:
                printf("Exiting Program.\n");
                break;
            default:
                printf("Invalid Choice. Please Try Again.\n");
        }
    } while (choice != 4);

    return 0;
}