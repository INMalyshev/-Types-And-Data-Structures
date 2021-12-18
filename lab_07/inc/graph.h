#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph graph_t;
struct graph
{
  int size;
  int **graph;
};

graph_t *new(int size);
void freeGraph(graph_t *graph);
int *dijkstra(graph_t *graph, int bi);

#endif
