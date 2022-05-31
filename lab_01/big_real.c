
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "big_real.h"

int _is_int_(char *s)
{
    for (size_t i = 0; s[i]; i++)
    {
        if (s[i] == '-' && i == 0)
            continue;
        if (!isdigit(s[i]))
            return _FALSE_;
    }
    return _TRUE_;
}

int make_s_of_big_real(char *dst, big_real_t *big_real)
{
    // Плохая структура -- выход
    if (is_struct_incorrect(big_real))
        return _STRUCT_IS_INCORRECT_;

    int position = 0;

    // Проверка знака
    if (big_real -> big_int.is_negative)
    {
        int minus_len = strlen(_MINUS_S_);
        if (sprintf(dst + position, "%s", _MINUS_S_) != minus_len)
            return _PRINTING_ERROR_;
        position += minus_len;
    }
    int zero_and_dot_len = strlen(_ZERO_AND_DOT_S_);

    if (sprintf(dst + position, "%s", _ZERO_AND_DOT_S_) != zero_and_dot_len)
        return _PRINTING_ERROR_;
    position += zero_and_dot_len;

    // Поиск максимального значащего разряда в мантиссе
    size_t max_exp = 0;
    for (size_t i = 0; i < _MANTISSA_LEN_; i++)
        if (big_real->big_int.mantissa[i] > 0)
            max_exp = i;

    for (int i = max_exp; i >= 0; i--)
    {
        if (sprintf(dst + position, "%hhu", big_real -> big_int.mantissa[i]) != _ONE_THING_)
            return _PRINTING_ERROR_;
        position += _ONE_THING_;
    }

    int exponent_len = strlen(_EXPONENT_S_);

    if (sprintf(dst + position, "%s", _EXPONENT_S_) != exponent_len)
        return _PRINTING_ERROR_;

    position += exponent_len;

    sprintf(dst + position, "%d", big_real -> exponent + (int) max_exp + 1);

    return _EXIT_SUCCESS_;
}

int is_struct_incorrect(big_real_t *big_real)
{
    // случайное значение в поле is_negative
    if (big_real -> big_int.is_negative != _TRUE_ && big_real -> big_int.is_negative != _FALSE_)
        return _TRUE_;

    int flag = 1;

    // есть ли в мантиссе не нули и не превышают ли значения разрядов _BASE_
    for (size_t i = 0; i < _MANTISSA_LEN_; i++)
    {
        if (big_real->big_int.mantissa[i] >= _BASE_)
            return _TRUE_;
        if (big_real->big_int.mantissa[i] > 0)
            flag = 0;
    }

    // одни нули -- некорректная структура
    if (flag)
        return _TRUE_;

    // модуль порядка превышает 99999 -- некорректная структура
    if (big_real -> exponent > _EXPONENT_MAX_ || big_real -> exponent < _EXPONENT_MIN_)
        return _TRUE_;

    return _FALSE_;
}

int is_equal_big_int(big_int_t *alpha, big_int_t *betta)
{
    // Функция пробегает все поля, проверяет на равенство

    if (alpha -> is_negative != betta -> is_negative)
        return _FALSE_;

    for (size_t i = 0; i < _MANTISSA_LEN_; i++)
        if (alpha -> mantissa[i] != betta -> mantissa[i])
            return _FALSE_;

    return _TRUE_;
}

