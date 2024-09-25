#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct BooksStruct {
  int id;
  char title[200];
  char author[200];
  char isbnNumber[50];
  int availability;
};

int Banner(){
  char chooseMenu[2];
  printf("[]================================[]\n");
  printf("|| Welcome To Book Management App ||\n");
  printf("[]================================[]\n");
  printf("[>] Menus: \n");
  printf("1. Add Books\n");
  printf("2. View Book\n");
  printf("3. View Book By Id\n");
  printf("4. Edit Book\n");
  printf("5. Delete Book\n");
  printf("6. Exit\n");
  printf("You Choose (Enter Number): ");
  fgets(chooseMenu, 2, stdin);
  if(strlen(chooseMenu) > 2){
    printf("Only input 1 digit");
    return 0;
  }
  int chooseMenuInt = atoi(chooseMenu); 
  if((chooseMenuInt < 0) || (chooseMenuInt > 6)){
    printf("Choose 1 - 6!");
    return 0;
  }
  return chooseMenuInt;
}

int getNextId(char *filename){
  FILE *file = fopen(filename, "rb");
  int highestIndex = 0;

  if(!file){
    printf("File not found, starting from index 1\n");
    return 1;
  }
  struct BooksStruct book; 
  // loop through all books to find highest id;
  while(fread(&book,sizeof(book), 1, file)) {
  if(highestIndex < book.id){
      highestIndex = book.id;
    }
  }
  fclose(file);
  return highestIndex + 1;
}

void addBook(char *filename){
  struct BooksStruct book;
  // open file to input book 
  FILE *file = fopen(filename, "ab"); // open file in append mode for binary
  getchar(); 
  printf("Enter title: ");
  fgets(book.title, 199, stdin);
  book.title[strcspn(book.title, "\n")] = 0; 
 
  printf("Enter author: ");
  fgets(book.author, 199, stdin);
  book.author[strcspn(book.author, "\n")] = 0;
 

  printf("Enter ISBN Number: ");
  fgets(book.isbnNumber, 49, stdin);
  book.isbnNumber[strcspn(book.isbnNumber, "\n")] = 0;

  printf("Is the book available? (1 for yes 0 for no): ");
  scanf("%d", &book.availability);
  getchar();

  book.id = getNextId(filename);

  fwrite(&book, sizeof(book), 1, file);
  fclose(file);

  printf("Book %s with author %s successfully added in with id %d!\n", book.title, book.author, book.id);
}

void viewBook(char *filename){
  struct BooksStruct book;
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    printf("No book found");
    return;
  }
  getchar();
  printf("[*]=================================================[*]\n");
  printf("[*]Library Books: \n");
  while (fread(&book, sizeof(book), 1, file)) {
    printf("[ID]: %d\n", book.id);
    printf("Title: %s\n", book.title);
    printf("Author: %s\n", book.author);
    printf("ISBN: %s\n", book.isbnNumber);
    printf("Available: %s\n", book.availability ? "Yes" : "No"); 
  }
  printf("[*]=================================================[*]\n");

  fclose(file);
}

void viewBookById(char *filename){
  struct BooksStruct book;
  FILE *file = fopen(filename, "rb");
  int bookId;
  int bookFound = 0; 
  printf("Insert Book Id: ");
  scanf("%d", &bookId);
  getchar();
  while (fread(&book, sizeof(book), 1, file)) {
    if(book.id == bookId){
      printf("[*] Book Found!\n");
      printf("ID: %d\n", book.id);
      printf("Title: %s\n", book.title);
      printf("Author: %s\n", book.author);
      printf("ISBN: %s\n", book.isbnNumber);
      printf("Available: %s\n", book.availability ? "Yes" : "No");
      bookFound = 1;
    }
  }
  if(!bookFound){
    printf("[x] Book not found\n");
  }
  fclose(file);
}

void updateBook(char *filename){
  struct BooksStruct book;
  FILE *file = fopen(filename, "rb+");
  int bookId;
  int bookFound = 0;
  printf("[*] Updating Book\n");
  printf("Insert Book Id: ");
  scanf("%d", &bookId);
  getchar();
  while (fread(&book, sizeof(book), 1, file)) {
    if(book.id == bookId){
      printf("[*] Book Found!\n");
      printf("ID: %d\n", book.id);
      printf("Title: %s\n", book.title);
      printf("Author: %s\n", book.author);
      printf("ISBN: %s\n", book.isbnNumber);
      printf("Available: %s\n", book.availability ? "Yes" : "No");

      printf("Enter new title: ");
      fgets(book.title, 199, stdin);
      book.title[strcspn(book.title, "\n")] = 0; 
 
      printf("Enter new author: ");
      fgets(book.author, 199, stdin);
      book.author[strcspn(book.author, "\n")] = 0;
 
      printf("Enter new ISBN Number: ");
      fgets(book.isbnNumber, 49, stdin);
      book.isbnNumber[strcspn(book.isbnNumber, "\n")] = 0;

      printf("Is the book available? (1 for yes 0 for no): ");
      scanf("%d", &book.availability);
      getchar();
  
      // Move the file pointer to the beginning of the current book's record
      fseek(file, -sizeof(book), SEEK_CUR);
      fwrite(&book, sizeof(book), 1, file);
 
      bookFound = 1;
      break;
    }
  }
  if(!bookFound){
    printf("[x] Book not found\n");
  }  
  fclose(file); 
}

void deleteBook(char *filename){
  struct BooksStruct book;
  FILE *file = fopen(filename, "rb+");
  int bookId;
  int answer;
  int bookFound = 0;
  printf("[-] Deleting Book: . . . \n");
  printf("Enter Book ID: ");
  scanf("%d",&bookId);
  getchar();

  while(fread(&book, sizeof(book), 1, file)){
    if(book.id == bookId){
      printf("[*] Book Found!\n");
      printf("ID: %d\n", book.id);
      printf("Title: %s\n", book.title);
      printf("Author: %s\n", book.author);
      printf("ISBN: %s\n", book.isbnNumber);
      printf("Available: %s\n", book.availability ? "Yes" : "No");
      bookFound = 1;
      printf("[?] Are you sure to delete this book? (1: yes or 2: no): "); 
      scanf("%d", &answer);
      getchar();

      if(answer){
        fseek(file, -sizeof(book), SEEK_CUR);
        fwrite(&book, sizeof(book), 1, file);
        printf("[*] Book successfully deleted!\n");
        break;
      } else {
        printf("Book Deletion Has Been Canceled!\n");
        break;
      }
    }
  }
  if(!bookFound){
    printf("[x] Book not found!\n");
  }
  fclose(file);
}

int main(){
  char filename[20] = "bookdb.dat";
  int exitLoop = 1;
  int menu = 0;
  while ((menu!=6) && (exitLoop != 0)) {
    int menu = Banner();
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
        exitLoop = 0;
      break;
      default:
        printf("Choose between 1 - 6!\n");
      break;
    } 
  } 

  return 0;
}
