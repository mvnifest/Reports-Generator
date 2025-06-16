/**
 * Plik: test_absence_storage.c
 * Autor: Konrad Biały
 *
 * Opis:
 * Testuje dodawanie i pobieranie nieobecności za pomocą absence_storage.
 */

#include <stdio.h>
#include <assert.h>
#include "input/absences/absence_storage.h"
#include "test_absence_storage.h"

int run_test_absence_storage() {
    int result = 1;

    clearAbsences();

    Absence a1 = { .userId = 1, .date = "2024-06-01" };
    Absence a2 = { .userId = 2, .date = "2024-06-02" };

    addAbsence(a1);
    addAbsence(a2);

    if (getAbsenceCount() != 2) result = 0;

    Absence found = getAbsence(1);
    if (found.userId != 2) result = 0;

    clearAbsences();
    if (getAbsenceCount() != 0) result = 0;

    printf("[test_absence_storage] %s\n", result ? "OK" : "FAILED");
    return result;
}
