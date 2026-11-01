#include "student.h"

#ifdef _WIN32
#include <windows.h>
#endif

#define TEMP_STUDENT_FILE "data/students.tmp"

typedef struct {
    int id;
    char name[STUDENT_NAME_LENGTH];
    int age;
    int mark;
} StudentFileRecord;

static void free_students(Student *head)
{
    while (head != NULL) {
        Student *next = head->next;
        free(head);
        head = next;
    }
}

int load_file(Student **head)
{
    FILE *file;
    StudentFileRecord record;
    long file_size;
    Student **tail = head;

    *head = NULL;
    file = fopen(STUDENT_FILE, "rb");
    if (file == NULL) {
        if (errno == ENOENT) {
            return 1;
        }
        perror("Could not open student data file");
        return 0;
    }

    if (fseek(file, 0, SEEK_END) != 0 || (file_size = ftell(file)) < 0) {
        perror("Could not determine student data file size");
        fclose(file);
        return 0;
    }
    if ((unsigned long)file_size % sizeof record != 0) {
        fprintf(stderr, "Student data file contains an incomplete record.\n");
        fclose(file);
        return 0;
    }
    if (fseek(file, 0, SEEK_SET) != 0) {
        perror("Could not rewind student data file");
        fclose(file);
        return 0;
    }

    while (fread(&record, sizeof record, 1, file) == 1) {
        Student *student;
        Student *existing;

        if (record.id <= 0 ||
            memchr(record.name, '\0', sizeof record.name) == NULL ||
            record.name[0] == '\0' ||
            record.age < 1 || record.age > 120 ||
            record.mark < 1 || record.mark > 100) {
            fprintf(stderr, "Student data file contains an invalid record.\n");
            free_students(*head);
            *head = NULL;
            fclose(file);
            return 0;
        }
        for (existing = *head; existing != NULL; existing = existing->next) {
            if (existing->id == record.id) {
                fprintf(stderr, "Student data file contains duplicate IDs.\n");
                free_students(*head);
                *head = NULL;
                fclose(file);
                return 0;
            }
        }

        student = calloc(1, sizeof *student);
        if (student == NULL) {
            perror("Could not allocate student record");
            free_students(*head);
            *head = NULL;
            fclose(file);
            return 0;
        }
        student->id = record.id;
        memcpy(student->name, record.name, strlen(record.name) + 1);
        student->age = record.age;
        student->mark = record.mark;
        student->next = NULL;
        *tail = student;
        tail = &student->next;
    }

    if (ferror(file)) {
        perror("Could not read student data file");
        free_students(*head);
        *head = NULL;
        fclose(file);
        return 0;
    }
    if (fclose(file) != 0) {
        perror("Could not close student data file");
        free_students(*head);
        *head = NULL;
        return 0;
    }

    if (*head != NULL) {
        printf("Records loaded successfully.\n");
    }
    return 1;
}

int save_file(const Student *head)
{
    FILE *file = fopen(TEMP_STUDENT_FILE, "wb");
    const Student *student;

    if (file == NULL) {
        perror("Could not create temporary student data file");
        return 0;
    }

    for (student = head; student != NULL; student = student->next) {
        StudentFileRecord record;

        memset(&record, 0, sizeof record);
        record.id = student->id;
        memcpy(record.name, student->name, strlen(student->name) + 1);
        record.age = student->age;
        record.mark = student->mark;
        if (fwrite(&record, sizeof record, 1, file) != 1) {
            perror("Could not write student record");
            fclose(file);
            remove(TEMP_STUDENT_FILE);
            return 0;
        }
    }

    if (fclose(file) != 0) {
        perror("Could not close temporary student data file");
        remove(TEMP_STUDENT_FILE);
        return 0;
    }

#ifdef _WIN32
    if (!MoveFileExA(TEMP_STUDENT_FILE, STUDENT_FILE,
                     MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
        fprintf(stderr, "Could not replace student data file (Windows error %lu).\n",
                (unsigned long)GetLastError());
        remove(TEMP_STUDENT_FILE);
        return 0;
    }
#else
    if (rename(TEMP_STUDENT_FILE, STUDENT_FILE) != 0) {
        perror("Could not replace student data file");
        remove(TEMP_STUDENT_FILE);
        return 0;
    }
#endif

    printf("Records saved successfully.\n");
    return 1;
}
