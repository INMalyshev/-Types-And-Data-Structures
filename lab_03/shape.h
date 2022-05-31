#ifndef SHAPE_H
#define SHAPE_H

#include <inttypes.h>

#include "matrix.h"

#define LINE_LEN 1024
#define STATISTICS_FILE_NAME "statistics.txt"
typedef char line_t[LINE_LEN];

//typedef struct couple_t couple_t;

typedef struct
{
    matrix_t *matrix;
    sparse_matrix_t *sparse_matrix;
} couple_t;

couple_t *create_couple_t(void);

void pri_init_menu(void);
void pri_main_menu(void);
void pri_input_instruction(void);

int handle_init_menu(couple_t *couple);
int handle_main_menu(int choice, couple_t *couple);
uint64_t tick(void);
void skip_stdin(void);

#endif
