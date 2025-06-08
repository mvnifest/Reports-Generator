#include "user_db.h"
#include "menu_users.h"
#include <stdio.h>
#include <string.h>

static User users[MAX_USERS];
static int userCount = 0;

void initUserDB() {
    memset(users, 0, sizeof(users));
    userCount = 0;
    loadUsersFromFile();
}

UserOperationStatus addUser(User user) {
    if (userCount >= MAX_USERS) return ADD_FULL;
    
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == user.id) return ADD_DUPLICATE;
    }
    
    users[userCount++] = user;
    saveUsersToFile();
    return ADD_SUCCESS;
}

UserOperationStatus editUser(int userId, int newSchedule) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == userId) {
            users[i].schedule = newSchedule;
            saveUsersToFile();
            return EDIT_SUCCESS;
        }
    }
    return EDIT_NOT_FOUND;
}

UserOperationStatus deleteUser(int userId) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == userId) {
            memmove(&users[i], &users[i+1], (userCount-i-1)*sizeof(User));
            userCount--;
            saveUsersToFile();
            return DELETE_SUCCESS;
        }
    }
    return DELETE_NOT_FOUND;
}

User* getUser(int userId) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == userId) return &users[i];
    }
    return NULL;
}

User* getAllUsers(int* count) {
    *count = userCount;
    return users;
}

int saveUsersToFile() {
    FILE* file = fopen(USER_DB_FILE, "wb");
    if (!file) return 0;
    
    fwrite(&userCount, sizeof(int), 1, file);
    fwrite(users, sizeof(User), userCount, file);
    
    fclose(file);
    return 1;
}

int loadUsersFromFile() {
    FILE* file = fopen(USER_DB_FILE, "rb");
    if (!file) return 0;
    
    fread(&userCount, sizeof(int), 1, file);
    fread(users, sizeof(User), userCount, file);
    
    fclose(file);
    return 1;
}