/**
 * Plik: config_storage.h
 * Autor: Konrad Biały
 *
 * Opis:
 * Zawiera deklaracje funkcji do przechowywania i odczytu konfiguracji zmian.
 */

#ifndef CONFIG_STORAGE_H
#define CONFIG_STORAGE_H

#include "../../include/structs.h"

void addScheduleConfig(ScheduleConfig config);
int getRequiredHours(int scheduleId);
int getScheduleCount();
ScheduleConfig getScheduleConfig(int index);
void clearScheduleConfigs();

#endif