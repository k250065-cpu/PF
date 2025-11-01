#include <stdio.h>
#include <string.h>

#define PRODUCTS 100
#define CART_ITEMS 50

struct Product {
    int code;
    int quantity;
    float price;
};

struct CartItem {
    int code;
    int quantity;
};

struct Product inventory[PRODUCTS] = {
    {101, 50, 100.0},
    {102, 10, 200.0},
    {103, 20, 300.0},
    {104, 8, 150.0}
};

struct CartItem cart[CART_ITEMS];
int cartCount = 0;

char customerName[50];
char customerCNIC[20];

void getCustomerInfo() {
    printf("\nEnter Customer Name: ");
    getchar();
    fgets(customerName, sizeof(customerName), stdin);
    customerName[strcspn(customerName, "\n")] = 0;

    printf("Enter Customer CNIC: ");
    fgets(customerCNIC, sizeof(customerCNIC), stdin);
    customerCNIC[strcspn(customerCNIC, "\n")] = 0;

    printf("\nCustomer Information Saved.\n");
}

void displayInventory() {
    printf("\nProduct Code\tQuantity in Stock\tPrice per Product\n");
    printf("--------------------------------------------------\n");
    for(int i = 0; i < 4; i++) {
        printf("%d\t\t%d\t\t\t%.2f\n", inventory[i].code, inventory[i].quantity, inventory[i].price);
    }
}

int findProduct(int code) {
    for(int i = 0; i < 4; i++) {
        if(inventory[i].code == code)
            return i;
    }
    return -1;
}

void updateInventory() {
    int code, updatedQuantity;
    printf("\nEnter Product Code to Update: ");
    scanf("%d", &code);

    int index = findProduct(code);
    if(index == -1) {
        printf("Product Not Found.\n");
        return;
    }

    printf("Enter New Quantity: ");
    scanf("%d", &updatedQuantity);
    inventory[index].quantity = updatedQuantity;

    printf("Inventory Updated.\n");
}

void addToCart() {
    int code, quantity;
    printf("\nEnter Product Code to Add: ");
    scanf("%d", &code);

    int index = findProduct(code);
    if(index == -1) {
        printf("Product Not Found.\n");
        return;
    }

    printf("Enter Quantity: ");
    scanf("%d", &quantity);

    if(quantity > inventory[index].quantity) {
        printf("Error: Not Enough Stock.\n");
        return;
    }

    inventory[index].quantity -= quantity;
    cart[cartCount].code = code;
    cart[cartCount].quantity = quantity;
    cartCount++;

    printf("Item Added to Cart.\n");
}

void displayTotalBill() {
    float total = 0;
    for(int i = 0; i < cartCount; i++) {
        int index = findProduct(cart[i].code);
        total += inventory[index].price * cart[i].quantity;
    }

    printf("\nTotal Bill (without discount): Rs. %.2f\n", total);

    char promoCode[20];
    printf("Do You Have a Promo Code ? (Enter 'Eid2025' for 25%% off or 'No'): ");
    scanf("%s", promoCode);

    if(strcmp(promoCode, "Eid2025") == 0) {
        float discount = total * 0.25;
        printf("Discount Applied: Rs. %.2f\n", discount);
        printf("Total Bill (with discount): Rs. %.2f\n", total - discount);
    } else {
        printf("No Discount.\n");
    }
}

void showInvoice() {
    float total = 0;
    printf("\n----------- INVOICE -----------\n");
    printf("Customer Name: %s\n", customerName);
    printf("CNIC: %s\n", customerCNIC);
    printf("\nProduct Code\tQuantity\tPrice\n");

    for(int i = 0; i < cartCount; i++) {
        int index = findProduct(cart[i].code);
        float itemTotal = inventory[index].price * cart[i].quantity;
        printf("%d\t\t%d\t\t%.2f\n", cart[i].code, cart[i].quantity, itemTotal);
        total += itemTotal;
    }

    printf("\nTotal Bill: Rs. %.2f\n", total);
    printf("--------------------------------\n");
}

int main() {
    int choice;

    do {
        printf("\n------ SUPERMARKET MANAGEMENT SYSTEM ------\n");
        printf("1. Enter Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Update Inventory\n");
        printf("4. Add Item to Cart\n");
        printf("5. Display Total Bill\n");
        printf("6. Show Invoice\n");
        printf("7. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                getCustomerInfo();
                break;
            case 2:
                displayInventory();
                break;
            case 3:
                updateInventory();
                break;
            case 4:
                addToCart();
                break;
            case 5:
                displayTotalBill();
                break;
            case 6:
                showInvoice();
                break;
            case 7:
                printf("Exiting The System.\n");
                break;
            default:
                printf("Invalid Choice. Try Again.\n");
        }
    } while(choice != 7);

    return 0;
}