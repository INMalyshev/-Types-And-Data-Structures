#include <stdlib.h>
#include <stdio.h>

#include "simulation.h"
#include "array_queue.h"
#include "queue.h"
#include "rc.h"

double my_rand_double(int alpha, int betta)
{
  double gamma = (double) alpha;
  int range = betta - alpha;

  gamma += rand() % range;
  gamma += STEP * (rand() % (STEPS + 1));

  return gamma;
}

int my_chance(double probability)
{
  int point = rand() % (STEPS + 1);

  if (point * STEP - probability > EPS)
    return 0;

  return 1;
}

void *new_request_t(double time_point)
{
  request_t *request = malloc(sizeof(request_t));
  if (!request) return NULL;

  request->time_point = time_point;

  return request;
}

void free_request_t(void *request)
{
  free(request);
}

void simulate_with_queue(void)
{
  double timeline = 0.0;
  queue_t queue = {NULL, 0};
  request_t *preparing_request = NULL;
  request_t *processing_request = NULL;

  int report_is_done = 0;

  int requests_out = 0;
  int processed_requests = 0;
  double total_lifetime = 0.0;
  int requests_in = 0;
  double free_processor = 0.0;
  double total_queue_len = 0.0;
  int iteration_amount = 0;

  printf("Начало моделирования.\n");
  printf("%s %s %s\n", "Обработано запросов", "Текущая длина очереди", "Средняя длина очереди");

  while (REQUIRED_REQUESTS_OUT > requests_out)
  {
    /* Вывод информации о системе */
    if (processed_requests >= 100 && processed_requests % 100 == 0 && !report_is_done)
    {
      printf("%-20.1d%-22.1d%-22.3lf\n", processed_requests, queue.len, total_queue_len / iteration_amount);
      report_is_done = 1;
    }

    if (processed_requests % 100 != 0)
    {
      report_is_done = 0;
    }

    /* Если в очереди не ожидается поступления нового request, он создается */
    if (!preparing_request)
    {
      double time_point = timeline + my_rand_double(T1_1, T1_2);
      preparing_request = new_request_t(time_point);
    }

    /* Если время ожидания request подошло, он добавляется в очередь */
    if (preparing_request->time_point - timeline < EPS)
    {
      push_queue_t(&queue, preparing_request);
      total_lifetime -= preparing_request->time_point;
      preparing_request = NULL;
      requests_in++;
    }

    /* Если время обработки request подошло, он добавляется в очередь или выходит из системы*/
    if (processing_request)
    {
      if (processing_request->time_point - timeline < EPS)
      {
        if (my_chance(P))
        {
          push_queue_t(&queue, processing_request);
          processing_request = NULL;
          processed_requests++;
        }
        else
        {
          free(processing_request);
          processing_request = NULL;
          requests_out++;
          processed_requests++;
          total_lifetime += timeline;
          if (requests_out == REQUIRED_REQUESTS_OUT) break;
        }
      }
    }


    /* Если ни один request не обрабатывается, производится попытка взять из очереди новый */
    if (!processing_request)
    {
      queue_note_t *head_note = pop_queue_t(&queue);
      if (head_note)
      {
        double time_point = timeline + my_rand_double(T1_1, T2_2);
        processing_request = head_note->data;
        processing_request->time_point = time_point;
        total_lifetime -= time_point - timeline;
        free(head_note);
      }
      else
      {
        free_processor += STEP;
      }
    }

    /* Сдвиг показателей системы */
    timeline += STEP;
    total_queue_len += queue.len;
    iteration_amount++;
  }
  printf("Конец моделирования.\n\n");

  total_lifetime += timeline * queue.len;

  double average_life_time = total_lifetime / requests_in;

  free_queue_t(&queue);

  printf("Резюме:\n\n");

  printf("Общее время моделирования :                 %.3lf\n", timeline);
  printf("Количество вошедших в систему заявок :      %d\n", requests_in);
  printf("Количество вышедших из системы заявок :     %d\n", requests_out);
  printf("Среднее время пребывания заявки в очереди : %.3lf\n", average_life_time);
  printf("Время простоя аппарата :                    %.3lf\n", free_processor);
  printf("Количество срабатываний ОА :                %d\n\n", processed_requests);
}

