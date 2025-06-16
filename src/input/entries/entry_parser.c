/**
 * Plik: entry_parser.c
 * Autor: Konrad Biały
 *
 * Opis:
 * Zawiera funkcję parseWorkLine(), która konwertuje pojedynczą linię tekstu
 * na strukturę Entry (userId, data, godzina wejścia/wyjścia).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input/entries/entry_parser.h"
#include "structs.h"

Entry parseWorkLine(const char* line) {
    Entry entry;
    entry.userId = -1; // domyślnie niepoprawny

    char buffer[256];
    strncpy(buffer, line, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char *userIdStr = strtok(buffer, ";");
    char *dateStr = strtok(NULL, ";");
    char *startStr = strtok(NULL, ";");
    char *endStr = strtok(NULL, ";\n");

    if (!userIdStr || !dateStr || !startStr || !endStr) {
        return entry;
    }

    entry.userId = atoi(userIdStr);
    strncpy(entry.date, dateStr, 10);
    entry.date[10] = '\0';
    strncpy(entry.startTime, startStr, 8);
    entry.startTime[8] = '\0';
    strncpy(entry.endTime, endStr, 8);
    entry.endTime[8] = '\0';

    return entry;
}
