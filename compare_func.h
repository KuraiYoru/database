#ifndef COMPARE_FUNCH
#define COMPARE_FUNCH

#include "student.h"
#include <string.h>
#include <stdlib.h>
// Comparison functions
typedef int (*CompareFunc)(const Student*, const Student*);
int compare_id_asc(const Student* a, const Student* b);
int compare_id_desc(const Student* a, const Student* b);
int compare_name_asc(const Student* a, const Student* b);
int compare_name_desc(const Student* a, const Student* b);
int compare_age_asc(const Student* a, const Student* b);
int compare_age_desc(const Student* a, const Student* b);
int compare_gpa_asc(const Student* a, const Student* b);
int compare_gpa_desc(const Student* a, const Student* b);

// Sorting function
void merge_sort(Student* arr, int l, int r, CompareFunc compare);

#endif