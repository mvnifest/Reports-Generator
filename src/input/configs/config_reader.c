/**
 * Plik: config_reader.c
 * Autor: Konrad Biały
 *
 * Opis:
 * Przegląda folder "RCP_Config/" i wczytuje dane konfiguracyjne ze zmianami.
 * Każdy plik zawiera pary scheduleId;wymaganeGodziny.
 * Dane są dodawane do pamięci poprzez config_storage.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "structs.h"
#include "input/configs/config_reader.h"
#include "input/configs/config_storage.h"

int isConfigFile(const char* filename) {
    return strstr(filename, ".txt") != NULL;
}

void readConfigFiles() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("RCP_Config");
    if (dir == NULL) {
        perror("Unable to open folder RCP_Config");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (isConfigFile(entry->d_name)) {
            char filePath[256];
            snprintf(filePath, sizeof(filePath), "RCP_Config/%s", entry->d_name);

            FILE *file = fopen(filePath, "r");
            if (file == NULL) {
                printf("Unable to open config file: %s\n", filePath);
                continue;
            }

            char line[128];
            while (fgets(line, sizeof(line), file)) {
                char* idStr = strtok(line, ";");
                char* hoursStr = strtok(NULL, ";\n");

                if (!idStr || !hoursStr) continue;

                ScheduleConfig config;
                config.scheduleId = atoi(idStr);
                config.requiredHours = atoi(hoursStr);

                addScheduleConfig(config);
            }

            fclose(file);
        }
    }

    closedir(dir);
}
