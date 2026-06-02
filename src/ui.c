#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Banner() {
    char chooseMenu[10];
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
    
    if (fgets(chooseMenu, sizeof(chooseMenu), stdin) == NULL) {
        return 0;
    }
    
    // Remove newline if present
    chooseMenu[strcspn(chooseMenu, "\n")] = 0;
    
    if (strlen(chooseMenu) == 0) {
        return 0;
    }

    int chooseMenuInt = atoi(chooseMenu);
    if ((chooseMenuInt < 1) || (chooseMenuInt > 6)) {
        printf("Choose 1 - 6!\n");
        return 0;
    }
    return chooseMenuInt;
}
