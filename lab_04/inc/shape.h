#ifndef SHAPE_H
#define SHAPE_H

#include "stec.h"

typedef struct
{
  stec_t *stec;
} base_t;

void skip_stdin(void);
void print_wellcome_menu(void);
int handle_manu(base_t *data_base);
void print_line(void);

#endif
