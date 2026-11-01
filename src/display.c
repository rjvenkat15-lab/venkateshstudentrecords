#include "student.h"

void display_students(const Student *student)
{
    if (student == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\n%-8s %-30s %-8s %-12s\n", "ID", "Name", "Age", "Percentage");
    printf("----------------------------------------------------------\n");
    while (student != NULL) {
        char percentage[8];

        snprintf(percentage, sizeof percentage, "%d%%", student->mark);
        printf("%-8d %-30s %-8d %-12s\n",
               student->id, student->name, student->age, percentage);
        student = student->next;
    }
}
