#include <stddef.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

#include "simulation.h"
#include "tick.h"

int main(void)
{
  setbuf(stdout, NULL);

  uint64_t t = tick();
  printf("%"PRIu64"\n", t);
  srand(t);

  simulate_with_queue();
  simulate_with_array_queue();

  return 0;
}
