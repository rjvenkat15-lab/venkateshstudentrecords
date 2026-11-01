#include "student.h"

static int comes_before(const Student *left, const Student *right, int choice)
{
    if (choice == 1) {
        return left->id < right->id;
    }
    if (choice == 2) {
        return strcmp(left->name, right->name) < 0;
    }
    return left->mark < right->mark;
}

void sort_student_records(Student **head)
{
    Student *sorted = NULL;
    Student *current;
    int choice;
    int result;

    if (*head == NULL) {
        printf("No records to sort.\n");
        return;
    }

    printf("\nSort by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("3. Percentage\n");
    result = read_int("Choose an option: ", &choice);
    if (result <= 0) {
        return;
    }
    if (choice < 1 || choice > 3) {
        printf("Choose 1 for ID, 2 for name, or 3 for percentage.\n");
        return;
    }

    current = *head;
    while (current != NULL) {
        Student *next = current->next;
        Student **position = &sorted;

        while (*position != NULL && !comes_before(current, *position, choice)) {
            position = &(*position)->next;
        }
        current->next = *position;
        *position = current;
        current = next;
    }
    *head = sorted;

    if (choice == 1) {
        printf("List sorted by ID. Use option 7 to save the new order.\n");
    } else if (choice == 2) {
        printf("List sorted by name. Use option 7 to save the new order.\n");
    } else {
        printf("List sorted by percentage. Use option 7 to save the new order.\n");
    }
    display_students(*head);
}
