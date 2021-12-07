#include <stdlib.h>
#include <stdio.h>

#include <text_file.h>

int create_tf_t(char *filename, tf_t *textfile)
{
  FILE *f = fopen(filename, "rt");
  if (!f) return 1;

  int nmemb;
  if (!fscanf(f, "%d", &nmemb)) return 1;

  int *data = calloc(nmemb, sizeof(int));

  for (int i = 0; i < nmemb; i++)
  {
    if (!fscanf(f, "%d", data + i)) return 1;
  }

  fclose(f);

  textfile->filename = filename;
  textfile->len = nmemb;
  textfile->data = data;

  return 0;
}

int delete_tf_t(tf_t *textfile, int alpha)
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

void pri_tf_t(tf_t *tf)
{
  printf("Text file content:\n\n");

  if (tf->len == 0)
  {
    printf("Emty file.\n");
    return;
  }

  for (int i = 0; i < tf->len; i++)
  {
    printf("%d\n", tf->data[i]);
  }
}
