#ifndef DATABASE_H
#define DATABASE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "student.h"

#define MAX_NAME_LENGTH 50
#define INITIAL_CAPACITY 50
#define MAX_FILENAME_LENGTH 256
#define DEFAULT_FILENAME "database.txt"

typedef struct {
    Student* students;
    int size;
    int capacity;
    int next_id;
    char current_filename[MAX_FILENAME_LENGTH];
} Database;

void db_init(Database* db);
void db_add_student(Database* db);
void delete_student(Database* db);
void search_student(Database* db);
void edit_student(Database* db);
void sort_database(Database* db);
void save_to_file(Database* db);
void save_as(Database* db);
void load_from_file(Database* db);
void load_from_named_file(const char* filename, Database* db);
void free_database(Database* db);
#endif