#include "student.h"

Student *find_student_by_id(Student *head, int id)
{
    while (head != NULL) {
        if (head->id == id) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}
