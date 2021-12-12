#include <stdio.h>

#include "binary_tree.h"
#include "interior_hash_table.h"
#include "text_file.h"
#include "shape.h"

int main(int argc, char **argv)
{
  setbuf(stdout, NULL);

  if (2 != argc)
  {
    printf("No filename. Restart program.\n");
    return 1;
  }

  structures_t *structures = index(argv[1]);
  if (!structures)
  {
    printf("Exit failure.\n");
    return 1;
  }

  while (mainloop_iteration(structures));
  // {
  //   printf("OK\n");
  // }

  return 0;
}
