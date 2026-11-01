#include "student.h"

int main(void)
{
    Student *head = NULL;
    int choice;
    int result;

    if (!load_file(&head)) {
        return EXIT_FAILURE;
    }

    for (;;) {
        printf("\nStudent Record Management\n");
        printf("1. Add student\n");
        printf("2. Display students\n");
        printf("3. Search student\n");
        printf("4. Update student\n");
        printf("5. Delete student\n");
        printf("6. Sort students\n");
        printf("7. Save records\n");
        printf("0. Exit\n");

        result = read_int("Choose an option: ", &choice);
        if (result == 0) {
            putchar('\n');
            break;
        }
        if (result < 0) {
            continue;
        }

        switch (choice) {
        case 1:
            insert_student(&head);
            break;
        case 2:
            display_students(head);
            break;
        case 3: {
            int id;
            Student *student;

            result = read_int("Student ID to search: ", &id);
            if (result <= 0) {
                break;
            }
            student = find_student_by_id(head, id);
            if (student == NULL) {
                printf("Student not found.\n");
            } else {
                printf("ID: %d\nName: %s\nAge: %d\nPercentage: %d%%\n",
                       student->id, student->name, student->age, student->mark);
            }
            break;
        }
        case 4:
            update_student(head);
            break;
        case 5:
            delete_student(&head);
            break;
        case 6:
            sort_student_records(&head);
            break;
        case 7:
            save_file(head);
            break;
        case 0: {
            int exit_choice;

            printf("\n1. Save and exit\n");
            printf("2. Exit without saving\n");
            result = read_int("Choose an option: ", &exit_choice);
            if (result == 0) {
                goto cleanup;
            }
            if (result < 0) {
                break;
            }
            if (exit_choice == 1) {
                if (save_file(head)) {
                    goto cleanup;
                }
                break;
            }
            if (exit_choice == 2) {
                goto cleanup;
            }
            printf("Choose 1 to save and exit or 2 to exit without saving.\n");
            break;
        }
        default:
            printf("Choose a number from 0 to 7.\n");
        }
    }

cleanup:
    while (head != NULL) {
        Student *next = head->next;
        free(head);
        head = next;
    }
    return 0;
}

int read_int(const char *prompt, int *value)
{
    char line[128];
    char *end;
    long parsed;

    printf("%s", prompt);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtol(line, &end, 10);
    if (end == line || errno == ERANGE) {
        printf("Invalid number.\n");
        return -1;
    }
    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        end++;
    }
    if (*end != '\0' || parsed < -2147483647L - 1 || parsed > 2147483647L) {
        printf("Invalid number.\n");
        return -1;
    }

    *value = (int)parsed;
    return 1;
}

int read_text(const char *prompt, char *buffer, size_t capacity)
{
    size_t length;
    int character;

    printf("%s", prompt);
    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return 0;
    }

    length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[--length] = '\0';
    } else {
        character = getchar();
        if (character != '\n' && character != EOF) {
            while ((character = getchar()) != '\n' && character != EOF) {
                /* Discard the remainder of an overlong input line. */
            }
            printf("Input is too long.\n");
            return -1;
        }
    }

    if (length == 0) {
        printf("This field cannot be empty.\n");
        return -1;
    }
    return 1;
}