int is_bigger_big_int(big_int_t *alpha, big_int_t *betta)
{
    // обработка случаев зависящих только от знака
    if (alpha -> is_negative == _TRUE_ && betta -> is_negative == _FALSE_)
        return _FALSE_;

    if (alpha -> is_negative == _FALSE_ && betta -> is_negative == _TRUE_)
        return _TRUE_;

    // Определение обрабатываемой области
    size_t alpha_max_exp = 0;
    for (size_t i = 0; i < _MANTISSA_LEN_; i++)
        if (alpha->mantissa[i] > 0)
            alpha_max_exp = i;

    size_t betta_max_exp = 0;
    for (size_t i = 0; i < _MANTISSA_LEN_; i++)
        if (alpha->mantissa[i] > 0)
            betta_max_exp = i;

    size_t max_exp = alpha_max_exp;
    if (betta_max_exp > max_exp)
        max_exp = betta_max_exp;

    // Сравнение с учетом знака
    for (int i = max_exp; i >= 0; i--)
    {
        if (alpha->mantissa[i] > betta->mantissa[i] && alpha->is_negative == _FALSE_)
            return _TRUE_;

        if (alpha->mantissa[i] > betta->mantissa[i] && alpha->is_negative == _TRUE_)
            return _FALSE_;

        if (alpha->mantissa[i] < betta->mantissa[i] && alpha->is_negative == _TRUE_)
            return _TRUE_;

        if (alpha->mantissa[i] < betta->mantissa[i] && alpha->is_negative == _FALSE_)
            return _FALSE_;
    }

    return _FALSE_;
}

int subtract_big_integers(big_int_t *alpha, big_int_t *betta, big_int_t *dst)
{
    // Если равны, то возврат нуля
    if (is_equal_big_int(alpha, betta))
    {
        dst->is_negative = _FALSE_;
        for (size_t i = 0; i < _MANTISSA_LEN_; i++)
            dst->mantissa[i] = 0;
    }

    // Если alpha больше betta
    else if (is_bigger_big_int(alpha, betta))
    {
        dst->is_negative = _FALSE_;
        int temp;
        int virtual_mantissa[_MANTISSA_LEN_] = {0};

        // вычитание как в школе
        for (size_t i = 0; i < _MANTISSA_LEN_; i++)
        {
            temp = virtual_mantissa[i] + alpha->mantissa[i] - betta->mantissa[i];
            if (temp < 0)
            {
                virtual_mantissa[i] += 1 * _BASE_;
                virtual_mantissa[i + 1] -= 1;
                temp = virtual_mantissa[i] + alpha->mantissa[i] - betta->mantissa[i];
            }
            dst->mantissa[i] = temp;
        }
    }

    // Если alpha больше betta
    else
    {
        dst->is_negative = _TRUE_;
        int temp;
        int virtual_mantissa[_MANTISSA_LEN_] = {0};
        for (size_t i = 0; i < _MANTISSA_LEN_; i++)
        {
            temp = virtual_mantissa[i] + betta->mantissa[i] - alpha->mantissa[i];
            if (temp < 0)
            {
                virtual_mantissa[i] += 1 * _BASE_;
                virtual_mantissa[i + 1] -= 1;
                temp = virtual_mantissa[i] + betta->mantissa[i] - alpha->mantissa[i];
            }
            dst->mantissa[i] = temp;
        }
    }

    return _EXIT_SUCCESS_;
}

