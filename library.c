#include <stdio.h>
#include <stdlib.h>

struct Book {
    int id;
    char name[50];
    int issued;   // 0 = not issued, 1 = issued
};

struct Book books[100];
int count = 0;

/* function declarations */
void addBook();
void issueBook();
void returnBook();
void viewBooks();
void saveData();
void loadData();

int main() {
    int choice;
    loadData();

    do {
        printf("\n--- Library Management System ---\n");
        printf("1. Add Book\n");
        printf("2. Issue Book\n");
        printf("3. Return Book\n");
        printf("4. View Books\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addBook(); break;
            case 2: issueBook(); break;
            case 3: returnBook(); break;
            case 4: viewBooks(); break;
            case 5:
                saveData();
                printf("Data saved. Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while(choice != 5);

    return 0;
}

void addBook() {
    printf("Enter Book ID: ");
    scanf("%d", &books[count].id);
    printf("Enter Book Name: ");
    scanf("%s", books[count].name);
    books[count].issued = 0;
    count++;
    printf("Book added successfully\n");
}

void issueBook() {
    int id, i, found = 0;
    printf("Enter Book ID to issue: ");
    scanf("%d", &id);

    for(i = 0; i < count; i++) {
        if(books[i].id == id && books[i].issued == 0) {
            books[i].issued = 1;
            printf("Book issued successfully\n");
            found = 1;
            break;
        }
    }
    if(!found)
        printf("Book not available\n");
}

void returnBook() {
    int id, i, found = 0;
    printf("Enter Book ID to return: ");
    scanf("%d", &id);

    for(i = 0; i < count; i++) {
        if(books[i].id == id && books[i].issued == 1) {
            books[i].issued = 0;
            printf("Book returned successfully\n");
            found = 1;
            break;
        }
    }
    if(!found)
        printf("Invalid Book ID\n");
}

void viewBooks() {
    int i;
    if(count == 0) {
        printf("No books available\n");
        return;
    }
    printf("\nID\tName\tIssued\n");
    for(i = 0; i < count; i++) {
        printf("%d\t%s\t%d\n",
               books[i].id,
               books[i].name,
               books[i].issued);
    }
}

void saveData() {
    FILE *fp = fopen("library.dat", "wb");
    if(fp == NULL) return;
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(books, sizeof(struct Book), count, fp);
    fclose(fp);
}

void loadData() {
    FILE *fp = fopen("library.dat", "rb");
    if(fp == NULL) return;
    fread(&count, sizeof(int), 1, fp);
    fread(books, sizeof(struct Book), count, fp);
    fclose(fp);
}
