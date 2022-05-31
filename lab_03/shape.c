#include <stdio.h>
#include <stdlib.h>

#include "shape.h"

char *in_file = "matrix.txt";
char *vector_in_file = "vector.txt";

couple_t *create_couple_t(void)
{
    couple_t *couple = malloc(sizeof(couple_t));
    if (!couple) return NULL;

    return couple;
}

void pri_init_menu(void)
{
    printf("                                                   \n");
    printf("Выберите действие:                                 \n");
    printf("1. Загрузить матрицу из файла ('matrix.txt');      \n");
    printf("2. Инициировать матрицу вручную.                   \n");
    printf("---------------------------------------------------\n");
}

void pri_vector_menu(void)
{
    printf("                                                   \n");
    printf("Выберите действие:                                 \n");
    printf("1. Загрузить вектор из файла ('vector.txt');       \n");
    printf("2. Инициировать вектор вручную (координатный ввод).\n");
    printf("---------------------------------------------------\n");
}

void pri_main_menu(void)
{
    printf("                                                   \n");
    printf("Выберите действие:                                 \n");
    printf("1. Вывести матрицу на экран;                       \n");
    printf("2. Вывести разреженную матрицу на экран;           \n");
    printf("3. Установить элемент матрицы по позиции;          \n");
    printf("4. Умножить матрицу на столбец, вывести результат; \n");
    printf("5. Вывести сравнение двух подходов хранения матриц;\n");
    printf("0. Выход.                                          \n");
    printf("---------------------------------------------------\n");
}

void pri_input_instruction(void)
{
    printf("                                                   \n");
    printf("Правильный ввод матрицы:                           \n");
    printf("1. Сначала введите 3 целых положительных числа:    \n");
    printf("   Количество строк, столбцов, ненулевых элементов.\n");
    printf("2. Введите информацию о всех ненулевых элементах:  \n");
    printf("   Индекс строки, столбца, значение элемента.      \n");
    printf("(Значение элемента - целое число, значение индекса \n");
    printf(" - целое положительное число, отличное от нуля)    \n");
    printf("---------------------------------------------------\n");
}

int handle_init_menu(couple_t *couple)
{
    pri_init_menu();
    printf("Ваш выбор: ");

    int choice;
    if (1 != scanf("%d", &choice))
        return ERROR;

    if (1 == choice)
    {
        FILE *f = fopen(in_file, "rt");
        if (!f) return ERROR;

        couple->matrix = scn_matrix_t(f);
        if (!couple->matrix) return ERROR;

        fclose(f);

        couple->sparse_matrix = matrix_t_to_sparse_matrix_t(couple->matrix);
        if (!couple->sparse_matrix) return ERROR;

        return OK;
    }

    if (2 == choice)
    {
        pri_input_instruction();

        couple->matrix = scn_matrix_t(stdin);
        if (!couple->matrix) return ERROR;

        couple->sparse_matrix = matrix_t_to_sparse_matrix_t(couple->matrix);
        if (!couple->sparse_matrix) return ERROR;

        return OK;
    }

    return ERROR;
}

int handle_vector_input(matrix_t *vector, size_t len)
{
    pri_vector_menu();
    printf("Ваш выбор: ");

    int choice;
    if (1 != scanf("%d", &choice))
        return ERROR;

    if (1 == choice)
    {
        FILE *f = fopen(vector_in_file, "rt");
        if (!f) return ERROR;

        size_t row_am, col_am, elem_am;
        if (3 != fscanf(f, "%zu%zu%zu", &row_am, &col_am, &elem_am))
            return ERROR;

        if (row_am != len || col_am != 1)
            return ERROR;

        if (elem_am > row_am * col_am)
            return ERROR;

        int row, col;
        int elem;
        for (size_t i = 0; i < elem_am; i++)
        {
            if (3 != fscanf(f, "%d%d%d", &row, &col, &elem))
                return ERROR;

            if (row >= (int) row_am)
                return ERROR;

            if (col >= (int) col_am)
                return ERROR;

            if (elem == 0)
                return ERROR;

            vector->rows[row][col] = elem;
        }

        fclose(f);

        return OK;
    }

    if (2 == choice)
    {
        pri_input_instruction();

        size_t row_am, col_am, elem_am;
        if (3 != fscanf(stdin, "%zu%zu%zu", &row_am, &col_am, &elem_am))
            return ERROR;

        if (row_am != len || col_am != 1)
            return ERROR;

        if (elem_am > row_am * col_am)
            return ERROR;

        int row, col;
        int elem;
        for (size_t i = 0; i < elem_am; i++)
        {
            if (3 != fscanf(stdin, "%d%d%d", &row, &col, &elem))
                return ERROR;

            if (row >= (int) row_am)
                return ERROR;

            if (col >= (int) col_am)
                return ERROR;

            if (elem == 0)
                return ERROR;

            vector->rows[row][col] = elem;
        }

        return OK;
    }

    return ERROR;
}

