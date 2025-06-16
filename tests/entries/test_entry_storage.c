/**
 * Plik: test_entry_storage.c
 * Autor: Konrad Biały
 *
 * Opis:
 * Testuje dodawanie i pobieranie wpisów typu Entry do bufora entry_storage.
 */

#include <stdio.h>
#include <assert.h>
#include "input/entries/entry_storage.h"
#include "test_entry_storage.h"

int run_test_entry_storage() {
    int result = 1;

    clearEntries();

    Entry e1 = { .userId = 1, .date = "2024-06-01", .startTime = "07:00:00", .endTime = "14:00:00" };
    Entry e2 = { .userId = 2, .date = "2024-06-02", .startTime = "14:00:00", .endTime = "22:00:00" };

    addEntry(e1);
    addEntry(e2);

    if (getEntryCount() != 2) result = 0;

    Entry found = getEntry(0);
    if (found.userId != 1) result = 0;

    found = getEntry(1);
    if (found.userId != 2) result = 0;

    clearEntries();
    if (getEntryCount() != 0) result = 0;

    printf("[test_entry_storage] %s\n", result ? "OK" : "FAILED");
    return result;
}
