#include "student.h"

void update_student(Student *head)
{
    Student *student;
    int id;
    int field;
    int result;

    result = read_int("Student ID to modify: ", &id);
    if (result <= 0) {
        return;
    }

    student = find_student_by_id(head, id);
    if (student == NULL) {
        printf("Record not found.\n");
        return;
    }

    printf("\nModify Field\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("3. Age\n");
    printf("4. Mark\n");
    result = read_int("Choose a field: ", &field);
    if (result <= 0) {
        return;
    }

    switch (field) {
    case 1: {
        int new_id;
        Student *duplicate;

        result = read_int("New ID: ", &new_id);
        if (result <= 0) {
            return;
        }
        duplicate = find_student_by_id(head, new_id);
        if (new_id <= 0 || (duplicate != NULL && duplicate != student)) {
            printf("ID must be positive and unique.\n");
            return;
        }
        student->id = new_id;
        break;
    }
    case 2: {
        char new_name[STUDENT_NAME_LENGTH];

        result = read_text("New name: ", new_name, sizeof new_name);
        if (result <= 0) {
            return;
        }
        memset(student->name, 0, sizeof student->name);
        memcpy(student->name, new_name, strlen(new_name) + 1);
        break;
    }
    case 3: {
        int new_age;

        result = read_int("New age (1-120): ", &new_age);
        if (result <= 0) {
            return;
        }
        if (new_age < 1 || new_age > 120) {
            printf("Age must be between 1 and 120.\n");
            return;
        }
        student->age = new_age;
        break;
    }
    case 4: {
        int new_mark;

        result = read_int("New mark (1-100): ", &new_mark);
        if (result <= 0) {
            return;
        }
        if (new_mark < 1 || new_mark > 100) {
            printf("Mark must be between 1 and 100.\n");
            return;
        }
        student->mark = new_mark;
        break;
    }
    default:
        printf("Invalid field choice.\n");
        return;
    }

    printf("Record modified. Use V to save changes.\n");
}
