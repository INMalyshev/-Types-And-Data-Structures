#include <stdio.h>

#include "rc.h"
#include "shape.h"
#include "stec.h"

int main(void)
{
  setbuf(stdout, NULL);

  base_t data_base;
  data_base.stec = new_stec_t();
  data_base.stec_deallocated_memory = new_list_t();
  data_base.array_stec = NULL;
  data_base.array_stec_deallocated_memory = new_list_t();

  while (handle_manu(&data_base) == OK);

  printf("Программа завершена.");

  return OK;
}
