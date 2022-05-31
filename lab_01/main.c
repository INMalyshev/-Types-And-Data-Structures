#include <stdio.h>
#include <stddef.h>

#include "big_real.h"

#define _HALF_STR_LEN_ ((size_t)_MAX_STR_LEN_ / 2)
#define _HALF_HALF_STR_LEN_ ((size_t)_HALF_STR_LEN_ / 2)
#define _OUT_STREAM_ stdout
#define _IN_STREAM_ stdin

int main(void)
{
    setbuf(stdout, NULL);

    fprintf(_OUT_STREAM_, "Program started...\n\n\n");

    fprintf(_OUT_STREAM_, "This program  is meant  to divide  decimal number by  big real number,\n\n");

    fprintf(_OUT_STREAM_, "the result  of division  is big  real too.  The program starts working\n\n");

    fprintf(_OUT_STREAM_, "after  you  have  entered  the numbers  in your  console. You can use \n\n");

    fprintf(_OUT_STREAM_, "arabic digits, letters 'e' & 'E', symbols '-' & '.'. Any other symbols\n\n");

    fprintf(_OUT_STREAM_, "are  banned.  Use  your  keyboard  to  enter  the  numbers.\n\n");

    // Считывание строк

    fprintf(_OUT_STREAM_, "\nEnter decimal number: \n");

    fprintf(_OUT_STREAM_, "    5    10   15   20   25   30\n");
    fprintf(_OUT_STREAM_, "----|----|----|----|----|----|\n");

    char decimal[_MAX_STR_LEN_];
    int response = 0;

    fscanf(_IN_STREAM_, "%128s", decimal);

    fprintf(_OUT_STREAM_, "\nEnter real number: \n");

    fprintf(_OUT_STREAM_, "    5    10   15   20   25  30     5\n");
    fprintf(_OUT_STREAM_, "----|----|----|----|----|----||----|\n");

    char real[_MAX_STR_LEN_];

    fscanf(_IN_STREAM_, "%128s", real);

    big_int_t decimal_big_int;
    if ((response = string_to_big_int(decimal, &decimal_big_int)))
    {
        fprintf(_OUT_STREAM_, "\n\nSomething wrong with decimal. Error # %d\n\n", response);
        fprintf(_OUT_STREAM_, "\nProgram finished unexpectedly...\n\n");
        return response;
    }

    big_real_t decimal_big_real = {
            decimal_big_int,
            0
    };

    big_real_t real_big_real;
    if ((response = string_to_big_real(real, &real_big_real)))
    {
        fprintf(_OUT_STREAM_, "\n\nSomething wrong with real. Error # %d\n\n", response);
        fprintf(_OUT_STREAM_, "\nProgram finished unexpectedly...\n\n");
        return response;
    }


    // Обработка введенных нулей
    int dec_is_zero = is_eq_zero_big_real(&decimal_big_real);
    int rea_is_zero = is_eq_zero_big_real(&real_big_real);

    if (dec_is_zero && rea_is_zero)
    {
        fprintf(_OUT_STREAM_, "\nResult : zero by zero division result is undefined\n\n");
        fprintf(_OUT_STREAM_, "\nProgram finished successfully...\n\n");
        return _EXIT_SUCCESS_;
    }
    else if (dec_is_zero)
    {
        fprintf(_OUT_STREAM_, "\nResult : 0.0e0\n\n");
        fprintf(_OUT_STREAM_, "\nProgram finished successfully...\n\n");
        return _EXIT_SUCCESS_;
    }
    else if (rea_is_zero)
    {
        fprintf(_OUT_STREAM_, "\nResult : INFINITY\n\n");
        fprintf(_OUT_STREAM_, "\nProgram finished successfully...\n\n");
        return _EXIT_SUCCESS_;
    }

    big_real_t result_big_real;

    if ((response = divide_big_reals(&decimal_big_real, &real_big_real, &result_big_real)))
    {
        fprintf(_OUT_STREAM_, "\n\nError occurred while division . Error # %d\n\n", response);
        fprintf(_OUT_STREAM_, "\nProgram finished unexpectedly...\n\n");
        return response;
    }

    char result[_MAX_STR_LEN_];

    if ((response = make_s_of_big_real(result, &result_big_real)))
    {
        fprintf(_OUT_STREAM_, "\n\nError occurred while converting big_real to string. Error # %d\n\n", response);
        fprintf(_OUT_STREAM_, "\nProgram finished unexpectedly...\n\n");
        return response;
    }

    fprintf(_OUT_STREAM_, "\nResult : %s\n\n", result);

    fprintf(_OUT_STREAM_, "\nProgram finished successfully...\n\n");

    return _EXIT_SUCCESS_;
}