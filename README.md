# C-imple Book Management System

A simple, modular Book Management System written in C. This project allows users to manage a library of books using a terminal-based interface, with data persisted in a binary file.

## Features

- **Add Books**: Register new books with title, author, and ISBN.
- **View All Books**: List all books currently in the system.
- **View Book by ID**: Quickly search for a specific book using its unique ID.
- **Edit Book**: Update details of existing books.
- **Delete Book**: Remove books from the library database.
- **Data Persistence**: All records are saved in `bookdb.dat` for persistent storage.

## Project Structure

The project follows a modular structure to separate concerns and improve maintainability:

```text
.
├── main.c           # Program entry point and main menu loop
├── include/         # Header files (.h) - Interface definitions
│   ├── book.h       # Book data structures and function prototypes
│   └── ui.h         # User Interface function prototypes
├── src/             # Source files (.c) - Implementation details
│   ├── book.c       # Logic for CRUD operations and file handling
│   └── ui.c         # Logic for the terminal interface and menus
├── Makefile         # Build configuration for easy compilation
└── bookdb.dat       # Binary database file (generated automatically)
```

## Prerequisites

- **GCC**: GNU Compiler Collection.
- **Make**: Build automation tool.

## Installation & Build

1. **Clone the repository**:
   ```bash
   git clone <repository-url>
   cd C-imple-Book-Management
   ```

2. **Compile the project**:
   Use the provided `Makefile` to compile the source code:
   ```bash
   make
   ```

3. **Run the application**:
   ```bash
   ./bms
   ```

4. **Clean build files** (optional):
   To remove object files and the executable:
   ```bash
   make clean
   ```

## Usage

When you run the application, you will be presented with a menu:
1. **Add Books**: Follow the prompts to enter book details.
2. **View Book**: Displays all books in a list format.
3. **View Book By Id**: Enter a specific ID to see detailed info.
4. **Edit Book**: Provide an ID to update that book's information.
5. **Delete Book**: Provide an ID to remove a book from the system.
6. **Exit**: Safely close the application.

## Future Improvements

- [ ] Implement search by title or author.
- [ ] Add user authentication.
- [ ] Implement a borrowing/lending system.
- [ ] Upgrade to a SQL-based database for larger datasets.
