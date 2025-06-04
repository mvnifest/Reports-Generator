#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    int id;
    int schedule; // 1 - zmiana 1, 2 - zmiana 2, 3 - nocna
} User;

typedef struct {
    int userId;
    char date[11];     // yyyy-mm-dd
    char startTime[9]; // hh:mm:ss
    char endTime[9];   // hh:mm:ss
} Entry;

typedef struct {
    int userId;
    char date[11];     // yyyy-mm-dd
} Absence;

typedef struct {
    int scheduleId;
    int requiredHours;
} ScheduleConfig;


#endif
