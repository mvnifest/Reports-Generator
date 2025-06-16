#include "user/user_db.h"
#include <stdio.h>
#include <string.h>



void saveUsers() {
    extern User users[];
    extern int userCount;
    FILE *f = fopen("users.dat", "wb");
    if (!f) return;
    fwrite(users, sizeof(User), userCount, f);
    fclose(f);
}
