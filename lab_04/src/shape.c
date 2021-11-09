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
  printf("1. [СТЕК] Добавить элемент в стек (push);\n");
  printf("2. [СТЕК] Удалить элемент из стека (pop);\n");
  printf("3. [СТЕК] Вывести состояние стека;\n");
  printf("4. [СТЕК] Вывести список освобожденных областей;\n");
  printf("5. [СТЕК] Очистить стек;\n");
  printf("6. [СТЕК] Сбросить список освобожденных обласей;\n");

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
    if (choice < 0 || choice > 6)
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
      string_t *string = malloc(sizeof(string_t));
      if (!string) return ALLOCATION_ERROR;

      printf("Введите слово:\n");
      scan_string_t(string, stdin);

      int got_string = 0;

      while (!got_string)
      {
        if  (OK != scan_string_t(string, stdin))
        {
          printf("Ошибка ввода. Введите слово заново:\n");
          continue;
        }
        got_string = 1;
      }

      if (!push_stec_t(data_base->stec, string))
        return ALLOCATION_ERROR;

      return OK;
    };
    case 2:
    {
      if (0 == data_base->stec->stec_len)
      {
        printf("СТЕК пуст!\n");
        return OK;
      }
      push_list_t(data_base->stec_deallocated_memory, data_base->stec->current_note->data);
      pop_stec_t(data_base->stec);
      return OK;
    };
    case 3:
    {
      if (0 == data_base->stec->stec_len)
      {
        printf("СТЕК пуст!\n");
        return OK;
      }
      print_stec_t(stdout, data_base->stec, (void(*) (FILE*, void*)) print_string_t);
      return OK;
    };
    case 4:
    {
      if (0 == data_base->stec_deallocated_memory->len)
      {
        printf("Список освобожденных областей пуст.\n");
        return OK;
      }
      print_list_t(data_base->stec_deallocated_memory);
      return OK;
    };
    case 5:
    {
      if (0 == data_base->stec->stec_len)
      {
        printf("СТЕК пуст!\n");
        return OK;
      }

      do
      {
        if (data_base->stec->current_note)
          push_list_t(data_base->stec_deallocated_memory, data_base->stec->current_note->data);
      } while(OK == pop_stec_t(data_base->stec));

      return OK;
    };
    case 6:
    {
      free_list_t(data_base->stec_deallocated_memory);
      data_base->stec_deallocated_memory = new_list_t();
      return OK;
    };
  }

  return ERROR;
}

void print_line(void)
{
  printf("|------------------------------------------------------|\n");
}

int push_list_t(list_t* list, void* data)
{
  if (list->len >= list->allocated)
  {
    void **new_dm = realloc(list->deallocated_memory, sizeof(void*) * list->allocated * ALLOCATION_INDEX_LIST_T);
    if (!new_dm)
    {
      free(list->deallocated_memory);
      return ALLOCATION_ERROR;
    }
    list->deallocated_memory = new_dm;
    list->allocated *= ALLOCATION_INDEX_LIST_T;
  }

  list->deallocated_memory[list->len++] = data;

  return OK;
}

void free_list_t(list_t* list)
{
  free(list->deallocated_memory);
  free(list);
}

void print_list_t(list_t* list)
{
  for (size_t i = 0; i < list->len; i++)
    printf("<%p>\n", (void*) list->deallocated_memory[i]);
}

list_t *new_list_t(void)
{
  void **data = calloc(INITIAL_LIST_T_ALLOCATION, sizeof(void*));
  if (!data) return NULL;
  list_t *new = malloc(sizeof(list_t));
  if (!new)
  {
    free(data);
    return NULL;
  }
  new->deallocated_memory = data;
  new->len = 0;
  new->allocated = INITIAL_LIST_T_ALLOCATION;
  return new;
}
