#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "graph.h"

graph_t *new(int size)
{
  graph_t *new = malloc(sizeof(graph_t));

  new->size = size;
  new->graph = malloc(size * sizeof(int*));

  for (int i = 0; i < size; i++)
    new->graph[i] = malloc(size * sizeof(int));

  return new;
}

void freeGraph(graph_t *graph)
{
  for (int i = 0; i < graph->size; i++)
    free(graph->graph[i]);
  free(graph->graph);
  free(graph);
}

int *dijkstra(graph_t *graph, int bi)
{
    int *d = malloc(graph->size * sizeof(int)); // min distance
    int *v = malloc(graph->size * sizeof(int)); // visited nodes

    for (int i = 0; i < graph->size; i++){
      d[i] = (i != bi) ? INT_MAX : 0;
      v[i] = 1;
    }

    int minindex, min, temp;

    // Шаг алгоритма
    do {
      minindex = INT_MAX;
      min = INT_MAX;
      for (int i = 0; i<graph->size; i++)
      { // Если вершину ещё не обошли и вес меньше min
        if ((v[i] == 1) && (d[i]<min))
        { // Переприсваиваем значения
          min = d[i];
          minindex = i;
        }
      }
      // Добавляем найденный минимальный вес
      // к текущему весу вершины
      // и сравниваем с текущим минимальным весом вершины
      if (minindex != INT_MAX)
      {
        for (int i = 0; i<graph->size; i++)
        {
          if (graph->graph[minindex][i] > 0)
          {
            temp = min + graph->graph[minindex][i];
            if (temp < d[i])
            {
              d[i] = temp;
            }
          }
        }
        v[minindex] = 0;
      }
    } while (minindex < INT_MAX);

    free(v);

    return d;
}
