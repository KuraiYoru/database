#include "database.h"
#include "compare_func.h"

Student* database = NULL;
int size = 0;
int capacity = 0;
int next_id = 1;
char current_filename[MAX_FILENAME_LENGTH] = DEFAULT_FILENAME;

void add_student() {
    if (size >= capacity) {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        database = realloc(database, capacity * sizeof(Student));
        if (database == NULL) {
            printf("Memory allocation error!\n");
            exit(1);
        }
    }
    
    Student new_student;
    new_student.id = next_id++;
    
    printf("Enter student name: ");
    fgets(new_student.name, MAX_NAME_LENGTH, stdin);
    new_student.name[strcspn(new_student.name, "\n")] = '\0';
    
    printf("Enter student age: ");
    scanf("%d", &new_student.age);
    
    printf("Enter student GPA: ");
    scanf("%lf", &new_student.gpa);
    while(getchar() != '\n'); 
    
    database[size++] = new_student;
    printf("Student added successfully! Assigned ID: %d\n", new_student.id);
}

void delete_student() {
    if (size == 0) {
        printf("Database is empty.\n");
        return;
    }
    
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);
    while(getchar() != '\n'); 
    
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (database[i].id == id) {
            found = true;
            for (int j = i; j < size - 1; j++) {
                database[j] = database[j + 1];
            }
            size--;
            printf("Student with ID %d deleted.\n", id);
            break;
        }
    }
    
    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }
}

void search_student() {
    if (size == 0) {
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
        for (int i = 0; i < size; i++) {
            if (database[i].id == id) {
                printf("\nStudent found:\n");
                printf("ID: %d\n", database[i].id);
                printf("Name: %s\n", database[i].name);
                printf("Age: %d\n", database[i].age);
                printf("GPA: %.2f\n", database[i].gpa);
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
        for (int i = 0; i < size; i++) {
            if (strcasecmp(database[i].name, name) == 0) {
                printf("\nStudent found:\n");
                printf("ID: %d\n", database[i].id);
                printf("Name: %s\n", database[i].name);
                printf("Age: %d\n", database[i].age);
                printf("GPA: %.2f\n", database[i].gpa);
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

void edit_student() {
    if (size == 0) {
        printf("Database is empty.\n");
        return;
    }
    
    int id;
    printf("Enter student ID to edit: ");
    scanf("%d", &id);
    while(getchar() != '\n'); // Clear input buffer
    
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (database[i].id == id) {
            printf("Current data:\n");
            printf("ID: %d (cannot be changed)\n", database[i].id);
            printf("Name: %s\n", database[i].name);
            printf("Age: %d\n", database[i].age);
            printf("GPA: %.2f\n", database[i].gpa);
            
            printf("\nEnter new data:\n");
            printf("New name (current: %s): ", database[i].name);
            char name[MAX_NAME_LENGTH];
            fgets(name, MAX_NAME_LENGTH, stdin);
            name[strcspn(name, "\n")] = '\0';
            if (strlen(name) > 0) {
                strcpy(database[i].name, name);
            }
            
            printf("New age (current: %d): ", database[i].age);
            char age_str[10];
            fgets(age_str, 10, stdin);
            if (strlen(age_str) > 0 && age_str[0] != '\n') {
                database[i].age = atoi(age_str);
            }
            
            printf("New GPA (current: %.2f): ", database[i].gpa);
            char gpa_str[10];
            fgets(gpa_str, 10, stdin);
            if (strlen(gpa_str) > 0 && gpa_str[0] != '\n') {
                database[i].gpa = atof(gpa_str);
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

void sort_database() {
    if (size == 0) {
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
    
    merge_sort(database, 0, size - 1, compare);
    printf("Database sorted successfully.\n");
}



void save_to_file() {
    FILE* file = fopen(current_filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d,%s,%d,%.2f\n", 
                database[i].id,
                database[i].name, 
                database[i].age, 
                database[i].gpa);
    }
    
    fclose(file);
    printf("Database saved to %s (%d records)\n", current_filename, size);
}

void save_as() {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter filename to save as: ");
    fgets(filename, MAX_FILENAME_LENGTH, stdin);
    filename[strcspn(filename, "\n")] = '\0';
    
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d,%s,%d,%.2f\n", 
                database[i].id,
                database[i].name, 
                database[i].age, 
                database[i].gpa);
    }
    
    fclose(file);
    strcpy(current_filename, filename);
    printf("Database saved to %s (%d records)\n", current_filename, size);
}



void load_from_file() {
    FILE* file = fopen(current_filename, "r");
    if (file == NULL) {
        printf("File not found. Starting with empty database.\n");
        return;
    }
    
    // Clear current database if any
    free_database();
    
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
        if (size >= capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            database = realloc(database, capacity * sizeof(Student));
            if (database == NULL) {
                printf("Memory allocation error!\n");
                exit(1);
            }
        }
        database[size++] = student;
        
        // Track max ID for next_id
        if (student.id >= max_id) {
            max_id = student.id;
        }
    }
    
    fclose(file);
    next_id = max_id + 1;
    printf("Database loaded from %s (%d records)\n", current_filename, size);
}

void load_from_named_file(const char* filename) {
    strncpy(current_filename, filename, MAX_FILENAME_LENGTH - 1);
    current_filename[MAX_FILENAME_LENGTH - 1] = '\0';
    load_from_file();
}

void free_database() {
    free(database);
    database = NULL;
    size = 0;
    capacity = 0;
    next_id = 1;
}