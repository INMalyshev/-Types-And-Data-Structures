#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <stdio.h>

#define OK 0
#define ERROR 17

#define MAN 1
#define WOMAN 2
#define HOUSE 1
#define HOSTEL 2

#define BAS_LEN 16
#define MAX_LEN 128

typedef struct {
    char street[MAX_LEN];
    unsigned int house_number;
    unsigned int apartment_number;
} house_t;

typedef struct {
    unsigned int hostel_number;
    unsigned int room_number;
} hostel_t;

typedef struct {
    char surname[MAX_LEN];
    char name[MAX_LEN];
    char group[MAX_LEN];
    int sex;
    unsigned int age;
    double gpa;
    unsigned int entrance_year;
    int residence_type;
    union {
        house_t house;
        hostel_t hostel;
    } residence;
} student_t;

typedef struct
{
    size_t index;
    unsigned int entrance_year;
} key_student_t;

int scn_student(FILE *restrict f, student_t *dst, int flag);
int pri_student(student_t *student);
int scan_string(char *dst, const size_t n, FILE *restrict f);
int pri_all_students(student_t *list, size_t len);

#endif
