#include "user/user_db.h"
#include "user/menu_users.h"
#include <stdio.h>
#include <string.h>

User users[MAX_USERS];
int userCount = 0;

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

void loadUsersFromFile() {
    FILE *f = fopen("users.txt", "r");
    if (!f) {
        userCount = 0;
        return;
    }
    userCount = 0;
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        int id, schedule;
        char name[64], surname[64];
        if (sscanf(line, "%d;%63[^;];%63[^;];%d", &id, name, surname, &schedule) == 4) {
            users[userCount].id = id;
            strncpy(users[userCount].name, name, sizeof(users[userCount].name));
            strncpy(users[userCount].surname, surname, sizeof(users[userCount].surname));
            users[userCount].schedule = schedule;
            userCount++;
        }
    }
    fclose(f);
}