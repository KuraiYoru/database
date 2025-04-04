#include "interface.h"


void print_menu() {
    printf("\n=== Student Database Menu ===\n");
    printf("Current file: %s\n", current_filename);
    printf("1. Add student\n");
    printf("2. Delete student\n");
    printf("3. Search student\n");
    printf("4. Edit student\n");
    printf("5. Sort database\n");
    printf("6. View database\n");
    printf("7. Save to current file\n");
    printf("8. Save as...\n");
    printf("9. Load from file...\n");
    printf("10. Exit\n");
}

void print_database() {
    if (size == 0) {
        printf("Database is empty.\n");
        return;
    }
    
    printf("\n=== Student Database (%d records) ===\n", size);
    printf("%-6s %-20s %-6s %-6s\n", "ID", "Name", "Age", "GPA");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < size; i++) {
        printf("%-6d %-20s %-6d %-6.2f\n", 
               database[i].id,
               database[i].name, 
               database[i].age, 
               database[i].gpa);
    }
}