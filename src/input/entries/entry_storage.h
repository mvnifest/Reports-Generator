/**
 * Plik: entry_storage.h
 * Autor: Konrad Biały
 *
 * Opis:
 * Zawiera deklaracje funkcji do zarządzania tablicą Entry w pamięci:
 * dodawanie, dostęp do wpisów, liczba wpisów i czyszczenie danych.
 */

#ifndef ENTRY_STORAGE_H
#define ENTRY_STORAGE_H

#include "../../include/structs.h"

void addEntry(Entry entry);
Entry getEntry(int index);
int getEntryCount();
void clearEntries();

#endif
