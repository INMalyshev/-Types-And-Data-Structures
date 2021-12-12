#include <stdlib.h>
#include <stdio.h>

#include <text_file.h>

text_file_t *create_text_file_t(char *filename)
{
  FILE *f = fopen(filename, "rt");
  if (!f) return NULL;

  int nmemb;
  if (!fscanf(f, "%d", &nmemb)) return NULL;

  text_file_t *textfile = malloc(sizeof(text_file_t));
  int *data = calloc(nmemb, sizeof(int));

  for (int i = 0; i < nmemb; i++)
  {
    if (!fscanf(f, "%d", data + i)) return NULL;
  }

  fclose(f);

  textfile->filename = filename;
  textfile->len = nmemb;
  textfile->data = data;

  return textfile;
}

int delete_text_file_t(text_file_t *textfile, int alpha)
{
  for (int i = 0; i < textfile->len; i++)
  {
    if (textfile->data[i] == alpha)
    {
      printf("\nNumber of comparisons: %d\n\n", i + 1);

      for (int j = i; j < textfile->len - 1; j++)
      {
        textfile->data[i] = textfile->data[i+1];
      }
      textfile->len -= 1;

      FILE *f = fopen(textfile->filename, "wt");
      if (!f) return 1;

      fprintf(f, "%d\n", textfile->len);
      for (int k = 0; i < textfile->len; k++)
      {
        fprintf(f, "%d\n", textfile->data[i]);
      }

      fclose(f);

      return 0;
    }
  }

  printf("Nothing found.\n");

  return 0;
}

void pri_text_file_t(text_file_t *tf)
{
  printf("Text file content:\n\n");

  if (tf->len == 0)
  {
    printf("Emty file.\n");
    return;
  }

  for (int i = 0; i < tf->len; i++)
  {
    printf("<index: %d> <value: %d>\n", i, tf->data[i]);
  }
}
