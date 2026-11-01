#include "student.h"

void insert_student(Student **head)
{
    Student *student;
    Student *current;
    int next_id = 1;
    int result;

    while (find_student_by_id(*head, next_id) != NULL) {
        if (next_id == 2147483647) {
            printf("No available student ID remains.\n");
            return;
        }
        next_id++;
    }

    student = calloc(1, sizeof *student);
    if (student == NULL) {
        perror("Could not allocate student record");
        return;
    }

    student->id = next_id;
    result = read_text("Name: ", student->name, sizeof student->name);
    if (result <= 0) {
        free(student);
        return;
    }
    result = read_int("Age: ", &student->age);
    if (result <= 0) {
        free(student);
        return;
    }
    if (student->age < 1 || student->age > 120) {
        printf("Age must be between 1 and 120.\n");
        free(student);
        return;
    }
    result = read_int("Mark (1-100): ", &student->mark);
    if (result <= 0) {
        free(student);
        return;
    }
    if (student->mark < 1 || student->mark > 100) {
        printf("Mark must be between 1 and 100.\n");
        free(student);
        return;
    }

    student->next = NULL;
    if (*head == NULL) {
        *head = student;
    } else {
        current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = student;
    }
    printf("Student added with ID %d.\n", student->id);
}