int handle_main_menu(int choice, couple_t *couple)
{
    switch (choice)
    {
        case 0:
        {
            return OK;
        }

        case 1:
        {
            printf("\n Матрица в виде таблицы чисел:\n\n");
            pri_matrix_t(stdout, couple->matrix);
            return OK;
        }

        case 2:
        {
            printf("\n Разреженная матрица:\n\n");
            pri_sparse_matrix_t(stdout, couple->sparse_matrix);
            return OK;
        }

        case 3:
        {
            printf("\n Введите индекс строки, индекс столбца и значение элемента\n");
            printf(" (Индексы -- положительные целые числа, значение элемента -- целое число):\n");

            size_t row, col;
            int elem;

            if (3 != fscanf(stdin, "%zu%zu%d", &row, &col, &elem)) return ERROR;

            if (row >= couple->matrix->row_am || col >= couple->matrix->col_am) return ERROR;

            couple->matrix->rows[row][col] = elem;

            couple->sparse_matrix = matrix_t_to_sparse_matrix_t(couple->matrix);

            if (!couple->sparse_matrix) return ERROR;

            return OK;
        }

        case 4:
        {
            matrix_t *alpha = init_matrix_t(couple->matrix->col_am, 1);
            if (!alpha) return ERROR;

            printf("\n Для выполнения умножения матрицы на столбец, необходимо\n");
            printf(" ввести столбец, состоящий из %zu целочисленных элементов: \n\n", couple->matrix->col_am);

            while (handle_vector_input(alpha, couple->matrix->col_am))
            {
                printf("Что-то пошло не так...\n");
                printf("Возврат к вводу вектора...\n");
                skip_stdin();
            }

//            for (size_t i = 0; i < couple->matrix->col_am; i++)
//                if (1 != fscanf(stdin, "%d", (int*) alpha->rows[i]))
//                    return ERROR;

            int64_t t1, t2;

            t1 = tick();
            matrix_t *result = multiply_matrix(couple->matrix, alpha);
            t2 = tick();

            int64_t t3, t4;

            t3 = tick();
            multiply_sparse_matrix_t_and_vector(couple->sparse_matrix, alpha);
            t4 = tick();

            if (!result) return ERROR;

            sparse_matrix_t *result_result = matrix_t_to_sparse_matrix_t(result);

            printf("\n Матрица, получившаяся после выполнения умножения:\n");
            // pri_matrix_t(stdout, result);
            pri_sparse_matrix_t(stdout, result_result);

            printf("\n Размерность матрицы: ( %zu x %zu )\n", couple->matrix->row_am, couple->matrix->col_am);
            printf(" Количество тактов процессора, при 'обычном' хранении матрицы: %" PRId64 "\n", t2 - t1);
            printf(" Количество тактов процессора, при 'разреженном' хранении матрицы: %" PRId64 "\n", t4 - t3 );

            return OK;
        }

        case 5:
        {
            FILE *f = fopen(STATISTICS_FILE_NAME, "rt");
            if (!f) return ERROR;

            printf("\n Информация из 'statistics.txt':\n\n");

            line_t line;
            while (fgets(line, LINE_LEN, f))
                printf("%s", line);

            fclose(f);

            printf("\n");

            return OK;
        }
    }

    return ERROR;
}

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
    "rdtsc\n"
    "movl %%edx, %0\n"
    "movl %%eax, %1\n"
    : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

void skip_stdin(void)
{
    int c;
    do
    {
        c = getchar();
    }
    while (c != '\n' && c != EOF);
}
