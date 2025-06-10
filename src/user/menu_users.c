#include "user/user_db.h"
#include "structs.h"
#include <stdio.h>

void displayUserMenu() {
    printf("\n=== MENU UZYTKOWNIKOW ===\n");
    printf("1. Dodaj uzytkownika\n");
    printf("2. Edytuj harmonogram\n");
    printf("3. Usun użytkownika\n");
    printf("4. Wyswietl wszystkich\n");
    printf("0. Powrot\n");
    printf("Wybierz opcje: ");
}

void showAllUsers() {
    int count;
    User* users = getAllUsers(&count);
    printf("\nID\tImię\t	Nazwisko\t	Harmonogram\n");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%-16s%-16s", users[i].id, users[i].name, users[i].surname);
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
        
        switch (choice) {
            case 1:
                printf("Podaj ID, imię, nazwisko i harmonogram (1-3): ");
                scanf("%d %31s %31s %d", &user.id, user.name, user.surname, &user.schedule);
                status = addUser(user);
                if (status == ADD_SUCCESS) printf("Dodano!\n");
                else if (status == ADD_DUPLICATE) printf("ID juz istnieje!\n");
                else printf("Blad dodawania!\n");
                break;

            case 2:
                printf("Podaj ID: ");
                scanf("%d", &id);
                do {
                    printf("Podaj nowy harmonogram (1-3): \n"
                        "1: 7-14\n"
                        "2: 14-22\n"
                        "3: Nienormowany (nadgodziny)\n");
                    scanf("%d", &schedule);
                    if (schedule < 1 || schedule > 3) {
                        printf("Bledny harmonogram! Dozwolone wartosci: 1, 2 lub 3.\n\n");
                    }
                } while (schedule < 1 || schedule > 3);
                status = editUser(id, schedule);
                if (status == EDIT_SUCCESS) printf("Zaktualizowano!\n");
                else printf("Nie znaleziono uzytkownika!\n");
                break;

            case 3:
                printf("Podaj ID do usuniccia: ");
                scanf("%d", &id);
                status = deleteUser(id);
                if (status == DELETE_SUCCESS) printf("Usunieto!\n");
                else printf("Nie znaleziono uzytkownika!\n");
                break;

            case 4:
                showAllUsers();
                break;
        }

    } while (choice != 0);
}