/**
 * Plik: absence_reader.c
 * Autor: Konrad Biały
 *
 * Opis:
 * Przegląda folder "RCP_IN/" i wczytuje dane z plików Absence_*.txt.
 * Każda linia reprezentuje nieobecność użytkownika w danym dniu.
 * Dane są dodawane do pamięci poprzez absence_storage.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "structs.h"
#include "input/absences/absence_reader.h"
#include "input/absences/absence_storage.h"

int isAbsenceFile(const char* filename) {
    return strncmp(filename, "Absence_", 8) == 0;
}

void readAbsences() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("RCP_IN");
    if (dir == NULL) {
        perror("Unable to open folder RCP_IN");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (isAbsenceFile(entry->d_name)) {
            char filePath[256];
            snprintf(filePath, sizeof(filePath), "RCP_IN/%s", entry->d_name);

            FILE *file = fopen(filePath, "r");
            if (file == NULL) {
                printf("Unable to open file: %s\n", filePath);
                continue;
            }

            char line[256];
            while (fgets(line, sizeof(line), file)) {
                char* userIdStr = strtok(line, ";");
                char* dateStr = strtok(NULL, ";\n");

                if (!userIdStr || !dateStr) continue;

                Absence absence;
                absence.userId = atoi(userIdStr);
                strncpy(absence.date, dateStr, 10);
                absence.date[10] = '\0';

                addAbsence(absence);
            }

            fclose(file);
        }
    }

    closedir(dir);
}
