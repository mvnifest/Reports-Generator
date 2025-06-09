/**
 * Plik: absence_storage.h
 * Autor: Konrad Biały
 *
 * Opis:
 * Zawiera deklaracje funkcji do zarządzania nieobecnościami w pamięci.
 */

#ifndef ABSENCE_STORAGE_H
#define ABSENCE_STORAGE_H

#include "structs.h"

void addAbsence(Absence a);
Absence getAbsence(int index);
int getAbsenceCount();
void clearAbsences();

#endif
