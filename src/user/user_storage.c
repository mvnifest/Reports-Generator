#include "user/user_db.h"
#include <stdio.h>
#include <string.h>

void loadUsers() {
    extern User users[];
    extern int userCount;
    FILE *f = fopen("users.dat", "rb");
    if (!f) { userCount = 0; return; }
    userCount = 0;
    while (fread(&users[userCount], sizeof(User), 1, f) == 1) {
        userCount++;
        if (userCount >= MAX_USERS) break;
    }
    fclose(f);
}

void saveUsers() {
    extern User users[];
    extern int userCount;
    FILE *f = fopen("users.dat", "wb");
    if (!f) return;
    fwrite(users, sizeof(User), userCount, f);
    fclose(f);
}
