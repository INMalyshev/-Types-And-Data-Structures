#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

int main(void)
{
  setbuf(stdout, NULL);

  graph_t *graph = new(6);
  graph->graph[0][1] = 7;
  graph->graph[1][0] = 7;
  graph->graph[0][2] = 9;
  graph->graph[2][0] = 9;
  graph->graph[0][5] = 14;
  graph->graph[5][0] = 14;
  graph->graph[1][2] = 10;
  graph->graph[2][1] = 10;
  graph->graph[1][3] = 15;
  graph->graph[3][1] = 15;
  graph->graph[2][3] = 11;
  graph->graph[3][2] = 11;
  graph->graph[2][5] = 2;
  graph->graph[5][2] = 2;
  graph->graph[3][4] = 6;
  graph->graph[4][3] = 6;
  graph->graph[4][5] = 9;
  graph->graph[5][4] = 9;

  int *res = dijkstra(graph, 0);

  for (int i = 0; i < graph->size; i++)
    printf("%d\n", res[i]);

  return 0;
}
