#ifndef REPORT_WRITER_H
#define REPORT_WRITER_H

#include "user/user_db.h"

// Deklaracje funkcji z report_writer.c
User* getUserById(int empId);
int getRequiredHoursForMonth(int year, int month, int workScheme);
int getDaysInMonth(int year, int month);
int isAbsence(int empId, int year, int month, int day);
double getWorkedHours(int empId, int year, int month, int day, int workScheme);
void generateReportForEmployee(int year, int month, int empId);

#endif
