#ifndef INTERFACE_H
#define INTERFACE_H
#include <stdio.h>
#include "database.h"
#define DEFAULT_FILENAME "database.txt"
#define MAX_FILENAME_LENGTH 256


void print_menu(Database* db);
void print_database(Database* db);

#endif