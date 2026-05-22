#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fname[50];
    char lname[50];
    int id;
    int grade;
} Student;

/*  Compare: grade first, then FirstName */
int compare(Student a, Student b) {
    if (a.grade < b.grade) return -1;
    if (a.grade > b.grade) return 1;
    return strcmp(a.fname, b.fname);
}

/*  Swap */
void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

/*  Partition */
int partition(Student arr[], int low, int high) {
    Student pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compare(arr[j], pivot) <= 0) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

/*  QuickSort */
void quicksort(Student arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quicksort(arr, low, p - 1);
        quicksort(arr, p + 1, high);
    }
}

int main() {
    Student *students = NULL;
    int count = 0;

    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error opening input file\n");
        return 1;
    }

    /*  Read dynamically  */
    Student temp;

    while (fscanf(fp, "%s %s %d %d",
                  temp.fname,
                  temp.lname,
                  &temp.id,
                  &temp.grade) == 4) {

        Student *new_ptr = realloc(students, (count + 1) * sizeof(Student));

        if (new_ptr == NULL) {
            printf("Memory allocation failed\n");
            free(students);
            fclose(fp);
            return 1;
        }

        students = new_ptr;
        students[count] = temp;
        count++;
    }

    fclose(fp);

    /*  Sort */
    if (count > 0) {
        quicksort(students, 0, count - 1);
    }

    /*  Write output */
    FILE *out = fopen("sorted_students.txt", "w");
    if (out == NULL) {
        printf("Error opening output file\n");
        free(students);
        return 1;
    }

    for (int i = 0; i < count; i++) {
        fprintf(out, "%s %s %d %d\n",
                students[i].fname,
                students[i].lname,
                students[i].id,
                students[i].grade);
    }

    fclose(out);

    free(students);

    printf("Sorting complete.\n");

    return 0;
}