#include <stdio.h>
#include "book.h"
#include "ui.h"

int main() {
    const char *filename = "bookdb.dat";
    int menu = 0;

    while (menu != 6) {
        menu = Banner();
        switch (menu) {
            case 1:
                addBook(filename);
                break;
            case 2:
                viewBook(filename);
                break;
            case 3:
                viewBookById(filename);
                break;
            case 4:
                updateBook(filename);
                break;
            case 5:
                deleteBook(filename);
                break;
            case 6:
                printf("Bye!\n");
                break;
            default:
                // Banner already handles invalid input feedback in this refactor
                break;
        }
    }

    return 0;
}
