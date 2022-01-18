#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

#include "graph.h"
#include "tick.h"

void skip_stdin(void)
{
    int c;
    do
    {
        c = getchar();
    }
    while (c != '\n' && c != EOF);
}

int get_choice(int minimum_value, int maximum_value)
{
  int choice;
  int got_choice = 0;

  while (!got_choice)
  {
    printf("Введите целое от %d до %d:\n", minimum_value, maximum_value);

    if (!scanf("%d", &choice))
    {
      printf("Введено неверное число. Повторите ввод.");
      skip_stdin();
      continue;
    }

    if (choice < minimum_value || choice > maximum_value)
    {
      printf("Введено неверное число. Повторите ввод.");
      skip_stdin();
      continue;
    }

    got_choice = 1;
  }

  return choice;
}

int main(int argc, char **argv)
{
  setbuf(stdout, NULL);

  if (2 != argc){
    printf("Что-то не так с аргументами командной строки.\n");
    printf("Требуется перезапуск программы с правильным именем исходного файла.\n");
    return 1;
  }

  graph_t *graph = createGraph(argv[1]);
  if (!graph){
    printf("Что-то не так с аргументами командной строки.\n");
    printf("Требуется перезапуск программы с правильным именем исходного файла.\n");
    return 1;
  }

  size_t w = sizeof(graph_t) + graph->size * sizeof(int*) + graph->size * graph->size * sizeof(int);
  printf("Память требуемая для хранения графа: %d (в байтах)\n", (int) w);

  printf("Был сгенерирован svg файл с представлением введенного графа:\n");
  createDotFile(graph, "graph.txt");
  system("dot -Tsvg -o graph.svg ./graph.txt");
  system("start ./graph.svg");

  printf("Введите индекс вершины, для которой будет проверяться условие:\n");

  int bi = get_choice(0, graph->size - 1);

  printf("Введите максимальную длину пути:\n");

  int mrl = get_choice(1, INT_MAX);

  int64_t t1, t2;

  t1 = tick();
  graph_t *solution = _findSolution(graph, bi, mrl);
  t2 = tick();

  printf("Время выполнения алгоритма: %"PRIu64" (тактов процессора).\n", t2 - t1);

  if (!solution){
    printf("Программой определено, что условие задачи не выполняется.\n");
    printf("Успешное завершение программы.\n");
    return 1;
  }

  printf("Программой определено, что условие задачи выполняется.\n");

  printf("Был сгенерирован svg файл с представлением графа-решения:\n");
  createDotFile(solution, "solution.txt");
  system("dot -Tsvg -o solution.svg ./solution.txt");
  system("start ./solution.svg");

  printf("Успешное завершение программы.\n");

  freeGraph(graph);
  freeGraph(solution);

  return 0;
}
