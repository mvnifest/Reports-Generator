/**
 * Plik: config_reader.h
 * Autor: Konrad Biały
 *
 * Opis:
 * Zawiera deklarację funkcji readConfigFiles(), która wczytuje konfigurację zmian.
 */

#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include "input/configs/config_storage.h"

void readConfigFiles();
int getConfigHoursForMonth(int year, int month, int workScheme);  // ← to jest potrzebne!

#endif