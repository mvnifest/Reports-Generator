/**
 * Plik: entry_storage.c
 * Autor: Konrad Biały
 *
 * Opis:
 * Przechowuje dane typu Entry[] zawierające informacje o wejściu i wyjściu pracowników.
 * Umożliwia dodawanie wpisów, pobieranie ich oraz czyszczenie całej tablicy.
 * Może być używany do dalszej analizy (np. w raportach lub podsumowaniach).
 */

#include "input/entries/entry_storage.h"
#include <string.h>
#include <stdio.h>
#include "structs.h"

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

Entry* getEntryForDay(int empId, int year, int month, int day) {
    char targetDate[11];
    snprintf(targetDate, sizeof(targetDate), "%04d-%02d-%02d", year, month, day);

    for (int i = 0; i < entryCount; i++) {
        if (allEntries[i].userId == empId && strncmp(allEntries[i].date, targetDate, 10) == 0) {
            return &allEntries[i];
        }
    }
    return NULL;
}
