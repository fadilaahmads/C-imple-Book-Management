#ifndef BOOK_H
#define BOOK_H

#define MAX_TITLE 200
#define MAX_AUTHOR 200
#define MAX_ISBN 50

typedef struct {
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    char isbnNumber[MAX_ISBN];
    int availability;
} Book;

int getNextId(const char *filename);
void addBook(const char *filename);
void viewBook(const char *filename);
void viewBookById(const char *filename);
void updateBook(const char *filename);
void deleteBook(const char *filename);

#endif // BOOK_H
