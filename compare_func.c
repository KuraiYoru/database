#include "compare_func.h"
#include "student.h"

// Comparison functions
int compare_id_asc(const Student* a, const Student* b) {
    return a->id - b->id;
}

int compare_id_desc(const Student* a, const Student* b) {
    return b->id - a->id;
}

int compare_name_asc(const Student* a, const Student* b) {
    return strcasecmp(a->name, b->name);
}

int compare_name_desc(const Student* a, const Student* b) {
    return strcasecmp(b->name, a->name);
}

int compare_age_asc(const Student* a, const Student* b) {
    return a->age - b->age;
}

int compare_age_desc(const Student* a, const Student* b) {
    return b->age - a->age;
}

int compare_gpa_asc(const Student* a, const Student* b) {
    if (a->gpa < b->gpa) return -1;
    if (a->gpa > b->gpa) return 1;
    return 0;
}

int compare_gpa_desc(const Student* a, const Student* b) {
    if (b->gpa < a->gpa) return -1;
    if (b->gpa > a->gpa) return 1;
    return 0;
}

void merge(Student* arr, int l, int m, int r, CompareFunc compare) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Student* L = malloc(n1 * sizeof(Student));
    Student* R = malloc(n2 * sizeof(Student));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (compare(&L[i], &R[j]) <= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void merge_sort(Student* arr, int l, int r, CompareFunc compare) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m, compare);
        merge_sort(arr, m + 1, r, compare);
        merge(arr, l, m, r, compare);
    }
}

