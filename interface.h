#ifndef INTERFACE_H
#define INTERFACE_H
#include <stdio.h>
#include "database.h"
#define DEFAULT_FILENAME "database.txt"
#define MAX_FILENAME_LENGTH 256

extern Student* database;
extern int size;
extern int capacity;
extern int next_id;
extern char current_filename[MAX_FILENAME_LENGTH];
void print_menu();
void print_database();

#endif