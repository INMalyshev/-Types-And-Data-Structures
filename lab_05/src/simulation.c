#include <stdlib.h>
#include <stdio.h>

#include "simulation.h"
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

void *new_request_t(void)
{
  request_t *request = malloc(sizeof(request_t));
  if (!request) return NULL;

  request->position = POSITION_PREPARING;
  request->new_position_time = my_rand_double(T1_1, T1_2);

  return request;
}

void free_request_t(void *request)
{
  free(request);
}

void *simulate_with_queue(void)
{
  double timeline = 0.0;
  queue_t queue = {NULL};
  request_t *preparing_request = NULL;
  int requests_out = 0;

  while (REQUIRED_REQUESTS_OUT > requests_out)
  {
    timeline += STEP;
  }
}
