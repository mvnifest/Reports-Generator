/**
 * Plik: config_storage.c
 * Autor: Konrad Biały
 *
 * Opis:
 * Przechowuje dane konfiguracyjne typu ScheduleConfig[].
 * Umożliwia dodawanie konfiguracji, pobieranie wymaganych godzin dla zmiany,
 * oraz odczyt liczby dostępnych konfiguracji.
 */

#include "config_storage.h"

#define MAX_CONFIGS 100

static ScheduleConfig configs[MAX_CONFIGS];
static int configCount = 0;

void addScheduleConfig(ScheduleConfig config) {
    if (configCount < MAX_CONFIGS) {
        configs[configCount++] = config;
    }
}

int getRequiredHours(int scheduleId) {
    for (int i = 0; i < configCount; i++) {
        if (configs[i].scheduleId == scheduleId) {
            return configs[i].requiredHours;
        }
    }
    return -1; // nie znaleziono
}

int getScheduleCount() {
    return configCount;
}

ScheduleConfig getScheduleConfig(int index) {
    if (index >= 0 && index < configCount) {
        return configs[index];
    }
    ScheduleConfig empty = { .scheduleId = -1 };
    return empty;
}

void clearScheduleConfigs() {
    configCount = 0;
}
