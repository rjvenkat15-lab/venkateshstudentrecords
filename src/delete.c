#include "student.h"

void delete_student(Student **head)
{
    int id;
    int choice;
    int result;
    Student *current;
    Student *previous = NULL;

    printf("\nDelete by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    result = read_int("Choose an option: ", &choice);
    if (result <= 0) {
        return;
    }
    if (choice != 1 && choice != 2) {
        printf("Invalid choice.\n");
        return;
    }

    if (choice == 1) {
        result = read_int("Student ID to delete: ", &id);
        if (result <= 0) {
            return;
        }
        current = *head;
        while (current != NULL && current->id != id) {
            previous = current;
            current = current->next;
        }
    } else {
        char name[STUDENT_NAME_LENGTH];
        int matches = 0;

        result = read_text("Student name to delete: ", name, sizeof name);
        if (result <= 0) {
            return;
        }
        current = *head;
        printf("\nMatching records:\n");
        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                printf("ID: %d  Name: %s  Age: %d  Mark: %d\n",
                       current->id, current->name, current->age, current->mark);
                matches++;
            }
            current = current->next;
        }
        if (matches == 0) {
            printf("Name not found.\n");
            return;
        }

        result = read_int("ID of record to delete: ", &id);
        if (result <= 0) {
            return;
        }
        current = *head;
        while (current != NULL &&
               (current->id != id || strcmp(current->name, name) != 0)) {
            previous = current;
            current = current->next;
        }
    }

    if (current == NULL) {
        printf("Record not found.\n");
        return;
    }

    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }
    printf("Deleted record ID %d (%s). Use V to save changes.\n",
           current->id, current->name);
    free(current);
}
