/**
 * Plik: test_entry_parser.c
 * Autor: Konrad Biały
 *
 * Opis:
 * Testuje parsowanie tekstu wejściowego na strukturę Entry.
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "input/entries/entry_parser.h"
#include "test_entry_parser.h"

int run_test_entry_parser() {
    int result = 1;

    const char* line = "3;2024-06-16;08:00:00;16:00:00";
    Entry e;

    e = parseWorkLine(line);

    if (e.userId != 3) result = 0;
    if (strcmp(e.date, "2024-06-16") != 0) result = 0;
    if (strcmp(e.startTime, "08:00:00") != 0) result = 0;
    if (strcmp(e.endTime, "16:00:00") != 0) result = 0;

    printf("[test_entry_parser] %s\n", result ? "OK" : "FAILED");
    return result;
}

