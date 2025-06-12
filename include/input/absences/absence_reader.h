/**
 * Plik: absence_reader.h
 * Autor: Konrad Biały
 *
 * Opis:
 * Zawiera deklarację funkcji readAbsenceEntries(), która odczytuje pliki nieobecności.
 */

#ifndef ABSENCE_READER_H
#define ABSENCE_READER_H

#include "input/absences/absence_storage.h"

void readAbsences();
int checkAbsence(int empId, int year, int month, int day);  // ← dodaj to!

#endif