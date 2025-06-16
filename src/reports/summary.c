#include <stdio.h>
#include "reports/summary.h"
#include "user/user_db.h"
#include "input/entries/entry_storage.h"
#include "input/configs/config_storage.h"
#include "input/absences/absence_storage.h"

void calculateSummary() {
    extern User users[];
    extern int userCount;

    // Załóżmy, że masz funkcje:
    // - getConfigHoursForMonth(int year, int month, int scheduleId)
    // - getEntryCount(), getEntry(int idx)
    // - getAbsenceCount(), getAbsence(int idx)

    // Ustal bieżący miesiąc i rok (możesz to rozwinąć na wybór z menu)
    int year = 2024;
    int month = 6;

    printf("\nPODSUMOWANIE PRACY (%04d-%02d):\n", year, month);
    printf("ID\tImie\t\tNazwisko\tSchemat\tWymagane\tPrzepracowane\tNieobecnosci\n");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; ++i) {
        User* u = &users[i];
        int required = getConfigHoursForMonth(year, month, u->schedule);
        double worked = 0.0;
        int absences = 0;

        // Sumuj godziny pracy z wpisów Entry
        int entryCount = getEntryCount();
        for (int j = 0; j < entryCount; ++j) {
            Entry e = getEntry(j);
            if (e.userId == u->id) {
                // Sprawdź czy wpis jest z danego miesiąca i roku
                int eYear, eMonth, eDay;
                sscanf(e.date, "%4d-%2d-%2d", &eYear, &eMonth, &eDay);
                if (eYear == year && eMonth == month) {
                    int sh, sm, ss, eh, em, es;
                    sscanf(e.startTime, "%2d:%2d:%2d", &sh, &sm, &ss);
                    sscanf(e.endTime, "%2d:%2d:%2d", &eh, &em, &es);
                    int startSec = sh*3600 + sm*60 + ss;
                    int endSec = eh*3600 + em*60 + es;
                    double hours = (endSec - startSec) / 3600.0;
                    if (hours > 0) worked += hours;
                }
            }
        }

        // Policz nieobecności w danym miesiącu
        int absenceCount = getAbsenceCount();
        for (int j = 0; j < absenceCount; ++j) {
            Absence a = getAbsence(j);
            int aYear, aMonth, aDay;
            sscanf(a.date, "%4d-%2d-%2d", &aYear, &aMonth, &aDay);
            if (a.userId == u->id && aYear == year && aMonth == month) {
                absences++;
            }
        }

        printf("%d\t%-10s\t%-12s\t%d\t%d\t\t%.2f\t\t%d\n",
            u->id, u->name, u->surname, u->schedule, required, worked, absences);
    }
    printf("\n");
}