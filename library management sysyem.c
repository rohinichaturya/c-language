#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store book details
struct Book 
{
    int id;
    char title[50];
    char author[50];
    int available; // 1: Available, 0: Issued
};

// Function prototypes
void addBook();
void displayBooks();
void searchBook();
void deleteBook();
void issueBook();
void returnBook();
void saveBook(struct Book);
void loadBooks();

FILE *fp;
struct Book books[100];  // Max 100 books
int bookCount = 0;       // Track number of books

// Main Menu
int main()
{
    int choice;
    loadBooks();

    while (1) 
    {
        printf("\n===== Library Management System =====\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Delete Book\n");
        printf("5. Issue Book\n");
        printf("6. Return Book\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: issueBook(); break;
            case 6: returnBook(); break;
            case 7: 
                printf("Exiting Library System...\n");
                exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Load books from file
void loadBooks() 
{
    fp = fopen("library.dat", "rb");
    if (fp == NULL) return;

    while (fread(&books[bookCount], sizeof(struct Book), 1, fp)) 
    {
        bookCount++;
    }
    fclose(fp);
}

// Save book to file
void saveBook(struct Book book) 
{
    fp = fopen("library.dat", "ab");
    fwrite(&book, sizeof(struct Book), 1, fp);
    fclose(fp);
}

// Add a new book
void addBook()
{
    struct Book book;
    printf("\nEnter Book ID: ");
    scanf("%d", &book.id);
    getchar();
    printf("Enter Book Title: ");
    fgets(book.title, 50, stdin);
    book.title[strcspn(book.title, "\n")] = 0; // Remove newline
    printf("Enter Author Name: ");
    fgets(book.author, 50, stdin);
    book.author[strcspn(book.author, "\n")] = 0;
    book.available = 1;

    books[bookCount++] = book;
    saveBook(book);

    printf("Book Added Successfully!\n");
}

// Display all books
void displayBooks() 
{
    printf("\n===== Book List =====\n");
    for (int i = 0; i < bookCount; i++) 
    {
        printf("ID: %d | Title: %s | Author: %s | %s\n",
               books[i].id, books[i].title, books[i].author,
               books[i].available ? "Available" : "Issued");
    }
}

// Search for a book by ID
void searchBook() 
{
    int id, found = 0;
    printf("\nEnter Book ID to Search: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) 
    {
        if (books[i].id == id) 
        {
            printf("Book Found! Title: %s, Author: %s, Status: %s\n",
                   books[i].title, books[i].author,
                   books[i].available ? "Available" : "Issued");
            found = 1;
            break;
        }
    }
    if (!found) printf("Book not found!\n");
}

// Delete a book
void deleteBook() 
{
    int id, found = 0;
    printf("\nEnter Book ID to Delete: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++)
      {
        if (books[i].id == id) {
            found = 1;
            for (int j = i; j < bookCount - 1; j++) 
            {
                books[j] = books[j + 1];
            }
            bookCount--;
            printf("Book Deleted Successfully!\n");
            break;
        }
    }

    if (!found) printf("Book not found!\n");

    // Save updated data to file
    fp = fopen("library.dat", "wb");
    for (int i = 0; i < bookCount; i++) 
    {
        fwrite(&books[i], sizeof(struct Book), 1, fp);
    }
    fclose(fp);
}

// Issue a book
void issueBook() 
{
    int id, found = 0;
    printf("\nEnter Book ID to Issue: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++)
      {
        if (books[i].id == id && books[i].available == 1) 
        {
            books[i].available = 0;
            found = 1;
            printf("Book Issued Successfully!\n");
            break;
        }
    }

    if (!found) printf("Book not found or already issued!\n");

    // Update file
    fp = fopen("library.dat", "wb");
    for (int i = 0; i < bookCount; i++) 
    {
        fwrite(&books[i], sizeof(struct Book), 1, fp);
    }
    fclose(fp);
}

// Return a book
void returnBook() 
{
    int id, found = 0;
    printf("\nEnter Book ID to Return: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) 
    {
        if (books[i].id == id && books[i].available == 0) 
        {
            books[i].available = 1;
            found = 1;
            printf("Book Returned Successfully!\n");
            break;
        }
    }

    if (!found) printf("Book not found or already returned!\n");

    // Update file
    fp = fopen("library.dat", "wb");
    for (int i = 0; i < bookCount; i++) {
        fwrite(&books[i], sizeof(struct Book), 1, fp);
    }
    fclose(fp);
}
