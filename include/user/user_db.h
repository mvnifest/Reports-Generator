#ifndef USER_DB_H
#define USER_DB_H

#include "../include/structs.h"

#define MAX_USERS 200
#define USER_DB_FILE "users.dat"

typedef enum {
    ADD_SUCCESS,
    ADD_DUPLICATE,
    ADD_FULL,
    EDIT_SUCCESS,
    EDIT_NOT_FOUND,
    DELETE_SUCCESS,
    DELETE_NOT_FOUND
} UserOperationStatus;

void initUserDB();
UserOperationStatus addUser(User user);
UserOperationStatus editUser(int userId, int newSchedule);
UserOperationStatus deleteUser(int userId);
User* getUser(int userId);
User* getAllUsers(int* count);
int saveUsersToFile();
void loadUsersFromFile();

#endif