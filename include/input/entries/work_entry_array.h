/**
 * Plik: work_entry_array.h
 * Autor: Konrad Biały
 *
 * Opis:
 * Zawiera deklaracje funkcji do zarządzania tablicą Entry:
 * dodawanie, pobieranie, liczba elementów, czyszczenie.
 */

#ifndef WORK_ENTRY_ARRAY_H
#define WORK_ENTRY_ARRAY_H

#include "structs.h"

void addEntry(Entry entry);
Entry getEntry(int index);
int getEntryCount();
void clearEntries();

#endif
