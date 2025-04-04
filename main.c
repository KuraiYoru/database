#include "student.h"
#include "database.h"
#include "interface.h"

#define MAX_NAME_LENGTH 50
#define MAX_FILENAME_LENGTH 256
#define DEFAULT_FILENAME "database.txt"

int main() {
    Database db;
    db_init(&db);

    load_from_file(&db);
    
    int choice;
    do {
        print_menu(&db);
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while(getchar() != '\n'); 
        
        switch(choice) {
            case 1: db_add_student(&db); break;
            case 2: delete_student(&db); break;
            case 3: search_student(&db); break;
            case 4: edit_student(&db); break;
            case 5: sort_database(&db); break;
            case 6: print_database(&db); break;
            case 7: save_to_file(&db); break;
            case 8: save_as(&db); break;
            case 9: {
                printf("Enter filename to load: ");
                char filename[MAX_FILENAME_LENGTH];
                fgets(filename, MAX_FILENAME_LENGTH, stdin);
                filename[strcspn(filename, "\n")] = '\0';
                load_from_named_file(filename, &db);
                break;
            }
            case 10: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 10);
    
    free_database(&db);
    return 0;
}