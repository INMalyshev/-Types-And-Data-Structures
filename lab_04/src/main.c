#include <stdio.h>

#include "rc.h"
#include "shape.h"
#include "stec.h"

int main(void)
{
  setbuf(stdout, NULL);

  base_t data_base;
  data_base.stec = new_stec_t();

  while (handle_manu(&data_base) == OK)
    printf("Успешно\n");

  printf("Программа завершена.");

  return OK;
}
