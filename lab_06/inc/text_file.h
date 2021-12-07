#ifndef TF_H
#define TF_H

typedef struct
{
  char *filename;
  int len;
  int *data;
} tf_t;

int create_tf_t(char *filename, tf_t *textfile);
int delete_tf_t(tf_t *textfile, int alpha);
void pri_tf_t(tf_t *tf);

#endif
