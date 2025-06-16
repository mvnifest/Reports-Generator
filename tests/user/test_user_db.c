#include <stdio.h>
#include <assert.h>
#include "user/user_db.h"
#include "test_user_db.h"



int run_test_user_db() {
    int result = 1;

    clearUsers();

    User u1 = { .id = 1, .name = "Alice", .surname = "Smith", .schedule = 1 };
    User u2 = { .id = 2, .name = "Bob", .surname = "Johnson", .schedule = 2 };

    addUser(u1);
    addUser(u2);

    User* found1 = getUserById(1);
    User* found2 = getUserById(2);
    User* missing = getUserById(3);

    if (!found1 || found1->schedule != 1) result = 0;
    if (!found2 || found2->schedule != 2) result = 0;
    if (missing != NULL) result = 0;

    clearUsers();
    if (getUserById(1) != NULL) result = 0;

    printf("[test_user_db] %s\n", result ? "OK" : "FAILED");
    return result;
}
