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

    char buffer[256];
    strncpy(buffer, line, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char *userIdStr, *entryStr, *exitStr;
    userIdStr = strtok(buffer, ";");
    entryStr  = strtok(NULL, ";");
    exitStr   = strtok(NULL, ";");

    if (!userIdStr || !entryStr || !exitStr) {
        entry.userId = -1; 
        return entry;
    }

    if (exitStr[strlen(exitStr) - 1] == '\n')
        exitStr[strlen(exitStr) - 1] = '\0';

    entry.userId = atoi(userIdStr);

    strncpy(entry.date, entryStr, 10);
    entry.date[10] = '\0';

    strncpy(entry.startTime, entryStr + 11, 8);
    entry.startTime[8] = '\0';

    strncpy(entry.endTime, exitStr + 11, 8);
    entry.endTime[8] = '\0';

    return entry;
}
