/**
 * Plik: work_entry_array.c
 * Autor: Konrad Biały
 *
 * Opis:
 * Zarządza tablicą Entry.
 * Pozwala dodawać nowe wpisy, pobierać je oraz odczytywać ich liczbę.
 * Służy jako bufor danych wejściowych dla dalszych modułów.
 */

#include "work_entry_array.h"

#define MAX_ENTRIES 1000

static Entry allEntries[MAX_ENTRIES];
static int entryCount = 0;

void addEntry(Entry entry) {
    if (entryCount < MAX_ENTRIES) {
        allEntries[entryCount++] = entry;
    }
}

Entry getEntry(int index) {
    if (index >= 0 && index < entryCount) {
        return allEntries[index];
    }

    Entry empty = { .userId = -1 };
    return empty;
}

int getEntryCount() {
    return entryCount;
}

void clearEntries() {
    entryCount = 0;
}
