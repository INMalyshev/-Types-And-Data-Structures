#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

note_t *new_note_t(int data)
{
    note_t *p = calloc(1, sizeof(note_t));
    if (!p)
        return NULL;

    p->data = data;
    p->next = NULL;

    return p;
}

void free_note_t(note_t *note)
{
    if (note->next)
        free_note_t((note_t*) note->next);

    free(note);
}

void pri_note_t(FILE *f, note_t *note)
{
    printf("%d, ", note->data);

    if (note->next)
        pri_note_t(f, (void*) note->next);
}

void free_sparse_matrix_t(sparse_matrix_t *sparse_matrix)
{
    free(sparse_matrix->data);
    free(sparse_matrix->row_index);
    free_note_t(sparse_matrix->cols);

    free(sparse_matrix);
}

void pri_sparse_matrix_t(FILE *f, sparse_matrix_t *sparse_matrix)
{
    fprintf(f, " A: (");

    for (size_t i = 0; i < sparse_matrix->elem_amount; i++)
        fprintf(f, "%d, ", sparse_matrix->data[i]);

    fprintf(f, ")\n");

    fprintf(f, "iA: (");

    for (size_t i = 0; i < sparse_matrix->elem_amount; i++)
        fprintf(f, "%d, ", sparse_matrix->row_index[i]);

    fprintf(f, ")\n");

    fprintf(f, "jA: (");

    pri_note_t(f, sparse_matrix->cols);

    fprintf(f, ")\n");
}

sparse_matrix_t *matrix_t_to_sparse_matrix_t(matrix_t *matrix)
{
    size_t elem_am = 0;

    for (size_t i = 0; i < matrix->row_am; i++)
    {
        for (size_t j = 0; j < matrix->col_am; j++)
        {
            if (matrix->rows[i][j] != 0)
            {
                elem_am++;
            }
        }
    }

    sparse_matrix_t *sparse_matrix = (sparse_matrix_t*) malloc(sizeof(sparse_matrix_t));
    if (!sparse_matrix)
        return NULL;

    sparse_matrix->data = (int*) malloc(elem_am * sizeof(int));
    if (!sparse_matrix->data)
    {
        free(sparse_matrix);
        return NULL;
    }

    sparse_matrix->row_index = (int*) malloc(elem_am * sizeof(int));
    if (!sparse_matrix->row_index)
    {
        free(sparse_matrix->data);
        free(sparse_matrix);
        return NULL;
    }

    sparse_matrix->elem_amount = elem_am;
    sparse_matrix->row_amount = matrix->row_am;
    sparse_matrix->col_amount = matrix->col_am;
    sparse_matrix->allocated = elem_am;

    sparse_matrix->cols = new_note_t(0);
    if (!sparse_matrix->cols) return NULL;

    size_t cur_position = 0;
    note_t *cur_note_t = sparse_matrix->cols;
    for (size_t j = 0; j < matrix->col_am; j++)
        for (size_t i = 0; i < matrix->row_am; i++)
        {
            if (j && !i)
            {
                note_t *new_note = new_note_t(cur_position);

                cur_note_t->next = (void*) new_note;

                if (!cur_note_t->next)
                {
                    free_sparse_matrix_t(sparse_matrix);
                    return NULL;
                }

                cur_note_t = (void*) cur_note_t->next;
            }

            if (matrix->rows[i][j] != 0)
            {
                sparse_matrix->data[cur_position] = matrix->rows[i][j];
                sparse_matrix->row_index[cur_position] = (int) i;
                cur_position++;
            }
        }

    return sparse_matrix;
}

matrix_t *init_matrix_t(size_t row_am, size_t col_am)
{
    matrix_t *matrix = (matrix_t*) malloc(sizeof(matrix_t));
    if (!matrix)
        return NULL;

    matrix->row_am = row_am;
    matrix->col_am = col_am;

    matrix->rows = (int**) calloc(row_am, sizeof(int*));
    if (!matrix->rows)
    {
        free(matrix);
        return NULL;
    }

    for (size_t i = 0; i < row_am; i++)
    {
        matrix->rows[i] = (int*) calloc(col_am, sizeof(int));
        if (!matrix->rows[i])
        {
            free_matrix_t(matrix);
            return NULL;
        }
    }

    return matrix;
}

void free_matrix_t(matrix_t *matrix)
{
    if (matrix)
    {
        if (matrix->rows)
        {
            for (size_t i = 0; i < matrix->row_am; i++)
                free(matrix->rows[i]);

            free(matrix->rows);
        }

        free(matrix);
    }
}

int pri_matrix_t(FILE *f, matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->row_am; i++)
    {
        for (size_t j = 0; j < matrix->col_am; j++)
            if(!fprintf(f, "%d ", matrix->rows[i][j]))
                return ERROR;

        if(!fprintf(f, "\n"))
            return ERROR;
    }

    return OK;
}

matrix_t *scn_matrix_t(FILE *f)
{
    size_t row_am, col_am, elem_am;
    if (3 != fscanf(f, "%zu%zu%zu", &row_am, &col_am, &elem_am))
        return NULL;

    if (!row_am || !col_am)
        return NULL;

    if (elem_am > row_am * col_am)
        return NULL;

    matrix_t *matrix = init_matrix_t(row_am, col_am);
    if (!matrix)
        return NULL;

    size_t row, col;
    int elem;
    for (size_t i = 0; i < elem_am; i++)
    {
        if (3 != fscanf(f, "%zu%zu%d", &row, &col, &elem))
            return NULL;

        if (row >= row_am)
            return NULL;

        if (col >= col_am)
            return NULL;

        if (elem == 0)
            return NULL;

        matrix->rows[row][col] = elem;
    }

    return matrix;
}

matrix_t *multiply_matrix(matrix_t *alpha, matrix_t *betta)
{
    if (alpha->col_am != betta->row_am) return NULL;

    matrix_t *matrix = init_matrix_t(alpha->row_am, betta->col_am);
    if (!matrix)
        return NULL;

    for (size_t a_i = 0; a_i < alpha->row_am; a_i++)
        for (size_t b_j = 0; b_j < betta->col_am; b_j++)
            for (size_t index = 0; index < alpha->col_am; index++)
                matrix->rows[a_i][b_j] += alpha->rows[a_i][index] * betta->rows[index][b_j];

    return matrix;
}

matrix_t *multiply_sparse_matrix_t_and_vector(sparse_matrix_t *alpha, matrix_t *betta)
{
    matrix_t *matrix = init_matrix_t(alpha->row_amount, betta->col_am);
    if (!matrix)
        return NULL;

    size_t elem_used = 0;
    note_t *p = alpha->cols;

    while (p->next && elem_used < alpha->elem_amount)
    {
        for (int i = p->data; i < p->next->data && elem_used < alpha->elem_amount; i++)
        {
            matrix->rows[alpha->row_index[i]][0] += alpha->data[i] * betta->rows[alpha->row_index[i]][0];
            elem_used++;
        }

        p = p->next;
    }

    return matrix;
}
