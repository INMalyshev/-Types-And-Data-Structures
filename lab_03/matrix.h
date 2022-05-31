#ifndef _MATRIX_H_
#define _MATRIX_H_

#define OK 0
#define ERROR 1

#define EXPANSION_INDEX 2

#include <stddef.h>

typedef struct note_t note_t;

struct note_t
{
    int data;
    note_t *next;
};

note_t *new_note_t(int data);
void free_note_t(note_t *note);
void pri_note_t(FILE *f, note_t *note);

typedef struct
{
    int *data;              // список ненулевых элементов
    int *row_index;         // хранит номер строки для каждого элемента
    note_t *cols;           // содержит указатели на начало очередного столбца
    size_t elem_amount;
    size_t row_amount;
    size_t col_amount;
    size_t allocated;
} sparse_matrix_t;

void free_sparse_matrix_t(sparse_matrix_t *sparse_matrix);
void pri_sparse_matrix_t(FILE *f, sparse_matrix_t *sparse_matrix);

typedef struct
{
    int **rows;
    size_t row_am;
    size_t col_am;
} matrix_t;

matrix_t *init_matrix_t(size_t row_am, size_t col_am);
void free_matrix_t(matrix_t *matrix);
int pri_matrix_t(FILE *f, matrix_t *matrix);
matrix_t *scn_matrix_t(FILE *f);
matrix_t *multiply_matrix(matrix_t *alpha, matrix_t *betta);

sparse_matrix_t *matrix_t_to_sparse_matrix_t(matrix_t *matrix);
matrix_t *multiply_sparse_matrix_t_and_vector(sparse_matrix_t *alpha, matrix_t *betta);

#endif