void simulate_with_array_queue(void)
{
  double timeline = 0.0;
  array_queue_t queue = new_array_queue_t();
  request_t *preparing_request = NULL;
  request_t *processing_request = NULL;

  int report_is_done = 0;

  int requests_out = 0;
  int processed_requests = 0;
  double total_lifetime = 0.0;
  int requests_in = 0;
  double free_processor = 0.0;
  double total_queue_len = 0.0;
  int iteration_amount = 0;
  int len = 0;

  printf("Начало моделирования.\n");
  printf("%s %s %s\n", "Обработано запросов", "Текущая длина очереди", "Средняя длина очереди");

  while (REQUIRED_REQUESTS_OUT > requests_out)
  {
    /* Вывод информации о системе */
    if (processed_requests >= 100 && processed_requests % 100 == 0 && !report_is_done)
    {
      printf("%-20.1d%-22.1d%-22.3lf\n", processed_requests, len, total_queue_len / iteration_amount);
      report_is_done = 1;
    }

    if (processed_requests % 100 != 0)
    {
      report_is_done = 0;
    }

    /* Если в очереди не ожидается поступления нового request, он создается */
    if (!preparing_request)
    {
      double time_point = timeline + my_rand_double(T1_1, T1_2);
      preparing_request = new_request_t(time_point);
    }

    /* Если время ожидания request подошло, он добавляется в очередь */
    if (preparing_request->time_point - timeline < EPS)
    {
      // printf("[DBG] try push 1\n");
      push_array_queue_t(queue, preparing_request);
      // printf("[DBG] push 1\n");
      len++;
      total_lifetime -= preparing_request->time_point;
      preparing_request = NULL;
      requests_in++;
    }

    /* Если время обработки request подошло, он добавляется в очередь или выходит из системы*/
    if (processing_request)
    {
      if (processing_request->time_point - timeline < EPS)
      {
        if (my_chance(P))
        {
          // printf("[DBG] try push 2\n");
          push_array_queue_t(queue, processing_request);
          // printf("[DBG] push 2\n");
          len++;
          processing_request = NULL;
          processed_requests++;
        }
        else
        {
          free(processing_request);
          processing_request = NULL;
          requests_out++;
          processed_requests++;
          total_lifetime += timeline;
          if (requests_out == REQUIRED_REQUESTS_OUT) break;
        }
      }
    }


    /* Если ни один request не обрабатывается, производится попытка взять из очереди новый */
    if (!processing_request)
    {
      // printf("[DBG] try pop \n");
      request_t *head_request = pop_array_queue_t(queue);
      // printf("[DBG] pop %d\n", len);
      if (head_request)
      {
        len--;
        double time_point = timeline + my_rand_double(T1_1, T2_2);
        processing_request = head_request;
        processing_request->time_point = time_point;
        total_lifetime -= time_point - timeline;
      }
      else
      {
        free_processor += STEP;
      }
    }

    /* Сдвиг показателей системы */
    timeline += STEP;
    total_queue_len += len;
    iteration_amount++;
  }
  printf("Конец моделирования.\n\n");

  total_lifetime += timeline * len;

  double average_life_time = total_lifetime / requests_in;

  free_array_queue_t(queue);

  printf("Резюме:\n\n");

  printf("Общее время моделирования :                 %.3lf\n", timeline);
  printf("Количество вошедших в систему заявок :      %d\n", requests_in);
  printf("Количество вышедших из системы заявок :     %d\n", requests_out);
  printf("Среднее время пребывания заявки в очереди : %.3lf\n", average_life_time);
  printf("Время простоя аппарата :                    %.3lf\n", free_processor);
  printf("Количество срабатываний ОА :                %d\n\n", processed_requests);
}
