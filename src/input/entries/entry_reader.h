/**
 * Plik: entry_reader.h
 * Autor: Konrad Biały
 *
 * Opis:
 * Zawiera deklarację funkcji readWorkEntries() odpowiedzialnej za
 * wczytywanie danych z plików RCP_*.txt.
 */

#ifndef ENTRY_READER_H
#define ENTRY_READER_H

typedef struct {
    int userId;
    char date[11];
    char entryTime[9];
    char exitTime[9];
    double hoursWorked;
} WorkEntry;

void readWorkEntries();
double calculateHoursWorked(const Entry* entry);


#endif