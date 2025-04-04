#ifndef DATABASE_H
#define DATABASE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "student.h"
#define MAX_NAME_LENGTH 50
#define MAX_FILENAME_LENGTH 256
#define DEFAULT_FILENAME "database.txt"


void add_student();
void delete_student();
void search_student();
void edit_student();

void sort_database();

void save_to_file();
void save_as();
void load_from_file();
void load_from_named_file(const char* filename);
void free_database();
#endif