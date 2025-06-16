/**
 * Plik: test_config_reader.c
 * Autor: Konrad Biały
 *
 * Opis:
 * Testuje funkcję readConfigFiles() przez zapisanie testowego pliku do katalogu "RCP_Config"
 * i sprawdzenie, czy zmiana została poprawnie wczytana do pamięci.
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <direct.h>
#include "input/configs/config_storage.h"
#include "input/configs/config_reader.h"
#include "test_config_reader.h"

int run_test_config_reader() {
    int result = 1;

    const char* folder = "RCP_Config";
    const char* testFile = "RCP_Config/Config_test.txt";

    // Stwórz folder jeśli nie istnieje
    #ifdef _WIN32
    _mkdir(folder);
    #else
    mkdir(folder, 0777);
    #endif

    FILE* f = fopen(testFile, "w");
    if (!f) return 0;

    fprintf(f, "3;144\n");
    fclose(f);

    clearScheduleConfigs();
    readConfigFiles();

    int hours = getRequiredHours(3);
    if (hours != 144) result = 0;

    // Cleanup
    remove(testFile);

    printf("[test_config_reader] %s\n", result ? "OK" : "FAILED");
    return result;
}
