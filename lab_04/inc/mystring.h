#ifndef MYSTRING_H
#define MYSTRING_H

#define INITIAL_STRING_LEN 1
#define STRING_ALLOCATION_INDEX 2

#define GOT_ONE_CHAR 1

typedef struct
{
  char *string;
  size_t allocated;
} string_t;

#endif
