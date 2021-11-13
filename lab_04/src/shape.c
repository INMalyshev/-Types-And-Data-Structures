#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "rc.h"
#include "stec.h"
#include "array_stec.h"
#include "mystring.h"
#include "shape.h"
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

void print_wellcome_menu(void)
{
  printf(" 1. [СПИСОК] Добавить элемент в стек (push);\n");
  printf(" 2. [СПИСОК] Удалить элемент из стека (pop);\n");
  printf(" 3. [СПИСОК] Вывести состояние стека;\n");
  printf(" 4. [СПИСОК] Вывести список освобожденных областей;\n");
  printf(" 5. [СПИСОК] Очистить стек;\n");
  printf(" 6. [СПИСОК] Сбросить список освобожденных обласей;\n");
  printf(" 7. [СПИСОК] Распечатать слова в обратном порядке в перевернутом виде;\n");
  printf("\n");
  printf(" 8. [МАССИВ] Добавить элемент в стек (push);\n");
  printf(" 9. [МАССИВ] Удалить элемент из стека (pop);\n");
  printf("10. [МАССИВ] Вывести состояние стека;\n");
  printf("11. [МАССИВ] Вывести список освобожденных областей;\n");
  printf("12. [МАССИВ] Сбросить стек;\n");
  printf("13. [МАССИВ] Сбросить список освобожденных обласей;\n");
  printf("14. [МАССИВ] Распечатать слова в обратном порядке в перевернутом виде;\n");
  printf("\n");
  printf("15. Сгенерировать статистику по одной размерности;\n");
  printf("16. Вывести готовую статистику из файла ('statistics.txt');\n");
  printf("\n");
  printf(" 0. Выход.\n");
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
    if (choice < 0 || choice > 16)
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
      if (data_base->array_stec)
      {
        free_array_stec_t(data_base->array_stec);
      }
      free_list_t(data_base->stec_deallocated_memory);
      free_list_t(data_base->array_stec_deallocated_memory);
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
    case 7:
    {
      if (0 == data_base->stec->stec_len)
      {
        printf("СТЕК пуст!\n");
        return OK;
      }

      uint64_t t1 = tick();
      solve_case_stec_t(stdout, data_base->stec);
      uint64_t t2 = tick();

      printf("\nВремя выполнения пункта (в тактах) : %"PRIu64"\n", t2 - t1);

      return OK;
    }
    case 8:
    {
      if (!data_base->array_stec)
      {
        printf("Необходимо инициализировать стек. Введите максимальную длину стека (не более %d).\n", MAX_ARRAY_STEC_LEN);

        int nmemb;
        int got_nmemb = 0;

        while (!got_nmemb)
        {
          if (!scanf("%d", &nmemb))
          {
            printf("Целое положительное число введено неверно. Повторите ввод:\n");
            skip_stdin();
            got_nmemb = 0;
            continue;
          }

          if (nmemb < 1 || nmemb > MAX_ARRAY_STEC_LEN)
          {
            printf("Целое положительное число от 0 до %d введено неверно. Повторите ввод:\n", MAX_ARRAY_STEC_LEN);
            skip_stdin();
            got_nmemb = 0;
            continue;
          }

          got_nmemb = 1;
        }

        data_base->array_stec = new_array_stec_t((size_t) nmemb);
      }

      if (data_base->array_stec->end_pointer == data_base->array_stec->current_position_pointer)
      {
        printf("СТЕК переполнен.\n");
        return OK;
      }

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

      if (OK != push_array_stec_t(data_base->array_stec, string))
      {
        return ALLOCATION_ERROR;
      }

      return OK;
    };
    case 9:
    {
      if (!data_base->array_stec)
      {
        printf("Необходимо инициализировать стек. Сначала обратитесь к пункту 8.\n");
        return OK;
      }

      if (data_base->array_stec->start_pointer == data_base->array_stec->current_position_pointer)
      {
        printf("СТЕК пуст!\n");
        return OK;
      }

      push_list_t(data_base->array_stec_deallocated_memory, *(data_base->array_stec->current_position_pointer - 1));
      pop_array_stec_t(data_base->array_stec);

      return OK;
    };
    case 10:
    {
      if (!data_base->array_stec)
      {
        printf("Необходимо инициализировать стек. Сначала обратитесь к пункту 8.\n");
        return OK;
      }

      if (data_base->array_stec->start_pointer == data_base->array_stec->current_position_pointer)
      {
        printf("СТЕК пуст!\n");
        return OK;
      }

      print_array_stec_t(stdout, data_base->array_stec, (void(*) (FILE*, void*)) print_string_t);

      return OK;
    };
    case 11:
    {
      if (0 == data_base->array_stec_deallocated_memory->len)
      {
        printf("Список освобожденных областей пуст.\n");
        return OK;
      }
      print_list_t(data_base->array_stec_deallocated_memory);
      return OK;
    };
    case 12:
    {
      if (data_base->array_stec)
      {
        void **cp = data_base->array_stec->current_position_pointer - 1;

        for (; cp >= data_base->array_stec->start_pointer; cp--)
          push_list_t(data_base->array_stec_deallocated_memory, *cp);

        free_array_stec_t(data_base->array_stec);
        data_base->array_stec = NULL;
      }

      return OK;
    };
    case 13:
    {
      free_list_t(data_base->array_stec_deallocated_memory);
      data_base->array_stec_deallocated_memory = new_list_t();
      return OK;
    };
    case 14:
    {
      if (!data_base->array_stec)
      {
        printf("Необходимо инициализировать стек. Сначала обратитесь к пункту 8.\n");
        return OK;
      }

      if (data_base->array_stec->start_pointer == data_base->array_stec->current_position_pointer)
      {
        printf("СТЕК пуст!\n");
        return OK;
      }

      uint64_t t1 = tick();
      solve_case_array_stec_t(stdout, data_base->array_stec);
      uint64_t t2 = tick();

      printf("\nВремя выполнения пункта (в тактах) : %"PRIu64"\n", t2 - t1);

      return OK;
    };
    case 15:
    {
      int got_sq_len = 0;
      int sq_len;

      FILE *f = fopen("rubbish.txt", "wt");

      printf("Введите количество повторений замеров (от %d до %d) :\n", MIN_REPITIONS_AMOUNT, MAX_REPITIONS_AMOUNT);

      while (!got_sq_len)
      {
        if (!scanf("%d", &sq_len))
        {
          skip_stdin();
          printf("Неверно введено количество замеров. Повторите ввод:\n");
          got_sq_len = 0;
          continue;
        }

        if (sq_len > MAX_REPITIONS_AMOUNT || sq_len < MIN_REPITIONS_AMOUNT)
        {
          skip_stdin();
          printf("Неверно введено количество замеров. Повторите ввод:\n");
          got_sq_len = 0;
          continue;
        }

        got_sq_len = 1;
      }

      int got_stec_len = 0;
      int stec_len;

      printf("Введите размер стеков для замеров (от %d до %d) :\n", MIN_STEC_LEN, MAX_STEC_LEN);

      while (!got_stec_len)
      {
        if (!scanf("%d", &stec_len))
        {
          skip_stdin();
          printf("Неверно введен размер стека. Повторите ввод:\n");
          got_stec_len = 0;
          continue;
        }

        if (stec_len > MAX_STEC_LEN || stec_len < MIN_STEC_LEN)
        {
          skip_stdin();
          printf("Неверно введен размер стека. Повторите ввод:\n");
          got_stec_len = 0;
          continue;
        }

        got_stec_len = 1;
      }

      uint64_t total_stec_time = 0;
      uint64_t total_array_stec_time = 0;

      uint64_t t1, t2;

      string_t data = {TEST_STRING, sizeof(TEST_STRING) + 1};

      for (int i = 0; i < sq_len; i++)
      {

        stec_t *stec = new_stec_t();
        array_stec_t *array_stec = new_array_stec_t((size_t) stec_len);


        for (int i = 0; i < stec_len; i++)
        {
            push_stec_t(stec, &data);
            push_array_stec_t(array_stec, &data);
        }


        t1 = tick();
        solve_case_stec_t(f, stec);
        t2 = tick();
        total_stec_time += t2 - t1;


        t1 = tick();
        solve_case_array_stec_t(f, array_stec);
        t2 = tick();
        total_array_stec_time += t2 - t1;



        free(array_stec->start_pointer);
        free(array_stec);

        stec_note_t* p = stec->current_note;
        while (p)
        {
          stec_note_t* np = p->previous;
          free(p);
          p = np;
        }
        free(stec);
        fclose(f);

      }

      uint64_t average_stec_time = total_stec_time / sq_len;
      uint64_t average_array_stec_time = total_array_stec_time / sq_len;

      size_t used_bytes_amount_stec_t = sizeof(stec_t) + sizeof(stec_note_t) * ((size_t) stec_len);
      size_t used_bytes_amount_array_stec_t = sizeof(array_stec_t) + sizeof(void*) * ((size_t) stec_len);

      printf("\n");
      printf("На %d повторениях для СТЕКа среднее время получилось: %"PRIu64" (в тактах)\n", sq_len, average_stec_time);
      printf("Затраченная память (без учета памяти, необходимой для хранения строк) : %zu (в байтах)\n", used_bytes_amount_stec_t);
      printf("\n");
      printf("На %d повторениях для МАССИВАа среднее время получилось: %"PRIu64" (в тактах)\n", sq_len, average_array_stec_time);
      printf("Затраченная память (без учета памяти, необходимой для хранения строк) : %zu (в байтах)\n", used_bytes_amount_array_stec_t);

      return OK;
    };
    case 16:
    {
      FILE *f = fopen(STATISTICS_FILE_NAME, "rt");
      if (!f) return ERROR;

      printf("\n Информация из 'statistics.txt':\n\n");

      line_t line;
      while (fgets(line, LINE_LEN, f))
          printf("%s", line);

      fclose(f);

      printf("\n\n");

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
