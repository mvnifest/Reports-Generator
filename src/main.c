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
#include "include/structs.h"
#include "entry_reader.h"



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
        printf("1. Wyświetl wszystkich użytkowników\n");
        printf("2. Wczytaj dane wejściowe ponownie\n");
        printf("3. Oblicz i pokaż podsumowanie pracy\n");
        printf("4. Wygeneruj raporty\n");
        printf("0. Wyjście\n");
        printf("Wybór: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Wyświetlanie wszystkich użytkowników:\n");
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
                printf("Wygenerowanie raportów:\n");
                generateReports();
                break;
            case 0:
                saveUsers();
                printf("Zamykam program...\n");
                break;
            default:
                printf("Nieprawidłowy wybór.\n");
        }
    } while (choice != 0);

    return 0;
}