int divide_big_integers(big_int_t *numerator, big_int_t *denominator, big_real_t *dst)
{
    if (is_equal_big_int(numerator, denominator))
    {
        dst->big_int.is_negative = 0;
        dst->exponent = 0;
        for (size_t i = 1; i < _MANTISSA_LEN_; i++)
            dst->big_int.mantissa[i] = 0;
        dst->big_int.mantissa[0] = 1;
    }

    unsigned char result_mantissa[_MANTISSA_LEN_] = {0};
    unsigned char alpha_mantissa[_MANTISSA_LEN_ + 1] = {0};
    unsigned char betta_mantissa[_MANTISSA_LEN_];
    int result_exp = 0;
    int counter = 0;
    int temp;
    int flag = _FALSE_;
    int needs_to_increment = _FALSE_;

    for (size_t i = 0; i < _MANTISSA_LEN_; i++)
    {
        alpha_mantissa[i] = numerator->mantissa[i];
        betta_mantissa[i] = denominator->mantissa[i];
    }

    size_t num_max_exp = 0, den_max_exp = 0;
    for (size_t i = 0; i < _MANTISSA_LEN_; i++)
    {
        if (numerator->mantissa[i] > 0)
            num_max_exp = i;
        if (denominator->mantissa[i] > 0)
            den_max_exp = i;
    }

    // единоразовое . Порядок знаменателя становится не меньше порядка числителя
    if (num_max_exp > den_max_exp)
    {
        for (size_t i = 0; i < num_max_exp - den_max_exp; i++)
            _base_times_multiply_mantissa_(betta_mantissa, _MANTISSA_LEN_);
        result_exp += num_max_exp - den_max_exp;
    }

    // единоразовое . Числитель становится больше знаменателя
    while (!_is_bigger_or_equal_mantissa_(alpha_mantissa, betta_mantissa))
    {
        _base_times_multiply_mantissa_(alpha_mantissa, _MANTISSA_LEN_ + 1);
        result_exp--;
    }

    while (counter < _MANTISSA_LEN_ && !_is_equal_zero_(alpha_mantissa))
    {

        // перед вычитанием нужно добится, чтобы порядок числителя был неменьше порядка знаменателя
        if (!_is_bigger_or_equal_mantissa_(alpha_mantissa, betta_mantissa))
        {
            _base_times_multiply_mantissa_(alpha_mantissa, _MANTISSA_LEN_ + 1);
            result_exp--;
            if (flag == _TRUE_)
            {
                _base_times_multiply_mantissa_(result_mantissa, _MANTISSA_LEN_);
                result_mantissa[0] = 0;
                counter++;
            }
            flag = _TRUE_;
        }

        // деление как в школе
        else
        {
            flag = _FALSE_;
            temp = 0;
            while (_is_bigger_or_equal_mantissa_(alpha_mantissa, betta_mantissa))
            {
                _subtract_mantissas_(alpha_mantissa, betta_mantissa);
                temp++;
            }
            _base_times_multiply_mantissa_(result_mantissa, _MANTISSA_LEN_);
            result_mantissa[0] = temp;
            counter++;
        }

        // округление
        if (counter == _MANTISSA_LEN_ && !_is_equal_zero_(alpha_mantissa))
        {
            temp = 0;

            _base_times_multiply_mantissa_(alpha_mantissa, _MANTISSA_LEN_ + 1);

            while (_is_bigger_or_equal_mantissa_(alpha_mantissa, betta_mantissa))
            {
                _subtract_mantissas_(alpha_mantissa, betta_mantissa);
                temp++;
            }

            if (temp >= 5)
                needs_to_increment = _TRUE_;
        }
    }

    // работа сло знаком
    if (numerator->is_negative == denominator->is_negative)
        dst->big_int.is_negative = 0;
    else
        dst->big_int.is_negative = 1;

    dst->exponent = result_exp;

    for (size_t i = 0; i < _MANTISSA_LEN_; i++)
        dst->big_int.mantissa[i] = result_mantissa[i];

    // округление
    if (needs_to_increment == _TRUE_)
        _increment_mantissa_big_real_(dst);

    return _EXIT_SUCCESS_;
}

void _base_times_multiply_mantissa_(unsigned char *mantissa, size_t len)
{
    // Сдвиг мантиссы на одну позицию вправо с потерей крайнего элемента
    for (int i = len - 1; i > 0; i--)
        mantissa[i] = mantissa[i - 1];
    mantissa[0] = 0;
}

void _subtract_mantissas_(unsigned char *alpha, unsigned char *betta)
{
    // Вычитание мантисс неравной длины
    int temp;
    int virtual_mantissa[_MANTISSA_LEN_ + 1] = {0};
    for (size_t i = 0; i < _MANTISSA_LEN_ + 1; i++)
    {
        if (i != _MANTISSA_LEN_)
            temp = virtual_mantissa[i] + alpha[i] - betta[i];
        else
            temp = virtual_mantissa[i] + alpha[i];

        if (temp < 0)
        {
            virtual_mantissa[i] += 1 * _BASE_;
            virtual_mantissa[i + 1] -= 1;
            temp = virtual_mantissa[i] + alpha[i] - betta[i];
        }
        alpha[i] = temp;
    }
}

