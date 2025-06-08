
#include "user_db.h"
#include "structs.h"
#include <stdio.h>

void displayUserMenu() {
    printf("\n=== MENU UŻYTKOWNIKÓW ===\n");
    printf("1. Dodaj użytkownika\n");
    printf("2. Edytuj harmonogram\n");
    printf("3. Usuń użytkownika\n");
    printf("4. Wyświetl wszystkich\n");
    printf("0. Powrót\n");
    printf("Wybierz opcję: ");
}

void showAllUsers() {
    int count;
    User* users = getAllUsers(&count);
    
    printf("\nID\tHarmonogram\n");
    printf("----------------\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t", users[i].id);
        switch(users[i].schedule) {
            case 1: printf("7-14"); break;
            case 2: printf("14-22"); break;
            case 3: printf("Nienormowany"); break;
            default: printf("Nieznany");
        }
        printf("\n");
    }
}

void handleUserMenu() {
    int choice;
    do {
        displayUserMenu();
        scanf("%d", &choice);
        
        int id, schedule;
        User user;
        UserOperationStatus status;
        
        switch(choice) {
            case 1:
                printf("Podaj ID i harmonogram (1-3): ");
                scanf("%d %d", &user.id, &user.schedule);
                status = addUser(user);
                if (status == ADD_SUCCESS) printf("Dodano!\n");
                else if (status == ADD_DUPLICATE) printf("ID już istnieje!\n");
                else printf("Błąd dodawania!\n");
                break;
                
            case 2:
                printf("Podaj ID i nowy harmonogram: ");
                scanf("%d %d", &id, &schedule);
                status = editUser(id, schedule);
                if (status == EDIT_SUCCESS) printf("Zaktualizowano!\n");
                else printf("Nie znaleziono użytkownika!\n");
                break;
                
            case 3:
                printf("Podaj ID do usunięcia: ");
                scanf("%d", &id);
                status = deleteUser(id);
                if (status == DELETE_SUCCESS) printf("Usunięto!\n");
                else printf("Nie znaleziono użytkownika!\n");
                break;
                
            case 4:
                showAllUsers();
                break;
        }
    } while (choice != 0);
}