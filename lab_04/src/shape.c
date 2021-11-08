#include <stdio.h>
#include <stdlib.h>

#include "rc.h"
#include "stec.h"
#include "mystring.h"
#include "shape.h"

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
  printf("1. [СТЕК] Прочитать элементы стека из файла;\n");
  printf("2. [СТЕК] Добавить элемент в стек (push);\n");
  printf("3. [СТЕК] Удалить элемент из стека (pop);\n");
  printf("4. [СТЕК] Ввести состояние стека;\n");
  printf("5. [СТЕК] Вывести список освобожденных областей;\n");
  printf("6. [СТЕК] Очистить стек;\n");
  printf("7. [СТЕК] Сбросить список освобожденных обласей;\n");

  printf("0. Выход.\n");
}

int handle_manu(base_t *data_base)
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
    if (choice < 0 || choice > 7)
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
      clear_stec_t(data_base->stec);
      free(data_base->stec);
      return EXIT;
    };
    case 1:
    {
      return EXIT;
    };
    case 2:
    {
      printf("Введите слово:\n");

      string_t *string = malloc(sizeof(string_t));
      if (!string) return ALLOCATION_ERROR;

      int got_string = 0;

      while (!got_string)
      {
        if  (OK != scan_string_t(string, stdin))
        {
          printf("Слово введено неверно. Повторите ввод:\n");
          continue;
        }
        got_string = 1;
      }

      if (!push_stec_t(data_base->stec, string))
        return ALLOCATION_ERROR;

      return OK;
    };
    case 3:
    {
      pop_stec_t(data_base->stec);
      return OK;
    };
    case 4:
    {
      print_stec_t(stdout, data_base->stec, (void(*) (FILE*, void*)) print_string_t);
      return OK;
    };
    case 5:
    {
      return EXIT;
    };
    case 6:
    {
      clear_stec_t(data_base->stec);
      return OK;
    };
    case 7:
    {
      return EXIT;
    };
  }

  return ERROR;
}

void print_line(void)
{
  printf("|------------------------------------------------------|\n");
}
