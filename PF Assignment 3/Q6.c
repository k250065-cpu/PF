#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int studentID;
    char fullName[100];
    char batch[20];
    char membershipType[10];
    char regDate[11];
    char dob[11];
    char interest[10];
} Student;

Student *database = NULL;
int count = 0;
int capacity = 0;

void checkAlloc(void *ptr) {
    if (!ptr) {
        printf("Memory Allocation Failed\n");
        exit(1);
    }
}

void loadDatabase(const char *filename) {
    FILE *fp = fopen(filename, "rb");

    if (!fp) {
        printf("No Existing Database Found\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    count = size / sizeof(Student);
    capacity = count > 0 ? count : 1;

    database = malloc(capacity * sizeof(Student));
    checkAlloc(database);

    fread(database, sizeof(Student), count, fp);
    fclose(fp);

    printf("%d Records Loaded from %s.\n", count, filename);
}

void saveDatabase(const char *filename) {
    FILE *fp = fopen(filename, "wb");

    if (!fp) {
        printf("Error: Could Not Save Database\n");
        return;
    }

    fwrite(database, sizeof(Student), count, fp);
    fclose(fp);

    printf("Database Saved\n");
}

int idExists(int id) {
    for (int i = 0; i < count; i++)
        if (database[i].studentID == id)
            return 1;
    return 0;
}

void addStudent() {
    Student s;

    printf("Enter Student ID: ");
    scanf("%d", &s.studentID);

    if (idExists(s.studentID)) {
        printf("Error: Student ID already exists\n");
        return;
    }

    printf("Enter Full Name: ");
    getchar();
    fgets(s.fullName, 100, stdin);
    s.fullName[strcspn(s.fullName, "\n")] = '\0';

    printf("Enter Batch (CS/SE/Cyber Security/AI): ");
    scanf("%s", s.batch);

    printf("Membership Type (IEEE/ACM): ");
    scanf("%s", s.membershipType);

    printf("Registration Date (YYYY-MM-DD): ");
    scanf("%s", s.regDate);

    printf("Date of Birth (YYYY-MM-DD): ");
    scanf("%s", s.dob);

    printf("Interested In (IEEE/ACM/Both): ");
    scanf("%s", s.interest);

    if (count == capacity) {
        capacity = capacity == 0 ? 2 : capacity * 2;
        database = realloc(database, capacity * sizeof(Student));
        checkAlloc(database);
    }

    database[count++] = s;

    printf("Student Added\n");
}

void updateStudent() {
    int id;
    printf("Enter Student ID to Update: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (database[i].studentID == id) {

            printf("Update Batch: ");
            scanf("%s", database[i].batch);

            printf("Update Membership Type (IEEE/ACM): ");
            scanf("%s", database[i].membershipType);

            printf("Record Updated\n");
            return;
        }
    }
    printf("Student Not Found\n");
}

void deleteStudent() {
    int id;
    printf("Enter Student ID to Delete: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (database[i].studentID == id) {
            for (int j = i; j < count - 1; j++)
                database[j] = database[j + 1];

            count--;
            printf("Student Deleted\n");
            return;
        }
    }
    printf("Student Not Found\n");
}

void displayAll() {
    printf("\n--- All Registered Students ---\n");
    for (int i = 0; i < count; i++) {
        printf("\nID: %d\nName: %s\nBatch: %s\nMembership: %s\nReg Date: %s\nDOB: %s\nInterest: %s\n",
               database[i].studentID,
               database[i].fullName,
               database[i].batch,
               database[i].membershipType,
               database[i].regDate,
               database[i].dob,
               database[i].interest);
    }
    printf("-------------------------------\n");
}

void batchReport() {
    char batch[20], interest[10];
    printf("Enter Batch (CS/SE/Cyber Security/AI): ");
    scanf("%s", batch);
    printf("Interested In (IEEE/ACM/Both): ");
    scanf("%s", interest);

    printf("\n--- Batch Wise Report ---\n");
    for (int i = 0; i < count; i++) {
        if (strcmp(database[i].batch, batch) == 0 &&
            strcmp(database[i].interest, interest) == 0) {

            printf("ID: %d | Name: %s | Membership: %s\n",
                   database[i].studentID,
                   database[i].fullName,
                   database[i].membershipType);
        }
    }
    printf("---------------------------\n");
}

int main() {
    loadDatabase("members.dat");

    int choice;

    while (1) {
        printf("\n===== IEEE/ACM Membership Manager =====\n");
        printf("1. Register New Student\n");
        printf("2. Update Student Record\n");
        printf("3. Delete Student\n");
        printf("4. View All Students\n");
        printf("5. Generate Batch-wise Report\n");
        printf("6. Save & Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: updateStudent(); break;
            case 3: deleteStudent(); break;
            case 4: displayAll(); break;
            case 5: batchReport(); break;
            case 6:
                saveDatabase("members.dat");
                printf("Goodbye\n");
                free(database);
                return 0;
            default:
                printf("Invalid Choice\n");
        }
    }
}