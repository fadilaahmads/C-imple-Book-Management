#include "book.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getNextId(const char *filename) {
    FILE *file = fopen(filename, "rb");
    int highestIndex = 0;

    if (!file) {
        return 1;
    }
    Book book;
    while (fread(&book, sizeof(Book), 1, file)) {
        if (highestIndex < book.id) {
            highestIndex = book.id;
        }
    }
    fclose(file);
    return highestIndex + 1;
}

void addBook(const char *filename) {
    Book book;
    FILE *file = fopen(filename, "ab");
    if (!file) {
        perror("Error opening file");
        return;
    }

    printf("Enter title: ");
    fgets(book.title, MAX_TITLE - 1, stdin);
    book.title[strcspn(book.title, "\n")] = 0;

    printf("Enter author: ");
    fgets(book.author, MAX_AUTHOR - 1, stdin);
    book.author[strcspn(book.author, "\n")] = 0;

    printf("Enter ISBN Number: ");
    fgets(book.isbnNumber, MAX_ISBN - 1, stdin);
    book.isbnNumber[strcspn(book.isbnNumber, "\n")] = 0;

    printf("Is the book available? (1 for yes 0 for no): ");
    scanf("%d", &book.availability);
    getchar();

    book.id = getNextId(filename);

    fwrite(&book, sizeof(Book), 1, file);
    fclose(file);

    printf("Book \"%s\" by %s successfully added with id %d!\n", book.title, book.author, book.id);
}

void viewBook(const char *filename) {
    Book book;
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("No books found.\n");
        return;
    }
    printf("[*]=================================================[*]\n");
    printf("[*] Library Books: \n");
    while (fread(&book, sizeof(Book), 1, file)) {
        printf("[ID]: %d\n", book.id);
        printf("Title: %s\n", book.title);
        printf("Author: %s\n", book.author);
        printf("ISBN: %s\n", book.isbnNumber);
        printf("Available: %s\n", book.availability ? "Yes" : "No");
        printf("-------------------------------------------------\n");
    }
    printf("[*]=================================================[*]\n");
    fclose(file);
}

void viewBookById(const char *filename) {
    Book book;
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("No books found.\n");
        return;
    }
    int bookId;
    int bookFound = 0;
    printf("Insert Book Id: ");
    scanf("%d", &bookId);
    getchar();
    while (fread(&book, sizeof(Book), 1, file)) {
        if (book.id == bookId) {
            printf("[*] Book Found!\n");
            printf("ID: %d\n", book.id);
            printf("Title: %s\n", book.title);
            printf("Author: %s\n", book.author);
            printf("ISBN: %s\n", book.isbnNumber);
            printf("Available: %s\n", book.availability ? "Yes" : "No");
            bookFound = 1;
            break;
        }
    }
    if (!bookFound) {
        printf("[x] Book not found\n");
    }
    fclose(file);
}

void updateBook(const char *filename) {
    Book book;
    FILE *file = fopen(filename, "rb+");
    if (!file) {
        printf("No books found.\n");
        return;
    }
    int bookId;
    int bookFound = 0;
    printf("[*] Updating Book\n");
    printf("Insert Book Id: ");
    scanf("%d", &bookId);
    getchar();
    while (fread(&book, sizeof(Book), 1, file)) {
        if (book.id == bookId) {
            printf("[*] Book Found!\n");
            printf("ID: %d\n", book.id);
            printf("Title: %s\n", book.title);
            printf("Author: %s\n", book.author);
            printf("ISBN: %s\n", book.isbnNumber);
            printf("Available: %s\n", book.availability ? "Yes" : "No");

            printf("Enter new title: ");
            fgets(book.title, MAX_TITLE - 1, stdin);
            book.title[strcspn(book.title, "\n")] = 0;

            printf("Enter new author: ");
            fgets(book.author, MAX_AUTHOR - 1, stdin);
            book.author[strcspn(book.author, "\n")] = 0;

            printf("Enter new ISBN Number: ");
            fgets(book.isbnNumber, MAX_ISBN - 1, stdin);
            book.isbnNumber[strcspn(book.isbnNumber, "\n")] = 0;

            printf("Is the book available? (1 for yes 0 for no): ");
            scanf("%d", &book.availability);
            getchar();

            fseek(file, -sizeof(Book), SEEK_CUR);
            fwrite(&book, sizeof(Book), 1, file);

            bookFound = 1;
            printf("[*] Book updated successfully!\n");
            break;
        }
    }
    if (!bookFound) {
        printf("[x] Book not found\n");
    }
    fclose(file);
}

void deleteBook(const char *filename) {
    Book book;
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("No books found.\n");
        return;
    }

    int bookId;
    printf("Enter Book ID to delete: ");
    scanf("%d", &bookId);
    getchar();

    FILE *tempFile = fopen("temp.dat", "wb");
    int bookFound = 0;

    while (fread(&book, sizeof(Book), 1, file)) {
        if (book.id == bookId) {
            bookFound = 1;
            printf("[*] Book Found and will be deleted:\n");
            printf("Title: %s\n", book.title);
            continue; // Skip writing this book to temp file
        }
        fwrite(&book, sizeof(Book), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (bookFound) {
        remove(filename);
        rename("temp.dat", filename);
        printf("[*] Book successfully deleted!\n");
    } else {
        remove("temp.dat");
        printf("[x] Book not found!\n");
    }
}
