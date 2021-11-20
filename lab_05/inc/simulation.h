#ifndef SIMULATION_H
#define SIMULATION_H

#define POSITION_PREPARING 1
#define POSITION_QUEUE 2
#define POSITION_PROCESSING 3

typedef struct
{
  double time_point;
} request_t;

void *new_request_t(double time_point);
void free_request_t(void *request);

#define EPS 1e-6

#define STEPS 1000
#define STEP 1e-3

double my_rand_double(int alpha, int betta);
int my_chance(double probability);

#define T1_1 0
#define T1_2 6
#define T2_2 1
#define P 0.8

#define REQUIRED_REQUESTS_OUT 1000

void simulate_with_queue(void);

#endif
