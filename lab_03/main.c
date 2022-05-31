#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "shape.h"

couple_t *couple;

int main(void)
{
    couple = malloc(sizeof(couple_t));
    if (!couple) return ERROR;

    setbuf(stdout, NULL);

    int answer = ERROR;
    while (answer == ERROR)
    {
        answer = handle_init_menu(couple);
        if (answer == ERROR)
        {
            printf("Что-то пошло не так...\n");
            printf("Возврат в меню...\n");
            skip_stdin();
        }
    }

    int choice = -1;

    while (choice != 0)
    {
        pri_main_menu();
        printf("Ваш выбор:\n");

        if (!scanf("%d", &choice))
        {
            printf("Неверный ввод...\n");
            printf("Возврат в меню...\n");
            choice = -1;
            skip_stdin();
            continue;
        }

        if (choice == 0)
        {
            printf("Программа завершена корректно...\n");
        }

        if (handle_main_menu(choice, couple) == ERROR)
        {
            printf("Возникла ошибка...\n");
            printf("Повторное выполнение пункта...\n");
            skip_stdin();
        }
    }

    return OK;
}
