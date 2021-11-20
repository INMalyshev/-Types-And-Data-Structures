#include <stddef.h>
#include <stdio.h>

#include "simulation.h"

int main(void)
{
  setbuf(stdout, NULL);

  simulate_with_queue();

  return 0;
}
