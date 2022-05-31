#include <string.h>
#include <ctype.h>

#include "student.h"


int scan_string(char *dst, const size_t n, FILE *restrict f)
{
    size_t len = 0;
    char c;
    int fsf_response = fscanf(f, "%c", &c);

    while (fsf_response == 1 && c != '\n' && len < n - 1)
    {
        dst[len++] = c;
        dst[len] = '\0';
        fsf_response = fscanf(f, "%c", &c);
    }

    if (ferror(f))
        return ERROR;

    if (len == 0)
        return ERROR;

    if (len == n - 1)
        return ERROR;

    size_t i = 0;
    for (; dst[i] && !isalpha(dst[i]); i++);

    if (!dst[i])
        return ERROR;

    return OK;
}

int pri_student(student_t *student)
{
    if(!printf("%-16s",student->surname))
        return ERROR;
    if(!printf("%-16s",student->name))
        return ERROR;
    if(!printf("%-16s",student->group))
        return ERROR;

    if (student->sex == MAN)
    {
        if (!printf("%-16s", "Male"))
            return ERROR;
    }
    else
    {
        if (!printf("%-16s", "Female"))
            return ERROR;
    }

    if(!printf("%-16.d",student->age))
        return ERROR;
    if(!printf("%-16.3lf",student->gpa))
        return ERROR;
    if(!printf("%-16.d",student->entrance_year))
        return ERROR;

    if (student->residence_type == HOUSE)
    {
        if (!printf("%-16s", "House"))
            return ERROR;

        if (!printf("%-16s", student->residence.house.street))
            return ERROR;

        if (!printf("%-16.d", student->residence.house.house_number))
            return ERROR;

        if (!printf("%-16.d\n", student->residence.house.apartment_number))
            return ERROR;
    }
    else
    {
        if (!printf("%-16s", "Hostel"))
            return ERROR;

        if (!printf("%-16s", ""))
            return ERROR;

        if (!printf("%-16.d", student->residence.hostel.hostel_number))
            return ERROR;

        if (!printf("%-16.d\n", student->residence.hostel.room_number))
            return ERROR;
    }

    return OK;
}

int pri_all_students(student_t *list, size_t len)
{
    printf("LIST OF STUDENTS:\n");

    if (len == 0)
    {
        printf("Список пуст...\n");
        printf("* * *\n");
        return OK;
    }

    printf("%-16s%-16s%-16s%-16s%-16s%-16s%-16s%-16s%-16s%-16s%-16s\n",
           "Surname","Name","Group","Sex","Age","GPA","Entrance year","Residence","street","house/hostel","apartment/room");
    char line[11*16+1] = {'\0'};
    for (size_t i = 0; i < 11 * 16; i++)
        line[i] = '-';
    if(!printf("%s\n",line))
        return ERROR;

    int rc;
    for (size_t i = 0; i < len; i++)
    {
        rc = pri_student(list + i);
        if (rc)
            return rc;
    }
    return OK;
}

int scn_student(FILE *restrict f, student_t *dst, int flag)
{
    if (flag)
    {
        printf("Введите фамилию студента:\n");
    }

    fscanf(f, "\n");
    int rc;

    rc = scan_string(dst->surname, BAS_LEN + 1, f);
    if (rc)
        return rc;

    if (flag)
    {
        printf("Введите имя студента:\n");
    }

    rc = scan_string(dst->name, BAS_LEN + 1, f);
    if (rc)
        return rc;

    if (flag)
    {
        printf("Введите группу студента:\n");
    }

    rc = scan_string(dst->group, BAS_LEN + 1, f);
    if (rc)
        return rc;

    if (flag)
    {
        printf("Введите 1, если студент мужского пола, 2, если женского:\n");
    }

    if(!fscanf(f, "%d", &dst->sex))
        return ERROR;

    if (dst->sex != MAN && dst->sex != WOMAN)
        return ERROR;

    if (flag)
    {
        printf("Введите возраст студента:\n");
    }

    if(!fscanf(f, "%ud", &dst->age))
        return ERROR;

    if (flag)
    {
        printf("Введите средний балл студента:\n");
    }

    if(!fscanf(f, "%lf", &dst->gpa))
        return ERROR;

    if (flag)
    {
        printf("Введите год поступления студента:\n");
    }

    if(!fscanf(f, "%ud", &dst->entrance_year))
        return ERROR;

    if (flag)
    {
        printf("Введите 1, если студент не живет в общажитии, иначе введите 2:\n");
    }

    if(!fscanf(f, "%d", &dst->residence_type))
        return ERROR;
    if (dst->residence_type != HOUSE && dst->residence_type != HOSTEL)
        return ERROR;

//    fscanf(f,"\n");
    if (dst->residence_type == HOUSE)
    {
        if (flag)
        {
            printf("Введите улицу, на которой проживает студент:\n");
        }

        fscanf(f,"\n");

        rc = scan_string((char*)dst->residence.house.street, BAS_LEN + 1, f);
        if (rc)
            return rc;

        if (flag)
        {
            printf("Введите номер дома студента:\n");
        }

        if(!fscanf(f, "%ud", &dst->residence.house.house_number))
            return ERROR;

        if (flag)
        {
            printf("Введите номер квартиры студента:\n");
        }

        if(!fscanf(f, "%ud", &dst->residence.house.apartment_number))
            return ERROR;
    }
    else
    {
        if (flag)
        {
            printf("Введите номер общежития студента:\n");
        }

        if(!fscanf(f, "%ud", &dst->residence.hostel.hostel_number))
            return ERROR;

        if (flag)
        {
            printf("Введите номер комнаты студента:\n");
        }

        if(!fscanf(f, "%ud", &dst->residence.hostel.room_number))
            return ERROR;
    }

    return OK;
}
