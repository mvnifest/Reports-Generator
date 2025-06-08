#ifndef MENU_USERS_H
#define MENU_USERS_H

#include "user_db.h"


void display_user_menu();


void print_user_header();


void print_user_details(User user);

void add_user_ui();


void edit_user_ui();


void delete_user_ui();


void list_all_users();


void search_user_ui();


int handle_user_menu();

#endif // MENU_USERS_H