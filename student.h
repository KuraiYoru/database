#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LENGTH 50
#define MAX_FILENAME 256

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    double gpa;
} Student;

#endif // STUDENT_H