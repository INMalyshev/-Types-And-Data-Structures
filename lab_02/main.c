#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "student.h"
#include "proc.h"

#define N_MAX 1000000

#define LOADING_ERROR 100
#define READING_ERROR 101
#define DELETING_ERROR 102
#define FINDING_ERROR 103
#define STATISTIC_ERROR 104

student_t students[N_MAX];
key_student_t keys[N_MAX];
student_t students_copy[N_MAX];
key_student_t keys_copy[N_MAX];
size_t len = 0;

void pri_menu(void)
{
    printf("\n");
    printf("------------------------------------------------------------------------------\n");
    printf("Меню:\n");
    printf("1. Загрузить список студентов из файла;\n");
    printf("2. Добавить студента в конец списка;\n");
    printf("3. Удалить студентов по году поступления;\n");
    printf("4. Вывести список студентов указанного года поступления, живущих в общежитии;\n");
    printf("5. Отсортировать таблицу методом простых вставок (по году поступления);\n");
    printf("6. Отсортировать таблицу ключей методом простых вставок (по году поступления);\n");
    printf("7. Отсортировать таблицу с помощью qsort (по году поступления);\n");
    printf("8. Отсортировать таблицу ключей с помощью qsort (по году поступления);\n");
    printf("9. Вывести сравнение сортировок;\n");
    printf("10. Вывести таблицу;\n");
    printf("11. Вывести таблицу по таблице ключей;\n");
    printf("0. Выход.\n");
    printf("------------------------------------------------------------------------------\n");
    printf("\n");
    printf("Ваш выбор: ");
}

void update_keys(void)
{
    key_student_t key;
    for (size_t i = 0; i < len; i++)
    {
        key.index = i;
        key.entrance_year = students[i].entrance_year;
        keys[i] = key;
    }
}

int p1(void)
{
    char s[N_MAX];
    printf("Enter file name:\n");

    scanf("\n");

    int rc = scan_string(s, BAS_LEN + 1, stdin);
    if (rc)
        return rc;

    FILE *f = fopen(s, "rt");
    if (!f)
        return LOADING_ERROR;

    if (fill_list(f, students, &len, N_MAX))
        return LOADING_ERROR;

    update_keys();

    return OK;
}

int p2(void)
{
    if (len >= N_MAX)
        return READING_ERROR;

    student_t student;

    if (scn_student(stdin, &student, 1))
        return READING_ERROR;

    students[len++] = student;

    update_keys();

    return OK;
}

int p3(void)
{
    int year;
    printf("Введите год поступления:\n");
    if(!scanf("%d", &year))
        return DELETING_ERROR;
    for (int i = 0; i < (int) len;)
    {
        if ((int)students[i].entrance_year == year)
        {
            for (int j = i; j < (int) len - 1; j++)
                students[j] = students[j+1];
            len--;
        }
        else i++;
    }

    update_keys();

    return OK;
}

int p4(void)
{
    int year, counter = 0;
    printf("Введите год поступления:\n");
    if(!scanf("%d", &year))
        return FINDING_ERROR;


    printf("%-16s%-16s%-16s%-16s%-16s%-16s%-16s%-16s%-16s%-16s%-16s\n",
           "Surname","Name","Group","Sex","Age","GPA","Entrance year","Residence","street","house/hostel","apartment/room");
    char line[11*16+1] = {'\0'};
    for (size_t i = 0; i < 11 * 16; i++)
        line[i] = '-';
    if(!printf("%s\n",line))
        return FINDING_ERROR;
    for (size_t i = 0; i < len; i++)
    {
        if (students[i].residence_type == HOSTEL && (int) students[i].entrance_year == year)
        {
            if(pri_student(&students[i]))
                return FINDING_ERROR;
            counter++;
        }
    }
    if (!counter)
    {
        printf("Ничего не найдено...\n");
        printf("* * *\n");
    }

    return OK;
}

int p5(void)
{
    mysort(students, len, sizeof(student_t), compar_01);

    return OK;
}

int p6(void)
{
    mysort(keys, len, sizeof(key_student_t), compar_02);

    return OK;
}

int p7(void)
{
    qsort(students, len, sizeof(student_t), compar_01);

    return OK;
}

int p8(void)
{
    qsort(keys, len, sizeof(key_student_t), compar_02);

    return OK;
}

int p9(void)
{
    char s[N_MAX];
    printf("Enter file name:\n");

    scanf("\n");

    int rc = scan_string(s, BAS_LEN + 1, stdin);
    if (rc)
        return rc;

    FILE *f = fopen(s, "rt");
    if (!f)
        return STATISTIC_ERROR;



    clock_t t1, t2;

    for (size_t i = 0; i < len; i++)
    {
        students_copy[i] = students[i];
        keys_copy[i] = keys[i];
    }

    if (fill_list(f, students, &len, N_MAX))
        return STATISTIC_ERROR;

    update_keys();

    t1 = clock();
    if(p5()) return STATISTIC_ERROR;
    t2 = clock();
    double p5_time = (t2 - t1) / (CLOCKS_PER_SEC * 1.0);

    if (fill_list(f, students, &len, N_MAX))
        return STATISTIC_ERROR;

    update_keys();

    t1 = clock();
    if(p6()) return STATISTIC_ERROR;
    t2 = clock();
    double p6_time = (t2 - t1) / (CLOCKS_PER_SEC * 1.0);

    if (fill_list(f, students, &len, N_MAX))
        return STATISTIC_ERROR;

    update_keys();

    t1 = clock();
    if(p7()) return STATISTIC_ERROR;
    t2 = clock();
    double p7_time = (t2 - t1) / (CLOCKS_PER_SEC * 1.0);

    if (fill_list(f, students, &len, N_MAX))
        return STATISTIC_ERROR;

    update_keys();

    t1 = clock();
    if(p8()) return STATISTIC_ERROR;
    t2 = clock();
    double p8_time = (t2 - t1) / (CLOCKS_PER_SEC * 1.0);

    for (size_t i = 0; i < len; i++)
    {
        students[i] = students_copy[i];
        keys[i] = keys_copy[i];
    }

    printf("Сравнение сортировок:\n");
    printf("Сортировка массива ключей (qsort)        : %lf (сек) : k = %lf\n", p8_time, p8_time / p8_time);
    printf("Сортировка массива ключей (вставками)    : %lf (сек) : k = %lf\n", p6_time, p6_time / p8_time);
    printf("Сортировка массива студентов (qsort)     : %lf (сек) : k = %lf\n", p7_time, p7_time / p8_time);
    printf("Сортировка массива студентов (вставками) : %lf (сек) : k = %lf\n", p5_time, p5_time / p8_time);
    printf("Длина контрольного массива %zu\n", len);

    return OK;
}

