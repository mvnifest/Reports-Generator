/**
 * Plik: entry_parser.h
 * Autor: Konrad Biały
 *
 * Opis:
 * Zawiera deklarację funkcji parseWorkLine() do przekształcania linii tekstu na Entry.
 */

#ifndef ENTRY_PARSER_H
#define ENTRY_PARSER_H

#include "../../include/structs.h"

Entry parseWorkLine(const char* line);

#endif
