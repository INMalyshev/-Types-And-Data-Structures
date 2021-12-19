#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph graph_t;
struct graph
{
  int size;
  int **graph;
};

graph_t *newGraph(int size);
void freeGraph(graph_t *graph);
int *dijkstra(graph_t *graph, int bi);

int _conditional(graph_t *graph, int bi, int mrl);
int _inGraph(graph_t *graph, int ci, int cj);
graph_t *_copy(graph_t *graph);
void _set(graph_t *graph, int ci, int cj, int value);
graph_t *_findSolution(graph_t *graph, int bi, int mrl);

void createDotFile(graph_t *graph, char *dotFileName);
graph_t *createGraph(char *fileName);

#endif
