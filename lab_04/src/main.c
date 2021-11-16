#include <stdio.h>

#include "rc.h"
#include "shape.h"
#include "stack.h"

int main(void)
{
  setbuf(stdout, NULL);

  base_t data_base;
  data_base.stack = new_stack_t();
  data_base.stack_deallocated_memory = new_list_t();
  data_base.array_stack = NULL;
  data_base.array_stack_deallocated_memory = new_list_t();

  while (handle_manu(&data_base) == OK);

  printf("Программа завершена.");

  return OK;
}
