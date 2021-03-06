#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "graph.h"

graph_t *newGraph(int size)
{
  graph_t *new = malloc(sizeof(graph_t));

  new->size = size;
  new->graph = malloc(size * sizeof(int*));

  for (int i = 0; i < size; i++)
    new->graph[i] = calloc(size, sizeof(int));

  return new;
}

void freeGraph(graph_t *graph)
{
  if (graph)
  {
    if (graph->graph)
    {
      for (int i = 0; i < graph->size; i++)
        free(graph->graph[i]);
    }
    free(graph->graph);
  }

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

int _conditional(graph_t *graph, int bi, int mrl)
{
  int *result = dijkstra(graph, bi);

  for (int i = 0; i < graph->size; i++)
    if (result[i] > mrl)
      {
        free(result);
        return 0;
      }

  free(result);
  return 1;
}

int _inGraph(graph_t *graph, int ci, int cj)
{
  if (graph->graph[ci][cj] && graph->graph[ci][cj])
    return 1;
  return 0;
}

graph_t *_copy(graph_t *graph)
{
  graph_t *new = newGraph(graph->size);
  for (int i = 0; i < graph->size; i++)
    for (int j = 0; j < graph->size; j++)
      new->graph[i][j] = graph->graph[i][j];

  return new;
}

void _set(graph_t *graph, int ci, int cj, int value)
{
  graph->graph[ci][cj] = value;
  graph->graph[cj][ci] = value;
}

graph_t *_findSolution(graph_t *graph, int bi, int mrl)
{
  if (_conditional(graph, bi, mrl))
    return _copy(graph);

  graph_t *processing = _copy(graph);

  for (int fi = 0; fi < graph->size; fi++){
    for (int fj = 0; fj < graph->size; fj++){

      if (fi == fj)
        continue;
      if (_inGraph(processing, fi, fj))
        continue;
      _set(processing, fi, fj, 1);
      if (_conditional(processing, bi, mrl))
        return processing;

      for (int si = fi; si < graph->size; si++){
        for (int sj = fj; sj < graph->size; sj++){

          if (si == sj)
            continue;
          if (_inGraph(processing, si, sj))
            continue;
          _set(processing, si, sj, 1);
          if (_conditional(processing, bi, mrl))
            return processing;

          for (int ti = si; ti < graph->size; ti++){
            for (int tj = sj; tj < graph->size; tj++){

              if (ti == tj)
                continue;
              if (_inGraph(processing, ti, tj))
                continue;
              _set(processing, ti, tj, 1);
              if (_conditional(processing, bi, mrl))
                return processing;

              _set(processing, ti, tj, 0);
            }
          }

          _set(processing, si, sj, 0);
        }
      }

      _set(processing, fi, fj, 0);
    }
  }

  freeGraph(processing);
  return NULL;
}

void createDotFile(graph_t *graph, char *dotFileName)
{
  FILE *f = fopen(dotFileName, "wt");

  fprintf(f, "graph G {\n");

  for (int i = 0; i < graph->size; i++)
    fprintf(f, "  %d;\n", i);

  for (int i = 0; i < graph->size; i++){
    for (int j = i; j < graph->size; j++){
      if (graph->graph[i][j] && graph->graph[j][i]){
        fprintf(f, "  %d -- %d;\n", i, j);
      }
    }
  }

  fprintf(f, "}\n");

  fclose(f);
}

graph_t *createGraph(char *fileName)
{
  FILE *f = fopen(fileName, "rt");
  if (!f) return NULL;

  int dotAmount, rootAmount;
  if (!fscanf(f, "%d", &dotAmount)) return NULL;
  if (dotAmount < 3) return NULL;
  if (!fscanf(f, "%d", &rootAmount)) return NULL;
  if (rootAmount < 0) return NULL;

  graph_t *graph = newGraph(dotAmount);

  int a, b;

  for (int i = 0; i < rootAmount; i++){
    if (!fscanf(f, "%d", &a)) return NULL;
    if (a < 0 || a >= dotAmount) return NULL;
    if (!fscanf(f, "%d", &b)) return NULL;
    if (b < 0 || b >= dotAmount) return NULL;
    _set(graph, a, b, 1);
  }

  return graph;
}
