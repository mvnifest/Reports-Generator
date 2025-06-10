#ifndef ENTRY_READER_H
#define ENTRY_READER_H

#include "input/entries/entry_storage.h"

void readWorkEntries();
void readAbsences();
Entry* getEntryForDay(int empId, int year, int month, int day);  // ← dodaj to!

#endif
