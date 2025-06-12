/**
 * Plik: main.c
 *
 * Opis:
 * Główna funkcja uruchamiająca system przetwarzania danych RCP.
 * Wczytuje dane z plików wejściowych:
 *  - godziny pracy pracowników,
 *  - nieobecności,
 *  - konfigurację zmian.
 * 
 * Dane są ładowane do pamięci przez odpowiednie moduły, a następnie gotowe
 * do dalszego przetwarzania (np. porównań, raportowania, itp.).
 */

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "input/entries/entry_reader.h"
#include "user/user_db.h"
#include "user/user_storage.h"
#include "user/menu_users.h"
#include "reports/report_writer.h"
#include "reports/summary.h"

void loadUsers();               
void saveUsers();
void showAllUsers();

void readConfigFiles();         
void readWorkEntries();
void readAbsences();

void calculateSummary();
void generateReports();
void showMenu();

int main() {
    int choice;

    loadUsers();
    readConfigFiles();
    readWorkEntries();
    readAbsences();

    do {
        printf("SYSTEM RCP\n");
        printf("1. Wyswietl wszystkich uzytkownikow\n");
        printf("2. Wczytaj dane wejsciowe ponownie\n");
        printf("3. Oblicz i pokaz podsumowanie pracy\n");
        printf("4. Wygeneruj raporty\n");
        printf("5. Menu Uzytkownikow\n");
        printf("0. Wyjscie\n");
        printf("Wybor: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Wyswietlanie wszystkich uzytkowników:\n");
                showAllUsers();
                break;
            case 2:
                printf("Wczytanie danych wejściowych ponownie:\n");
                readWorkEntries();
                readAbsences();
                break;
            case 3:
                printf("Obliczenie i pokazanie podsumowania pracy:\n");
                calculateSummary();
                break;
            case 4:
                printf("Wygenerowanie raportow:\n");
                generateReports();
                break;
            case 5:
                handleUserMenu();
                break;
            case 0:
                saveUsers();
                printf("Zamykam program...\n");
                break;
            default:
                printf("Nieprawidlowy wybor.\n");
        }
    } while (choice != 0);

    return 0;
}
