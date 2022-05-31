#ifndef _PROC_H_
#define _PROC_H_

#include <stdio.h>

#include "student.h"

int fill_list(FILE *restrict f, student_t *list, size_t *counter, size_t n_max);
int compar_01(const void *s1, const void *s2);
int compar_02(const void *s1, const void *s2);
void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

#endif
