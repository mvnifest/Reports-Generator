/**
 * Plik: test_user_storage.c
 * Autor: Konrad Biały
 *
 * Opis:
 * Testuje zapis i odczyt użytkowników do/z pliku testowego przez user_storage.
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "user/user_storage.h"
#include "user/user_db.h"
#include "test_user_storage.h"

int run_test_user_storage() {
    int result = 1;

    // Usuń plik users.txt przed testem, jeśli istnieje
    remove("users.txt");

    clearUsers();

    User u1 = { .id = 10, .name = "Test", .surname = "User", .schedule = 1 };
    User u2 = { .id = 11, .name = "Guest", .surname = "Example", .schedule = 2 };

    addUser(u1);
    addUser(u2);

    saveUsersToFile();
    clearUsers();
    loadUsersFromFile();

    User* found1 = getUserById(10);
    User* found2 = getUserById(11);
    User* notFound = getUserById(99);

    if (!found1 || strcmp(found1->name, "Test") != 0) result = 0;
    if (!found2 || strcmp(found2->surname, "Example") != 0) result = 0;
    if (notFound != NULL) result = 0;

    // Cleanup
    clearUsers();
    remove("users.txt"); // Usuń plik po teście

    printf("[test_user_storage] %s\n", result ? "OK" : "FAILED");
    return result;
}
