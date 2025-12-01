#include <stdio.h>
#include <string.h>

#define MAX_EMPLOYEES 10

struct Employee {
    int id;
    char name[50];
    char designation[50];
    float salary;
};

void inputEmployeeData(struct Employee employees[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter Details for Employee %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &employees[i].id);
        getchar();
        printf("Name: ");
        fgets(employees[i].name, 50, stdin);
        employees[i].name[strcspn(employees[i].name, "\n")] = '\0';
        printf("Designation: ");
        fgets(employees[i].designation, 50, stdin);
        employees[i].designation[strcspn(employees[i].designation, "\n")] = '\0';
        printf("Salary: ");
        scanf("%f", &employees[i].salary);
    }
}

void displayEmployees(struct Employee employees[], int n) {
    printf("\nEmployee ID\tName\t\tDesignation\tSalary\n");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%s\t\t%s\t\t%.2f\n", employees[i].id, employees[i].name, employees[i].designation, employees[i].salary);
    }
}

void findHighestSalary(struct Employee employees[], int n) {
    int highestIndex = 0;
    for (int i = 1; i < n; i++) {
        if (employees[i].salary > employees[highestIndex].salary) {
            highestIndex = i;
        }
    }
    printf("\nEmployee with Highest Salary:\n");
    printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
           employees[highestIndex].id, employees[highestIndex].name,
           employees[highestIndex].designation, employees[highestIndex].salary);
}

void searchEmployeeID(struct Employee employees[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (employees[i].id == id) {
            printf("\nEmployee Found by ID:\n");
            printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                   employees[i].id, employees[i].name,
                   employees[i].designation, employees[i].salary);
            return;
        }
    }
    printf("Employee with ID %d Not Found\n", id);
}

void searchEmployeeName(struct Employee employees[], int n, char name[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(employees[i].name, name) == 0) {
            printf("\nEmployee Found by Name:\n");
            printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                   employees[i].id, employees[i].name,
                   employees[i].designation, employees[i].salary);
            return;
        }
    }
    printf("Employee with Name '%s' Not Found\n", name);
}

void applyBonus(struct Employee employees[], int n, float threshold) {
    for (int i = 0; i < n; i++) {
        if (employees[i].salary < threshold) {
            employees[i].salary += employees[i].salary * 0.10;
        }
    }
}

int main() {
    int n;

    printf("Enter the Number of Employees: ");
    scanf("%d", &n);

    struct Employee employees[MAX_EMPLOYEES];
    
    inputEmployeeData(employees, n);

    displayEmployees(employees, n);

    findHighestSalary(employees, n);

    int searchID;
    printf("\nEnter ID to Search: ");
    scanf("%d", &searchID);
    searchEmployeeID(employees, n, searchID);

    char searchName[50];
    printf("\nEnter Name to Search: ");
    getchar();
    fgets(searchName, 50, stdin);
    searchName[strcspn(searchName, "\n")] = '\0';
    searchEmployeeName(employees, n, searchName);

    float threshold = 50000.0;
    applyBonus(employees, n, threshold);
    printf("\nUpdated Salary Details after Applying Bonus:\n");
    displayEmployees(employees, n);

    return 0;
}