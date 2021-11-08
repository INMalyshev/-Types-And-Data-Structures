CC := gcc

CFLAGS := -std=c99 -Werror -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -pedantic

mystring.o : src/mystring.c inc/mystring.h inc/rc.h
	$(CC) -Iinc $(CFLAGS) -c $<

tick.o : src/tick.c inc/tick.h
	$(CC) -Iinc $(CFLAGS) -c $<

stec.o : src/stec.c inc/stec.h inc/rc.h
	$(CC) -Iinc $(CFLAGS) -c $<
