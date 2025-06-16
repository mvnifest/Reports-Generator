/**
 * Plik: test_entry_reader.c
 * Autor: Konrad Biały
 *
 * Opis:
 * Testuje funkcję readWorkEntries() przez stworzenie pliku w katalogu tymczasowym
 * i sprawdzenie, czy dane zostały poprawnie wczytane do pamięci.
 */

#include <stdio.h>
#include <assert.h>
#include <direct.h>
#include <string.h>
#include "input/entries/entry_storage.h"
#include "input/entries/entry_reader.h"
#include "input/configs/config_reader.h"
#include "test_entry_reader.h"

int run_test_entry_reader() {
    int result = 1;

    const char* folder = "RCP_IN";
    const char* testFile = "RCP_IN/RCP_test_entry.txt";

    // Stwórz folder jeśli nie istnieje
    #ifdef _WIN32
    _mkdir(folder);
    #else
    mkdir(folder, 0777);
    #endif

    FILE* f = fopen(testFile, "w");
    if (!f) return 0;

    fprintf(f, "5;2024-06-17;07:00:00;14:00:00\n");
    fclose(f);

    clearEntries();
    readWorkEntries();

    if (getEntryCount() != 1) result = 0;

    Entry e = getEntry(0);
    if (e.userId != 5) result = 0;
    if (strcmp(e.date, "2024-06-17") != 0) result = 0;

    // Cleanup
    remove(testFile);

    printf("[test_entry_reader] %s\n", result ? "OK" : "FAILED");
    return result;
}
