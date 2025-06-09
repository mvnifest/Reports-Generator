/**
 * Plik: absence_storage.c
 * Autor: Konrad Biały
 *
 * Opis:
 * Przechowuje tablicę Absence[] z informacjami o nieobecnościach.
 * Umożliwia dodawanie, pobieranie oraz czyszczenie wpisów.
 */

 #include "input/absences/absence_storage.h"

#define MAX_ABSENCES 1000

static Absence absences[MAX_ABSENCES];
static int absenceCount = 0;

void addAbsence(Absence a) {
    if (absenceCount < MAX_ABSENCES) {
        absences[absenceCount++] = a;
    }
}

Absence getAbsence(int index) {
    if (index >= 0 && index < absenceCount) {
        return absences[index];
    }

    Absence empty = { .userId = -1 };
    return empty;
}

int getAbsenceCount() {
    return absenceCount;
}

void clearAbsences() {
    absenceCount = 0;
}

// Sprawdza, czy pracownik był nieobecny danego dnia
int checkAbsence(int empId, int year, int month, int day) {
    // TODO: Sprawdź w tablicy nieobecności, na razie zawsze 0
    return 0;
}
