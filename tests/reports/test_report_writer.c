/**
 * Plik: test_report_writer.c
 * Autor: Konrad Biały
 *
 * Opis:
 * Testuje funkcję getWorkedHours() i logikę kar w zależności od schematu pracy.
 */

#include <stdio.h>
#include <assert.h>
#include "input/entries/entry_storage.h"
#include "input/configs/config_storage.h"
#include "reports/report_writer.h"
#include "test_report_writer.h"
#include "user/user_db.h"

int run_test_report_writer(void) {
    int result = 1;

    clearEntries();
    clearScheduleConfigs();
    clearUsers();
    ScheduleConfig cfg = { .scheduleId = 1, .requiredHours = 160 };
    addScheduleConfig(cfg);

    // Dodaj użytkownika do bazy przed testem
    User u1 = { .id = 1, .name = "Test", .surname = "User", .schedule = 1 };
    addUser(u1);

    Entry e = {
        .userId = 1,
        .date = "2024-06-01",
        .startTime = "07:00:00",
        .endTime = "14:00:00"
    };
    addEntry(e);

    double hours = getWorkedHours(1, 2024, 6, 1, 1); // scheme 1 (7-14)
    if (hours < 6.9 || hours > 7.1) result = 0; // should be 7.0

    // test with late start
    Entry late = {
        .userId = 2,
        .date = "2024-06-02",
        .startTime = "07:10:00",
        .endTime = "14:00:00"
    };
    addEntry(late);

    // Dodaj drugiego użytkownika do bazy przed testem
    User u2 = { .id = 2, .name = "Late", .surname = "Guy", .schedule = 1 };
    addUser(u2);

    hours = getWorkedHours(2, 2024, 6, 2, 1);
    if (hours >= 7.0) result = 0; // should have penalty

    clearEntries();
    clearUsers();

    printf("[test_report_writer] %s\n", result ? "OK" : "FAILED");
    return result;
}
