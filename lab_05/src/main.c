#include <stddef.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

#include "shape.h"
#include "rc.h"

int main(void)
{
  setbuf(stdout, NULL);

  while (handle_manu() == OK);

  printf("Программа завершена.");

  return OK;

  return 0;
}
