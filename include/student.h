#ifndef STUDENT_H
#define STUDENT_H

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_NAME_LENGTH 80
#define STUDENT_FILE "data/students.dat"

typedef struct student {
    int id;
    char name[STUDENT_NAME_LENGTH];
    int age;
    int mark;
    struct student *next;
} Student;

int read_int(const char *prompt, int *value);
int read_text(const char *prompt, char *buffer, size_t capacity);

int load_file(Student **head);
int save_file(const Student *head);
void insert_student(Student **head);
void display_students(const Student *head);
Student *find_student_by_id(Student *head, int id);
void update_student(Student *head);
void delete_student(Student **head);
void sort_student_records(Student **head);

#endif
