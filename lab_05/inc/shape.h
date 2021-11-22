#ifndef SHAPE_H
#define SHAPE_H

#define STATISTICS_FILE_NAME "statistics.txt"
#define LINE_LEN 1024
typedef char line_t[LINE_LEN];

void skip_stdin(void);
void print_line(void);
int handle_manu(void);

#endif
