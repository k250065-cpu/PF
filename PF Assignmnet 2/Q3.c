#include <stdio.h>

#define ROWS 5
#define COLS 5
#define POWER 0x01     // Bit 0
#define OVERLOAD 0x02 // Bit 1
#define MAINTENANCE 0x04 // Bit 2

void updateStatus(int grid[ROWS][COLS], int row, int col, int flagMask) {
    grid[row][col] |= flagMask;
}

void clearStatus(int grid[ROWS][COLS], int row, int col, int flagMask) {
    grid[row][col] &= ~flagMask;
}

void queryStatus(int grid[ROWS][COLS], int row, int col) {
    printf("Sector (%d, %d) Status:\n", row, col);
    if (grid[row][col] & POWER) {
        printf("  Power Status: ON\n");
    } else {
        printf("  Power Status: OFF\n");
    }

    if (grid[row][col] & OVERLOAD) {
        printf("  Overload Warning: YES\n");
    } else {
        printf("  Overload Warning: NO\n");
    }

    if (grid[row][col] & MAINTENANCE) {
        printf("  Maintenance Required: YES\n");
    } else {
        printf("  Maintenance Required: NO\n");
    }
}

void runDiagnostic(int grid[ROWS][COLS]) {
    int countOL = 0;
    int countM = 0;
    
    printf("System Diagnostic:\n");
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (grid[row][col] & OVERLOAD) {
                countOL++;
            }
            if (grid[row][col] & MAINTENANCE) {
                countM++;
            }
        }
    }

    printf("Total Overloaded Sectors: %d\n", countOL);
    printf("Total Sectors Requiring Maintenance: %d\n", countM);
}

int main() {
    int grid[ROWS][COLS] = {0};

    int choice, row, col;

    do {
        printf("\nPower Grid Monitoring System Menu\n");
        printf("1. Update Sector Status\n");
        printf("2. Query Sector Status\n");
        printf("3. Run System Diagnostic\n");
        printf("4. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Row and Column (0 to 4): ");
                scanf("%d %d", &row, &col);

                printf("Select Flag to Update (1 = Power , 2 = Overload, 3 = Maintenance): ");
                int flag;
                scanf("%d", &flag);

                if (flag == 1) {
                    updateStatus(grid, row, col, POWER);
                } else if (flag == 2) {
                    updateStatus(grid, row, col, OVERLOAD);
                } else if (flag == 3) {
                    updateStatus(grid, row, col, MAINTENANCE);
                } else {
                    printf("Invalid flag.\n");
                }
                break;

            case 2:
                printf("Enter Row and Column to Query (0 to 4): ");
                scanf("%d %d", &row, &col);
                queryStatus(grid, row, col);
                break;

            case 3:
                runDiagnostic(grid);
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid Choice.\n");
        }
    } while (choice != 4);

    return 0;
}