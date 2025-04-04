#include "student.h"
#include "database.h"
#include "interface.h"

#define MAX_NAME_LENGTH 50
#define MAX_FILENAME_LENGTH 256
#define DEFAULT_FILENAME "database.txt"


int main(int argc, char* argv[]) {
    if (argc > 1) {
        strncpy(current_filename, argv[1], MAX_FILENAME_LENGTH - 1);
        current_filename[MAX_FILENAME_LENGTH - 1] = '\0';
    }
    
    load_from_file();
    
    int choice;
    do {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while(getchar() != '\n'); 
        
        switch(choice) {
            case 1: add_student(); break;
            case 2: delete_student(); break;
            case 3: search_student(); break;
            case 4: edit_student(); break;
            case 5: sort_database(); break;
            case 6: print_database(); break;
            case 7: save_to_file(); break;
            case 8: save_as(); break;
            case 9: {
                printf("Enter filename to load: ");
                char filename[MAX_FILENAME_LENGTH];
                fgets(filename, MAX_FILENAME_LENGTH, stdin);
                filename[strcspn(filename, "\n")] = '\0';
                load_from_named_file(filename);
                break;
            }
            case 10: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 10);
    
    free_database();
    return 0;
}
