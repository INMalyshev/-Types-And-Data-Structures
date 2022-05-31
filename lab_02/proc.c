#include <stdio.h>

#include "student.h"
#include "proc.h"

#define START_OFFSET 0L

int fill_list(FILE *restrict f, student_t *list, size_t *counter, size_t n_max)
{
    student_t temp;

    if (fseek(f, START_OFFSET, SEEK_SET))
        return ERROR;

    size_t i = 0;
    int rc;
    while ((rc = scn_student(f, &temp, 0)) == OK)
    {
        if (i == n_max)
            return ERROR;

        fscanf(f, "\n");
        *(list + i++) = temp;

    }

    if (ferror(f))
        return ERROR;

    *counter = i;

    return OK;
}

int compar_01(const void *s1, const void *s2)
{
    return (int) ((student_t*) s1)->entrance_year - ((student_t*) s2)->entrance_year;
}

int compar_02(const void *s1, const void *s2)
{
    return (int) ((key_student_t*) s1)->entrance_year - ((key_student_t*) s2)->entrance_year;
}

void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    if (nmemb == 1)
        return;

    char *pb = base;
    char *pe = (char*) base + nmemb * size;
    char *pc = (char*) base + size;
    char *pc_temp;
    char temp;

    while (pc < pe)
    {
        pc_temp = pc;
        while (pc_temp > pb && compar(pc_temp - size, pc) > 0)
            pc_temp -= size;

        for (size_t i = 0; i < size; i++)
        {
            temp = *(pc + i);

            for (char *p = pc; p > pc_temp; p -= size)
                *(p + i) = *(p - size + i);

            *(pc_temp + i) = temp;
        }

        pc += size;
    }
}

