/**
 * Plik: test_absence_reader.c
 * Autor: Konrad Biały
 *
 * Opis:
 * Testuje funkcję readAbsences() poprzez utworzenie pliku testowego w folderze "RCP_IN"
 * i sprawdzenie, czy dane zostały poprawnie zinterpretowane jako nieobecność.
 */

#include <stdio.h>
#include <assert.h>
#include <direct.h>
#include <string.h>
#include "input/absences/absence_storage.h"
#include "input/absences/absence_reader.h"
#include "input/configs/config_reader.h"
#include "test_absence_reader.h"

int run_test_absence_reader() {
    int result = 1;

    const char* folder = "RCP_IN";
    const char* testFile = "RCP_IN/Absence_test.txt";

    // Stwórz folder jeśli nie istnieje
    #ifdef _WIN32
    _mkdir(folder);
    #else
    mkdir(folder, 0777);
    #endif

    FILE* f = fopen(testFile, "w");
    if (!f) return 0;

    fprintf(f, "4;2024-06-15\n");
    fclose(f);

    clearAbsences();
    readAbsences();

    if (getAbsenceCount() != 1) result = 0;

    Absence a = getAbsence(0);
    if (a.userId != 4) result = 0;
    if (strcmp(a.date, "2024-06-15") != 0) result = 0;

    // Cleanup
    remove(testFile);

    printf("[test_absence_reader] %s\n", result ? "OK" : "FAILED");
    return result;
}
