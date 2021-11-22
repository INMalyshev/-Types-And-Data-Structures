#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "array_queue.h"
#include "simulation.h"
#include "queue.h"
#include "shape.h"
#include "tick.h"
#include "rc.h"

void skip_stdin(void)
{
    int c;
    do
    {
        c = getchar();
    }
    while (c != '\n' && c != EOF);
}

void print_wellcome_menu(void)
{
  printf(" 1. [ОЧЕРЕДЬ-СПИСОК] Провести моделированиие;\n");
  printf(" 2. [ОЧЕРЕДЬ-МАССИВ] Провести моделированиие;\n");
  printf(" 3. Сгенерировать статистику по работе двух реализаций очереди;\n");
  printf("\n");
  printf(" 0. Выход.\n");
}

int handle_manu(void)
{
  print_line();
  print_wellcome_menu();
  print_line();

  int choice;

  int got_choice = 0;

  while (!got_choice)
  {
    if (!scanf("%d", &choice))
    {
      printf("Неправильный ввод. Запрос на повторный ввод:\n");
      skip_stdin();
      continue;
    }
    if (choice < 0 || choice > 3)
    {
      printf("Неправильный ввод. Запрос на повторный ввод:\n");
      continue;
    }
    got_choice = 1;
  }

  print_line();

  switch (choice)
  {
    case 0:
    {
      return EXIT;
    };
    case 1:
    {
      int ch;
      int gch = 0;
      while (!gch)
      {
        printf("1. Указать параметры симуляции;\n");
        printf("2. Использовать настроики по умолчанию.\n");

        if (!scanf("%d", &ch))
        {
          printf("Пункт выбран неверно. Повторите ввод.\n");
          skip_stdin();
          continue;
        }

        if (ch < 1 || ch > 2)
        {
          printf("Пункт выбран неверно. Повторите ввод.\n");
          skip_stdin();
          continue;
        }

        gch = 1;
      }

      if (ch == 1)
      {
        int flag = 0;
        int t1_1, t1_2, t2_1, t2_2, n;
        double p;

        while (!flag)
        {
          printf("Введите 2 чисел:\n");
          printf("1. Минимальное время появления новой заявки (Целое неотрицательное число);\n");
          printf("2. Максимальное время появления новой заявки (Целое неотрицательное число);\n");

          if (2 != scanf("%d%d", &t1_1, &t1_2))
          {
            printf("Введены неверные данные. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          if (t1_1 > t1_2 || t1_1 < 0 || t1_2 < 0)
          {
            printf("Введены неверные данные. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          if (t1_2 == 0)
          {
            printf("Время появления заявки не может быть нулевым. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          flag = 1;
        }

        flag = 0;

        while (!flag)
        {
          printf("Введите 2 чисел:\n");
          printf("1. Минимальное время обработки заявки (Целое неотрицательное число);\n");
          printf("2. Максимальное время обработки заявки (Целое неотрицательное число);\n");

          if (2 != scanf("%d%d", &t2_1, &t2_2))
          {
            printf("Введены неверные данные. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          if (t2_1 > t2_2 || t2_1 < 0 || t2_2 < 0)
          {
            printf("Введены неверные данные. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          if (t2_2 == 0)
          {
            printf("Время обработки заявки не может быть нулевым. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          flag = 1;
        }

        flag = 0;

        while (!flag)
        {
          printf("Введите количество вышедших из системы запросов до завершения симуляции (Целое неотрицательное число <= 10000);\n");

          if (1 != scanf("%d", &n))
          {
            printf("Введены неверные данные. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          if (n < 0 || n > 10000)
          {
            printf("Введены неверные данные. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          flag = 1;
        }

        flag = 0;

        while (!flag)
        {
          printf("Введите вероятность того, что заявка, после обработки, останется в системе (действительное (0,1)).\n");

          if (1 != scanf("%lf", &p))
          {
            printf("Введены неверные данные. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          if (p <= 0.0 || p >= 1.0)
          {
            printf("Введены неверные данные. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          flag = 1;
        }

        srand(tick());
        simulate_with_queue(t1_1, t1_2, t2_1, t2_2, p, n);

        return OK;
      }

      if (ch == 2)
      {
        srand(tick());
        simulate_with_queue(T1_1, T1_2, T1_1, T2_2, P, REQUIRED_REQUESTS_OUT);
        return OK;
      }

      return OK;
    };

    case 2:
    {
      int ch;
      int gch = 0;
      while (!gch)
      {
        printf("1. Указать параметры симуляции;\n");
        printf("2. Использовать настроики по умолчанию.\n");

        if (!scanf("%d", &ch))
        {
          printf("Пункт выбран неверно. Повторите ввод.\n");
          skip_stdin();
          continue;
        }

        if (ch < 1 || ch > 2)
        {
          printf("Пункт выбран неверно. Повторите ввод.\n");
          skip_stdin();
          continue;
        }

        gch = 1;
      }

      if (ch == 1)
      {
        int flag = 0;
        int t1_1, t1_2, t2_1, t2_2, n;
        double p;

        while (!flag)
        {
          printf("Введите 2 чисел:\n");
          printf("1. Минимальное время появления новой заявки (Целое неотрицательное число);\n");
          printf("2. Максимальное время появления новой заявки (Целое неотрицательное число);\n");

          if (2 != scanf("%d%d", &t1_1, &t1_2))
          {
            printf("Введены неверные данные. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          if (t1_1 > t1_2 || t1_1 < 0 || t1_2 < 0)
          {
            printf("Введены неверные данные. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          if (t1_2 == 0)
          {
            printf("Время появления заявки не может быть нулевым. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          flag = 1;
        }

        flag = 0;

        while (!flag)
        {
          printf("Введите 2 чисел:\n");
          printf("1. Минимальное время обработки заявки (Целое неотрицательное число);\n");
          printf("2. Максимальное время обработки заявки (Целое неотрицательное число);\n");

          if (2 != scanf("%d%d", &t2_1, &t2_2))
          {
            printf("Введены неверные данные. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          if (t2_1 > t2_2 || t2_1 < 0 || t2_2 < 0)
          {
            printf("Введены неверные данные. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          if (t2_2 == 0)
          {
            printf("Время появления заявки не может быть нулевым. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          flag = 1;
        }

        flag = 0;

        while (!flag)
        {
          printf("Введите количество вышедших из системы запросов до завершения симуляции (Целое неотрицательное число <= 10000);\n");

          if (1 != scanf("%d", &n))
          {
            printf("Введены неверные данные. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          if (n < 0 || n > 10000)
          {
            printf("Введены неверные данные. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          flag = 1;
        }

        flag = 0;

        while (!flag)
        {
          printf("Введите вероятность того, что заявка, после обработки, останется в системе (действительное (0,1)).\n");

          if (1 != scanf("%lf", &p))
          {
            printf("Введены неверные данные. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          if (p <= 0.0 || p >= 1.0)
          {
            printf("Введены неверные данные. Повториите ввод.\n");
            skip_stdin();
            continue;
          }

          flag = 1;
        }

        srand(tick());
        simulate_with_array_queue(t1_1, t1_2, t2_1, t2_2, p, n);

        return OK;
      }

      if (ch == 2)
      {
        srand(tick());
        simulate_with_array_queue(T1_1, T1_2, T1_1, T2_2, P, REQUIRED_REQUESTS_OUT);
        return OK;
      }

      return OK;
    };

    case 3:
    {
      int len, glen = 0;
      while (!glen)
      {
        printf("Введите начальную длину очереди:\n");

        if (!scanf("%d", &len))
        {
          printf("Введены неверные данные. Попторите ввод.\n");
          skip_stdin();
          continue;
        }

        if (len < 0 || len > 10000)
        {
          printf("Введены неверные данные. Попторите ввод.\n");
          skip_stdin();
          continue;
        }

        glen = 1;
      }

      printf("\nОчередь-список:\n\n");

      queue_t queue = {NULL, 0};
      int64_t t1, t2, push_sum = 0, pop_sum = 0;

      for (int i = 0; i < len; i++)
      {
        push_queue_t(&queue, NULL);
      }

      for (size_t i = 0; i < 1000; i++)
      {
        t1 = tick();
        push_queue_t(&queue, NULL);
        t2 = tick();
        push_sum += t2 - t1;

        t1 = tick();
        pop_queue_t(&queue);
        t2 = tick();
        pop_sum += t2 - t1;
      }

      size_t size = sizeof(queue_t) + sizeof(queue_note_t) * len;

      printf("  Среднее время добавления элемента: %d (в тактах)\n", (int) (push_sum / 1000));
      printf("  Среднее время извлечения элемента: %d (в тактах)\n", (int) (pop_sum / 1000));
      printf("  Память затраченая на хранение структуры: %d (в байтах)\n", (int) size);

      printf("\nОчередь-мвссив:\n\n");

      array_queue_t *array_queue = new_array_queue_t();
      push_sum = 0;
      pop_sum = 0;

      for (int i = 0; i < len; i++)
      {
        push_array_queue_t(array_queue, NULL);
      }

      for (size_t i = 0; i < 1000; i++)
      {
        t1 = tick();
        push_array_queue_t(array_queue, NULL);
        t2 = tick();
        push_sum += t2 - t1;

        t1 = tick();
        pop_array_queue_t(array_queue);
        t2 = tick();
        pop_sum += t2 - t1;
      }

      size = sizeof(void*) * len;

      printf("  Среднее время добавления элемента: %d (в тактах)\n", (int) (push_sum / 1000));
      printf("  Среднее время извлечения элемента: %d (в тактах)\n", (int) (pop_sum / 1000));
      printf("  Память затраченая на хранение структуры: %d (в байтах)\n\n", (int) size);

      return OK;
    };
  }


  return ERROR;
}

void print_line(void)
{
  printf("|------------------------------------------------------|\n");
}
