#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "reports/report_writer.h"
#include "user/user_db.h"
#include "input/entries/entry_storage.h"
#include "input/absences/absence_storage.h"
#include "input/configs/config_storage.h"
#include "input/configs/config_reader.h"   
#include "input/absences/absence_reader.h"   
#include "input/entries/entry_reader.h"
#include <string.h>

// --- Pomocnicze funkcje do raportowania ---

// Zwraca wskaźnik do użytkownika o danym ID
User* getUserById(int empId) {
    extern User users[];
    extern int userCount;
    for (int i = 0; i < userCount; ++i) {
        if (users[i].id == empId) return &users[i];
    }
    return NULL;
}

// Zwraca liczbę wymaganych godzin w danym miesiącu dla danego schematu pracy
int getRequiredHoursForMonth(int year, int month, int workScheme) {
    // Przykład: odczytaj z config_storage lub zwróć domyślną wartość
    return getConfigHoursForMonth(year, month, workScheme); // zakładamy istnienie tej funkcji
}

// Zwraca liczbę dni w miesiącu
int getDaysInMonth(int year, int month) {
    static const int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int d = days[month-1];
    if (month == 2 && ((year%4==0 && year%100!=0) || (year%400==0))) d = 29;
    return d;
}

// Sprawdza, czy pracownik był nieobecny danego dnia
int isAbsence(int empId, int year, int month, int day) {
    // Przykład: sprawdź w absence_storage
    return checkAbsence(empId, year, month, day); // zakładamy istnienie tej funkcji
}

// Zwraca liczbę przepracowanych godzin danego dnia
// Uwzględnia reguły kar i schemat pracy
// workScheme: 1 - 7-14, 2 - 14-22, 3 - nienormowany
double getWorkedHours(int empId, int year, int month, int day, int workScheme) {
    // Przykład: pobierz wpisy z entry_storage
    Entry* entry = getEntryForDay(empId, year, month, day); // zakładamy istnienie tej funkcji
    if (!entry) return 0.0;
    int startHour, startMin, startSec, endHour, endMin, endSec;
    sscanf(entry->startTime, "%d:%d:%d", &startHour, &startMin, &startSec);
    sscanf(entry->endTime, "%d:%d:%d", &endHour, &endMin, &endSec);
    double hours = (endHour*3600+endMin*60+endSec - (startHour*3600+startMin*60+startSec))/3600.0;
    // Reguły kar
    if (workScheme == 1) { // 7-14
        if (startHour > 6 || (startHour == 6 && startMin > 50)) hours -= 0.25; // kara za spóźnienie
        if (endHour < 14) hours -= 0.25; // kara za wcześniejsze wyjście
    } else if (workScheme == 2) { // 14-22
        if (startHour > 13 || (startHour == 13 && startMin > 50)) hours -= 0.25;
        if (endHour < 22) hours -= 0.25;
    } else if (workScheme == 3) { // nienormowany
        if (hours < 8.0) hours = hours; // po prostu licz rzeczywiste godziny
    }
    if (hours < 0) hours = 0;
    return hours;
}

// Szablon funkcji do generowania raportu dla jednego pracownika
void generateReportForEmployee(int year, int month, int empId) {
    char filename[64];
    snprintf(filename, sizeof(filename), "raport_%d_%02d_%d.txt", year, month, empId);
    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("Błąd: nie można utworzyć pliku %s!\n", filename);
        return;
    }
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char date[32];
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", tm_info);
    fprintf(f, "RAPORT PRACY PRACOWNIKA\nData generowania: %s\n\n", date);
    fprintf(f, "Pracownik: %d\nRok: %d, Miesiąc: %02d\n", empId, year, month);

    // Pobierz dane pracownika
    User* user = getUserById(empId);
    if (!user) {
        fprintf(f, "Brak danych o pracowniku!\n");
        fclose(f);
        printf("Brak danych o pracowniku %d!\n", empId);
        return;
    }
    fprintf(f, "Imię i nazwisko: %s %s\nSchemat pracy: %d\n\n", user->name, user->surname, user->schedule);

    // Pobierz wymagane godziny z configu
    int wymaganeGodziny = getRequiredHoursForMonth(year, month, user->schedule);
    fprintf(f, "Wymagane godziny w miesiącu: %d\n", wymaganeGodziny);

    // Zlicz przepracowane godziny i nieobecności
    double przepracowaneGodziny = 0.0;
    int liczbaNieobecnosci = 0;
    int liczbaDni = getDaysInMonth(year, month);
    for (int dzien = 1; dzien <= liczbaDni; ++dzien) {
        if (isAbsence(empId, year, month, dzien)) {
            liczbaNieobecnosci++;
            przepracowaneGodziny += 8.0; // Za nieobecność licz jak za dzień pracy
            continue;
        }
        double godziny = getWorkedHours(empId, year, month, dzien, user->schedule);
        przepracowaneGodziny += godziny;
    }
    fprintf(f, "Przepracowane godziny: %.2f\n", przepracowaneGodziny);
    fprintf(f, "Nieobecności: %d\n", liczbaNieobecnosci);

    // Nadgodziny/braki
    double nadgodziny = przepracowaneGodziny - wymaganeGodziny;
    if (nadgodziny > 0)
        fprintf(f, "Nadgodziny: %.2f\n", nadgodziny);
    else
        fprintf(f, "Brakujące godziny: %.2f\n", -nadgodziny);

    fclose(f);
    printf("Raport dla pracownika %d został wygenerowany do pliku %s\n", empId, filename);
}

// Menu wyboru raportów
void generateReportsMenu() {
    int wybor;
    printf("\nMENU RAPORTOW:\n");
    printf("1. Raport jednego pracownika\n");
    printf("2. Raport kilku pracowników (podaj zakres)\n");
    printf("3. Raport wszystkich pracownikow\n");
    printf("0. Powrot\n");
    printf("Wybierz opcje: ");
    scanf("%d", &wybor);
    if (wybor == 1) {
        int rok, miesiac, id;
        printf("Podaj rok: "); scanf("%d", &rok);
        printf("Podaj miesiac: "); scanf("%d", &miesiac);
        printf("Podaj nr pracownika: "); scanf("%d", &id);
        generateReportForEmployee(rok, miesiac, id);
    } else if (wybor == 2) {
        int rok, miesiac, id1, id2;
        printf("Podaj rok: "); scanf("%d", &rok);
        printf("Podaj miesiac: "); scanf("%d", &miesiac);
        printf("Podaj zakres nr pracownikow (np. 1 5): "); scanf("%d %d", &id1, &id2);
        for (int i = id1; i <= id2; ++i) generateReportForEmployee(rok, miesiac, i);
    } else if (wybor == 3) {
        int rok, miesiac;
        printf("Podaj rok: "); scanf("%d", &rok);
        printf("Podaj miesiac: "); scanf("%d", &miesiac);
        // TODO: pobierz liczbę pracowników z bazy
        int liczbaPracownikow = 10; // przykładowo
        for (int i = 1; i <= liczbaPracownikow; ++i) generateReportForEmployee(rok, miesiac, i);
    } else {
        printf("Powrot do glownego menu.\n");
    }
}

// Stara funkcja generateReports wywołuje teraz menu
void generateReports() {
    generateReportsMenu();
}
