/**
 * Plik: test_runner.c
 * Autor: Konrad Biały
 *
 * Opis:
 * Uruchamia wszystkie testy jednostkowe projektu.
 */

#include <stdio.h>

// Configs
#include "configs/test_config_storage.h"
#include "configs/test_config_reader.h"

// Entries
#include "entries/test_entry_storage.h"
#include "entries/test_entry_parser.h"
#include "entries/test_entry_reader.h"

// Absences
#include "absences/test_absence_storage.h"
#include "absences/test_absence_reader.h"

// User
#include "user/test_user_db.h"
#include "user/test_user_storage.h"

// Reports
#include "reports/test_report_writer.h"

int main() {
    int passed = 0, total = 0;

    // === Configs ===
    total++; if (run_test_config_storage()) passed++;
    total++; if (run_test_config_reader()) passed++;

    // === Entries ===
    total++; if (run_test_entry_storage()) passed++;
    total++; if (run_test_entry_parser()) passed++;
    total++; if (run_test_entry_reader()) passed++;

    // === Absences ===
    total++; if (run_test_absence_storage()) passed++;
    total++; if (run_test_absence_reader()) passed++;

    // === User ===
    total++; if (run_test_user_db()) passed++;
    total++; if (run_test_user_storage()) passed++;

    // === Reports ===
    total++; if (run_test_report_writer()) passed++;

    printf("\n[Summary] Passed %d / %d tests\n", passed, total);
    return passed == total ? 0 : 1;
}

#ifdef _WIN32
int WinMain(void* hInst, void* hPrev, char* lpCmdLine, int nCmdShow) {
    (void)hInst; (void)hPrev; (void)lpCmdLine; (void)nCmdShow;
    return main();
}
#endif
