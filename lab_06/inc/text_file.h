#ifndef TF_H
#define TF_H

typedef struct
{
  char *filename;
  int len;
  int *data;
} text_file_t;

text_file_t *create_text_file_t(char *filename);
int delete_text_file_t(text_file_t *textfile, int alpha);
void pri_text_file_t(text_file_t *tf);
int find_text_file_t(text_file_t *text_file, int key);
void insert_text_file_t(text_file_t *text_file, int key);

#endif
