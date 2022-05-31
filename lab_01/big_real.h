#ifndef _BIG_REAL_H_
#define _BIG_REAL_H_

#define _MANTISSA_LEN_ 30

#define _EXPONENT_MAX_ 99999
#define _EXPONENT_MIN_ -99999

#define _MAX_STR_LEN_ 256

#define _MINUS_S_ "-"
#define _ZERO_AND_DOT_S_ "0."
#define _EXPONENT_S_ "e"

#define _BASE_ 10

#define _TRUE_ 1
#define _FALSE_ 0

#define _EXIT_SUCCESS_ 0
#define _PRINTING_ERROR_ 1
#define _STRUCT_IS_INCORRECT_ 2
#define _NOT_ONLY_DIGITS_IN_LINE_ 3
#define _BUFFER_OVERFLOW_ 4
#define _EMPTY_STRING_ 5
#define _WRONG_SEQUENCE_ 6
#define _WRONG_ELEMENTS_ 7

#define _GOT_ONE_CHAR_ 1

#define _ONE_THING_ 1

typedef struct
{
    int is_negative;
    unsigned char mantissa[_MANTISSA_LEN_];
} big_int_t;
// В мантиссу число помещается поразрядно, начиная с нуливого разряда
// Таким образом число 123 будет представлено, как {3, 2, 1, 0, ...}

typedef struct
{
    big_int_t big_int;
    int exponent;
} big_real_t;
// Структура состоит из большого целого big_int и степени десятки

int make_s_of_big_real(char *dst, big_real_t *big_real);
// Выводит большое действительное в поток f, в формате 0.{до 30 символов}e{порядок}
// При мантиссе и порядке плюс не ставится, минус - при необходимостиы

int is_struct_incorrect(big_real_t *big_real);
// Структура считается корректной, если каждый элемент массива mantissa не больше _BASE_
// Если значением поля is_negative является одно из значение _TRUE_ или  _FALSE_
// В мантиссе есть хотябы один отличный от нуля разряд

int divide_big_integers(big_int_t *numerator, big_int_t *denominator, big_real_t *dst);
// Ситуация деления нуля на что-либо не обрабатывается
// Ситуация деления чего-либо на ноль не обрабатывается
// Не контролирует размер exp

int subtract_big_integers(big_int_t *alpha, big_int_t *betta, big_int_t *dst);
// Функция не работает в общем случае!!!
// На вход подаются два положительных числа типа big_int_t
// Функция не учитывает ситуацию переполнения

int is_bigger_big_int(big_int_t *alpha, big_int_t *betta);
// Выдакт значение _TRUE_, если alpha больше betta, иначе _FALSE_

int is_equal_big_int(big_int_t *alpha, big_int_t *betta);
// Выдакт значение _TRUE_, если alpha равен betta, иначе _FALSE_

void _base_times_multiply_mantissa_(unsigned char *mantissa, size_t len);
// Служебная функция
// Работает с увеличенным буфером

void _subtract_mantissas_(unsigned char *alpha, unsigned char *betta);
// Служебная функция
// alpha заведомо больше или равна betta
// Работает с неравными по длине буферами
// изменяет буфер alpha

int _is_bigger_or_equal_mantissa_(unsigned char *alpha, unsigned char *betta);
// Служебная функция
// Работает с неравными по длине буферами

int _is_equal_zero_(unsigned char *alpha);
// Служебная функция
// Работает с увеличенным буфером

int is_equal_big_real(big_real_t *alpha, big_real_t *betta);
// Выдакт значение _TRUE_, если alpha равен betta, иначе _FALSE_

int divide_big_reals(big_real_t *numerator, big_real_t *denominator, big_real_t *dst);

int string_to_big_int(char *s, big_int_t *dst);
// Выделяет из строки структуру big_int_t,
// если воявляются лишние символы или ошибки при обработке,
// возвращает число, отличное от _EXIT_SUCCESS_

int string_to_big_real(char *s, big_real_t *dst);
// Выделяет из строки структуру big_real_t,
// если воявляются лишние символы или ошибки при обработке,
// возвращает число, отличное от _EXIT_SUCCESS_

int is_eq_zero_big_real(big_real_t *big_real);
// Выдает значение _TRUE_, если big_real эквивалентен нулю, иначе _FALSE_

void _increment_mantissa_big_real_(big_real_t *big_real);
// Служебная функция
// Необходима для округления
// Увеличивает мантиссу на 1
// при необходимости увеличивает порядок числа

#endif
