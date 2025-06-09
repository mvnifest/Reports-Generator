/**
 * Plik: entry_reader.c
 * Autor: Konrad Biały
 *
 * Opis:
 * Przegląda folder "RCP_IN/" i wczytuje dane z plików RCP_*.txt.
 * Każda linia jest parsowana do struktury Entry.
 * Wpisy są dodawane do globalnej tablicy Entry za pomocą work_entry_array.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include "input/entries/entry_reader.h"
#include "input/entries/entry_parser.h"
#include "input/entries/entry_storage.h"
#include "input/entries/work_entry_array.h"


int isRCPFile(const char* filename) {
    return strncmp(filename, "RCP_", 4) == 0;
};

double calculateHoursWorked(const Entry* entry) {
    struct tm startTm = {0}, endTm = {0};

    sscanf(entry->startTime, "%2d:%2d:%2d", &startTm.tm_hour, &startTm.tm_min, &startTm.tm_sec);
    sscanf(entry->endTime,   "%2d:%2d:%2d", &endTm.tm_hour, &endTm.tm_min, &endTm.tm_sec);

    startTm.tm_year = endTm.tm_year = 123;
    startTm.tm_mon = endTm.tm_mon = 0;
    startTm.tm_mday = endTm.tm_mday = 1;

    time_t t1 = mktime(&startTm);
    time_t t2 = mktime(&endTm);

    double seconds = difftime(t2, t1);
    return seconds / 3600.0;
}

void readWorkEntries() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("RCP_IN");
    if (dir == NULL) {
        perror("Unable to open folder RCP_IN");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (isRCPFile(entry->d_name)) {
            char filePath[256];
            snprintf(filePath, sizeof(filePath), "RCP_IN/%s", entry->d_name);

            FILE *file = fopen(filePath, "r");
            if (file == NULL) {
                printf("Unable to open file: %s\n", filePath);
                continue;
            }

            printf("\n>> file: %s\n", entry->d_name);

            char line[256];
            while (fgets(line, sizeof(line), file)) {
                Entry entry = parseWorkLine(line);

                if (entry.userId != -1) {
                    addEntry(entry);
                }
            }

            fclose(file);
        }
    }
}