int _is_bigger_or_equal_mantissa_(unsigned char *alpha, unsigned char *betta)
{
    // Сравнение мантисс неравной длины
    if (alpha[_MANTISSA_LEN_])
        return _TRUE_;
    for (int i = _MANTISSA_LEN_ - 1; i >= 0; i--)
    {
        if (alpha[i] > betta[i])
            return _TRUE_;
        else if (alpha[i] < betta[i])
            return _FALSE_;
    }
    return _TRUE_;
}

int _is_equal_zero_(unsigned char *alpha)
{
    // проверка на равенство мантиссы нулю
    for (size_t i = 0; i < _MANTISSA_LEN_ + 1; i++)
        if (alpha[i])
            return _FALSE_;

    return _TRUE_;
}

int is_equal_big_real(big_real_t *alpha, big_real_t *betta)
{
    // Сравнивает все поля
    if (alpha->exponent != betta->exponent)
        return _FALSE_;

    if (is_equal_big_int(&alpha->big_int, &betta->big_int) == _FALSE_)
        return _FALSE_;

    return _TRUE_;
}

int divide_big_reals(big_real_t *numerator, big_real_t *denominator, big_real_t *dst)
{
    // Сначала делит целые части действительных числе
    // потом прибавляет к получившемуся порядку разность
    // порядка числителя и порядка знаменателя
    big_real_t division_mantissas_result;
    divide_big_integers(&numerator->big_int, &denominator->big_int, &division_mantissas_result);

    int exponent_difference = numerator->exponent - denominator->exponent;
    division_mantissas_result.exponent += exponent_difference;

    if(is_struct_incorrect(&division_mantissas_result))
        return _STRUCT_IS_INCORRECT_;

    *dst = division_mantissas_result;

    return _EXIT_SUCCESS_;
}

int string_to_big_int(char *s, big_int_t *dst)
{
    size_t len = strlen(s);

    if (len == 0)
        return _EMPTY_STRING_;

    size_t counter = 0;

    unsigned char mantissa[_MANTISSA_LEN_] = {0};
    int is_negative = _FALSE_;

    for (size_t i = 0; i < len; i++)
    {
        if (counter == _MANTISSA_LEN_)
            return _BUFFER_OVERFLOW_;

        if (i == 0 && s[i] == '-')
            is_negative = _TRUE_;

        else if (s[i] == '\n')
            continue;

        else if (isdigit(s[i]))
        {
            if (s[i] == '1')
            {
                _base_times_multiply_mantissa_(mantissa, _MANTISSA_LEN_);
                mantissa[0] = 1;
            }
            else if (s[i] == '2')
            {
                _base_times_multiply_mantissa_(mantissa, _MANTISSA_LEN_);
                mantissa[0] = 2;
            }
            else if (s[i] == '3')
            {
                _base_times_multiply_mantissa_(mantissa, _MANTISSA_LEN_);
                mantissa[0] = 3;
            }
            else if (s[i] == '4')
            {
                _base_times_multiply_mantissa_(mantissa, _MANTISSA_LEN_);
                mantissa[0] = 4;
            }
            else if (s[i] == '5')
            {
                _base_times_multiply_mantissa_(mantissa, _MANTISSA_LEN_);
                mantissa[0] = 5;
            }
            else if (s[i] == '6')
            {
                _base_times_multiply_mantissa_(mantissa, _MANTISSA_LEN_);
                mantissa[0] = 6;
            }
            else if (s[i] == '7')
            {
                _base_times_multiply_mantissa_(mantissa, _MANTISSA_LEN_);
                mantissa[0] = 7;
            }
            else if (s[i] == '8')
            {
                _base_times_multiply_mantissa_(mantissa, _MANTISSA_LEN_);
                mantissa[0] = 8;
            }
            else if (s[i] == '9')
            {
                _base_times_multiply_mantissa_(mantissa, _MANTISSA_LEN_);
                mantissa[0] = 9;
            }
            else if (s[i] == '0')
            {
                _base_times_multiply_mantissa_(mantissa, _MANTISSA_LEN_);
                mantissa[0] = 0;
            }
            counter++;
        }
        else
        {
            return _WRONG_ELEMENTS_;
        }
    }

    if (counter == 0)
        return _WRONG_ELEMENTS_;

    dst->is_negative = is_negative;
    for (size_t i = 0; i < _MANTISSA_LEN_; i++)
        dst->mantissa[i] = mantissa[i];

    return _EXIT_SUCCESS_;
}

