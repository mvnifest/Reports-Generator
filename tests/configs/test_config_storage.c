#include <assert.h>
#include <stdio.h>
#include "input/configs/config_storage.h"
#include "test_config_storage.h"

int run_test_config_storage() {
    int success = 1;
    clearScheduleConfigs();

    ScheduleConfig cfg1 = { .scheduleId = 1, .requiredHours = 160 };
    ScheduleConfig cfg2 = { .scheduleId = 2, .requiredHours = 120 };

    addScheduleConfig(cfg1);
    addScheduleConfig(cfg2);

    if (getRequiredHours(1) != 160) success = 0;
    if (getRequiredHours(2) != 120) success = 0;
    if (getRequiredHours(3) != -1) success = 0;

    clearScheduleConfigs();
    if (getScheduleCount() != 0) success = 0;

    printf("[test_config_storage] %s\n", success ? "OK" : "FAILED");
    return success;
}