int p10(void)
{
    if (pri_all_students(students, len))
        return ERROR;

    return OK;
}

int p11(void)
{
    printf("LIST OF STUDENTS:\n");
    printf("%-16s%-16s%-16s%-16s%-16s%-16s%-16s%-16s%-16s%-16s%-16s\n",
           "Surname","Name","Group","Sex","Age","GPA","Entrance year","Residence","street","house/hostel","apartment/room");
    char line[11*16+1] = {'\0'};
    for (size_t i = 0; i < 11 * 16; i++)
        line[i] = '-';
    if(!printf("%s\n",line))
        return ERROR;
    if (len == 0)
    {
        printf("Список пуст...\n");
        printf("* * *\n");
        return OK;
    }

    for (size_t i = 0; i < len; i++)
    {
        if (pri_student(&students[keys[i].index]))
            return ERROR;
    }

    return OK;
}

int main(void)
{
    setbuf(stdout, NULL);

    int choice;

    while (1)
    {
        pri_menu();

        if (!scanf("%d", &choice))
        {
            printf("Ошибка выбора . . .\n");
            printf("Аварийная остановка.\n");
            return ERROR;
        }

        if (0 > choice || 11 < choice)
        {
            printf("Ошибка выбора . . .\n");
            printf("Аварийная остановка.\n");
            return ERROR;
        }

        if (choice == 1)
        {
            printf("Считывание . . .\n");
            if (p1())
            {
                printf("Ошибка считывания . . .\n");
                printf("Аварийная остановка.\n");
                return ERROR;
            }
            printf("Считывание успешно.\n");
        }
        else if (choice == 10)
        {
            printf("Начало печати . . .\n");
            if (p10())
            {
                printf("Ошибка печати . . .\n");
                printf("Аварийная остановка.\n");
                return ERROR;
            }
            printf("Конец печати.\n");
        }
        else if (choice == 2)
        {
            printf("Считывание . . .\n");
            if (p2())
            {
                printf("Ошибка считывания . . .\n");
                printf("Аварийная остановка.\n");
                return ERROR;
            }
            printf("Считывание успешно.\n");
        }
        else if (choice == 3)
        {
            printf("Удаление . . .\n");
            if (p3())
            {
                printf("Ошибка удаления . . .\n");
                printf("Аварийная остановка.\n");
                return ERROR;
            }
            printf("Удаление успешно.\n");
        }
        else if (choice == 4)
        {
            printf("Поиск . . .\n");
            if (p4())
            {
                printf("Ошибка поиска . . .\n");
                printf("Аварийная остановка.\n");
                return ERROR;
            }
            printf("Поиск успешно.\n");
        }
        else if (choice == 7)
        {
            printf("Сортировка всего списка qsort . . .\n");
            if (p7())
            {
                printf("Ошибка сортировки . . .\n");
                printf("Аварийная остановка.\n");
                return ERROR;
            }
            printf("Сортировка успешно.\n");
        }
        else if (choice == 8)
        {
            printf("Сортировка списка ключей qsort . . .\n");
            if (p8())
            {
                printf("Ошибка сортировки . . .\n");
                printf("Аварийная остановка.\n");
                return ERROR;
            }
            printf("Сортировка успешно.\n");
        }
        else if (choice == 0)
        {
            printf("Программа завершена корректно.\n");
            return OK;
        }
        else if (choice == 11)
        {
            printf("Начало печати . . .\n");
            if (p11())
            {
                printf("Ошибка печати . . .\n");
                printf("Аварийная остановка.\n");
                return ERROR;
            }
            printf("Конец печати.\n");
        }
        else if (choice == 5)
        {
            printf("Сортировка всего списка методом простых вставок . . .\n");
            if (p5())
            {
                printf("Ошибка сортировки . . .\n");
                printf("Аварийная остановка.\n");
                return ERROR;
            }
            printf("Сортировка успешно.\n");
        }
        else if (choice == 6)
        {
            printf("Сортировка списка ключей методом простых вставок . . .\n");
            if (p6())
            {
                printf("Ошибка сортировки . . .\n");
                printf("Аварийная остановка.\n");
                return ERROR;
            }
            printf("Сортировка успешно.\n");
        }
        else if (choice == 9)
        {
            printf("Проведение замеров для разных сортировок . . .\n");
            if (p9())
            {
                printf("Ошибка сортировки . . .\n");
                printf("Аварийная остановка.\n");
                return ERROR;
            }
            printf("Замеры успешно.\n");
        }
    }
}