int string_to_big_real(char *s, big_real_t *dst)
{
    size_t len = strlen(s);

    if (len == 0)
        return _EMPTY_STRING_;

    size_t e_index;
    for (e_index = 0; e_index < len && s[e_index] != 'e' && s[e_index] != 'E'; e_index++);


    size_t dot_index;
    for (dot_index = 0; dot_index < e_index && s[dot_index] != '.'; dot_index++);

    int result_exponent = 0;

    if (dot_index < e_index)
        result_exponent = dot_index - e_index + 1;

    char buf[_MAX_STR_LEN_] = {'\0'};
    size_t buf_len = 0;

    for (size_t i = 0; i < e_index; i++)
    {
        if (buf_len == _MAX_STR_LEN_ - 1)
            return _BUFFER_OVERFLOW_;
        if (i != dot_index)
        {
            buf[buf_len++] = s[i];
            buf[buf_len] = '\0';
        }
    }

    big_int_t big_int;
    int response = 0;

    if ((response = string_to_big_int(buf, &big_int)))
        return response;

    if (e_index < len)
    {
        size_t e_part_len = strlen(s + e_index + 1);

        if (e_part_len != 0)
        {
            if (_is_int_(s + e_index + 1) == _FALSE_)
                return _WRONG_ELEMENTS_;

            int only_zeroes = _TRUE_;
            for (size_t i = e_index + 1; s[i]; i++)
                if (s[i] != '0')
                    only_zeroes = _FALSE_;

            int e_e = atoi(s + e_index + 1);

            if (e_e == 0 && only_zeroes == _FALSE_)
                return _WRONG_ELEMENTS_;

            result_exponent += e_e;
        }
    }

    if (result_exponent > _EXPONENT_MAX_ || result_exponent < _EXPONENT_MIN_)
        return _STRUCT_IS_INCORRECT_;

    dst->big_int = big_int;
    dst->exponent = result_exponent;

    return _EXIT_SUCCESS_;
}

int is_eq_zero_big_real(big_real_t *big_real)
{
    // если в мантиссе есть хотябы один не ноль, то возвращает _FALSE_ иначе _TRUE_
    for (size_t i = 0; i < _MANTISSA_LEN_; i++)
        if (big_real->big_int.mantissa[i] != 0)
            return _FALSE_;
    return _TRUE_;
}

void _increment_mantissa_big_real_(big_real_t *big_real)
{
    // реализует школьный алгоритм сложения двух чисел,
    // в условиях ограниченной длины результата
    // инкрементирует мантиссу
    // в случае переполнения сдвигает мантиссу в лево
    // и увеличивает порядок результата на один
    unsigned char in_mind = 1;

    for (size_t i = 0; i < _MANTISSA_LEN_; i++)
    {
        unsigned char temp = (big_real->big_int.mantissa[i] + in_mind);
        big_real->big_int.mantissa[i] = temp % _BASE_;
        in_mind = temp / _BASE_;
    }

    if (in_mind != 0)
    {
        big_real->exponent += 1;
        for (size_t i = 0; i < _MANTISSA_LEN_ - 1; i++)
        {
            big_real->big_int.mantissa[i] = big_real->big_int.mantissa[i+1];
        }
        big_real->big_int.mantissa[_MANTISSA_LEN_ - 1] = in_mind;
    }

    size_t zero_count = 0;
    for (; big_real->big_int.mantissa[zero_count] == 0 && zero_count < _MANTISSA_LEN_; zero_count++);

    size_t i;
    if (zero_count != 0)
    {
        big_real->exponent += zero_count;
        for (i = 0; i < _MANTISSA_LEN_ - zero_count; i++)
            big_real->big_int.mantissa[i] = big_real->big_int.mantissa[i + zero_count];
        for (; i < _MANTISSA_LEN_; i++)
            big_real->big_int.mantissa[i] = 0;
    }
}
