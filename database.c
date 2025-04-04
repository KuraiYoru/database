#include "database.h"
#include "compare_func.h"


void db_init(Database* db) {
    db->students = malloc(INITIAL_CAPACITY * sizeof(Student));
    db->size = 0;
    db->capacity = INITIAL_CAPACITY;
    db->next_id = 1;
    strcpy(db->current_filename, DEFAULT_FILENAME);
}

void db_add_student(Database* db) {
    if (db->size >= db->capacity) {
        db->capacity = (db->capacity == 0) ? 1 : db->capacity * 2;
        db->students = realloc(db->students, db->capacity * sizeof(Student));
        if (db == NULL) {
            printf("Memory allocation error!\n");
            exit(1);
        }
    }
    
    Student new_student;
    new_student.id = db->next_id++;
    
    printf("Enter student name: ");
    fgets(new_student.name, MAX_NAME_LENGTH, stdin);
    new_student.name[strcspn(new_student.name, "\n")] = '\0';
    
    printf("Enter student age: ");
    scanf("%d", &new_student.age);
    
    printf("Enter student GPA: ");
    scanf("%lf", &new_student.gpa);
    while(getchar() != '\n'); 
    
    db->students[db->size++] = new_student;
    printf("Student added successfully! Assigned ID: %d\n", new_student.id);
}
void delete_student(Database* db) {
    if (db->size == 0) {
        printf("Database is empty.\n");
        return;
    }
    
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);
    while(getchar() != '\n'); 
    
    bool found = false;
    for (int i = 0; i < db->size; i++) {
        if (db->students[i].id == id) {
            found = true;
            for (int j = i; j < db->size - 1; j++) {
                db->students[j] = db->students[j + 1];
            }
            db->size--;
            printf("Student with ID %d deleted.\n", id);
            break;
        }
    }
    
    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }
}

void search_student(Database* db) {
    if (db->size == 0) {
        printf("Database is empty.\n");
        return;
    }
    
    int search_choice;
    printf("Search by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("Enter search option: ");
    scanf("%d", &search_choice);
    while(getchar() != '\n');
    
    if (search_choice == 1) {
        int id;
        printf("Enter student ID: ");
        scanf("%d", &id);
        while(getchar() != '\n');
        
        bool found = false;
        for (int i = 0; i < db->size; i++) {
            if (db->students[i].id == id) {
                printf("\nStudent found:\n");
                printf("ID: %d\n", db->students[i].id );
                printf("Name: %s\n", db->students[i].name );
                printf("Age: %d\n", db->students[i].age );
                printf("GPA: %.2f\n", db->students[i].gpa);
                found = true;
                break;
            }
        }
        
        if (!found) {
            printf("Student with ID %d not found.\n", id);
        }
    }
    else if (search_choice == 2) {
        char name[MAX_NAME_LENGTH];
        printf("Enter student name: ");
        fgets(name, MAX_NAME_LENGTH, stdin);
        name[strcspn(name, "\n")] = '\0';
        
        bool found = false;
        for (int i = 0; i < db->size; i++) {
            if (strcasecmp(db->students[i].name, name) == 0) {
                printf("\nStudent found:\n");
                printf("ID: %d\n", db->students[i].id );
                printf("Name: %s\n", db->students[i].name );
                printf("Age: %d\n", db->students[i].age );
                printf("GPA: %.2f\n", db->students[i].gpa);
                found = true;
                // Don't break to find all matches
            }
        }
        
        if (!found) {
            printf("Student with name '%s' not found.\n", name);
        }
    }
    else {
        printf("Invalid search option.\n");
    }
}

void edit_student(Database* db) {
    if (db->size == 0) {
        printf("Database is empty.\n");
        return;
    }
    
    int id;
    printf("Enter student ID to edit: ");
    scanf("%d", &id);
    while(getchar() != '\n'); // Clear input buffer
    
    bool found = false;
    for (int i = 0; i < db->size; i++) {
        if (db->students[i].id == id) {
            printf("Current data:\n");
            printf("ID: %d\n", db->students[i].id );
                printf("Name: %s\n", db->students[i].name );
                printf("Age: %d\n", db->students[i].age );
                printf("GPA: %.2f\n", db->students[i].gpa);
            
            printf("\nEnter new data:\n");
            printf("New name (current: %s): ", db->students[i].name);
            char name[MAX_NAME_LENGTH];
            fgets(name, MAX_NAME_LENGTH, stdin);
            name[strcspn(name, "\n")] = '\0';
            if (strlen(name) > 0) {
                strcpy(db->students[i].name, name);
            }
            
            printf("New age (current: %d): ", db->students[i].age);
            char age_str[10];
            fgets(age_str, 10, stdin);
            if (strlen(age_str) > 0 && age_str[0] != '\n') {
                db->students[i].age = atoi(age_str);
            }
            
            printf("New GPA (current: %.2f): ", db->students[i].gpa);
            char gpa_str[10];
            fgets(gpa_str, 10, stdin);
            if (strlen(gpa_str) > 0 && gpa_str[0] != '\n') {
                db->students[i].gpa = atof(gpa_str);
            }
            
            printf("Data updated successfully.\n");
            found = true;
            break;
        }
    }
    
    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }
}

