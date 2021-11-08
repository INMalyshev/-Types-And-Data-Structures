#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "mystring.h"
#include "rc.h"

int scan_string_t(string_t *dst, FILE *restrict f)
{
  char c;
  int fsf_response = fscanf(f, "%c", &c);

  char *string = calloc(INITIAL_STRING_LEN, sizeof(char));
  if (!string)
    return ALLOCATION_ERROR;

  size_t allocated = INITIAL_STRING_LEN;

  size_t len = 0;

  while (fsf_response == GOT_ONE_CHAR && c != '\n')
  {
    if (strlen(string) == allocated - 1)
    {
      char *new_string = realloc(string, allocated *STRING_ALLOCATION_INDEX);

      if (!new_string)
      {
        free(string);

        return ALLOCATION_ERROR;
      }

      string = new_string;
      allocated *= STRING_ALLOCATION_INDEX;
    }

    string[len++] = c;
    string[len] = '\0';
    fsf_response = fscanf(f, "%c", &c);
  }

  if (ferror(f))
  {
    free(string);

    return READ_ERROR;
  }

  if (len == 0)
  {
    free(string);

    return NO_STRING;
  }

  size_t i = 0;
  for (; string[i] && !isalpha(string[i]); i++);

  if (!string[i])
  {
    free(string);

    return BLANK_STRING;
  }

  dst->string = string;
  dst->allocated = allocated;

  return OK;
}

void free_string_t(string_t *string)
{
  free(string->string);
}

void print_string_t(FILE *f, string_t *string)
{
  fprintf(f, "%s\n", string->string);
}