void sort_database(Database* db) {
    if (db->size == 0) {
        printf("Database is empty.\n");
        return;
    }
    
    int field_choice, order_choice;
    CompareFunc compare = NULL;
    
    printf("Sort by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("3. Age\n");
    printf("4. GPA\n");
    printf("Enter field to sort by: ");
    scanf("%d", &field_choice);
    
    printf("Sort order:\n");
    printf("1. Ascending\n");
    printf("2. Descending\n");
    printf("Enter sort order: ");
    scanf("%d", &order_choice);
    while(getchar() != '\n'); // Clear input buffer
    
    switch(field_choice) {
        case 1:
            compare = (order_choice == 1) ? compare_id_asc : compare_id_desc;
            break;
        case 2:
            compare = (order_choice == 1) ? compare_name_asc : compare_name_desc;
            break;
        case 3:
            compare = (order_choice == 1) ? compare_age_asc : compare_age_desc;
            break;
        case 4:
            compare = (order_choice == 1) ? compare_gpa_asc : compare_gpa_desc;
            break;
        default:
            printf("Invalid field choice.\n");
            return;
    }
    
    merge_sort(db->students, 0, db->size - 1, compare);
    printf("Database sorted successfully.\n");
}



void save_to_file(Database* db) {
    FILE* file = fopen(db->current_filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    
    for (int i = 0; i < db->size; i++) {
        fprintf(file, "%d,%s,%d,%.2f\n", 
                db->students[i].id,
                db->students[i].name, 
                db->students[i].age, 
                db->students[i].gpa);
    }
    
    fclose(file);
    printf("Database saved to %s (%d records)\n", db->current_filename, db->size);
}

void save_as(Database* db) {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter filename to save as: ");
    fgets(filename, MAX_FILENAME_LENGTH, stdin);
    filename[strcspn(filename, "\n")] = '\0';
    
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    
    for (int i = 0; i < db->size; i++) {
        fprintf(file, "%d,%s,%d,%.2f\n", 
                db->students[i].id,
                db->students[i].name, 
                db->students[i].age, 
                db->students[i].gpa);
    }
    
    fclose(file);
    strcpy(db->current_filename, filename);
    printf("Database saved to %s (%d records)\n", db->current_filename, db->size);
}



void load_from_file(Database* db) {
    FILE* file = fopen(db->current_filename, "r");
    if (file == NULL) {
        printf("File not found. Starting with empty database.\n");
        return;
    }
    
    // Clear current database if any
    free_database(db);
    
    char line[256];
    int max_id = 0;
    
    while (fgets(line, sizeof(line), file)) {
        // Skip empty lines or lines with only whitespace
        if (strspn(line, " \t\n\r") == strlen(line)) {
            continue;
        }
        
        Student student;
        char* token;
        
        // Parse ID
        token = strtok(line, ",");
        if (token == NULL) continue;
        student.id = atoi(token);
        
        // Parse Name
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strncpy(student.name, token, MAX_NAME_LENGTH - 1);
        student.name[MAX_NAME_LENGTH - 1] = '\0';
        
        // Parse Age
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        student.age = atoi(token);
        
        // Parse GPA
        token = strtok(NULL, ",\n");
        if (token == NULL) continue;
        student.gpa = atof(token);
        
        // Add to database
        if (db->size >= db->capacity) {
            db->capacity = (db->capacity == 0) ? 1 : db->capacity * 2;
            db->students = realloc(db->students, db->capacity * sizeof(Student));
            if (db == NULL) {
                printf("Memory allocation error!\n");
                exit(1);
            }
        }
        db->students[db->size++] = student;
        
        // Track max ID for next_id
        if (student.id >= max_id) {
            max_id = student.id;
        }
    }
    
    fclose(file);
    db->next_id = max_id + 1;
    printf("Database loaded from %s (%d records)\n", db->current_filename, db->size);
}

void load_from_named_file(const char* filename, Database* db) {
    strncpy(db->current_filename, filename, MAX_FILENAME_LENGTH - 1);
    db->current_filename[MAX_FILENAME_LENGTH - 1] = '\0';
    load_from_file(db);
}

void free_database(Database* db) {
    free(db->students);
    db->students = NULL;
    db->size = 0;
    db->capacity = 0;
    db->next_id = 1;
}