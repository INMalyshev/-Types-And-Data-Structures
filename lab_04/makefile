CC := gcc

CFLAGS := -std=c99 -Werror -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -pedantic

app.exe : main.o  mystring.o stec.o shape.o tick.o array_stec.o
	$(CC) -o $@ $^ $(COV)

main.o : src/main.c inc/mystring.h inc/stec.h inc/shape.h inc/array_stec.h
	$(CC) -Iinc $(CFLAGS) -c $<

mystring.o : src/mystring.c inc/mystring.h inc/rc.h
	$(CC) -Iinc $(CFLAGS) -c $<

tick.o : src/tick.c inc/tick.h
	$(CC) -Iinc $(CFLAGS) -c $<

stec.o : src/stec.c inc/stec.h inc/rc.h inc/mystring.h
	$(CC) -Iinc $(CFLAGS) -c $<

shape.o : src/shape.c inc/rc.h inc/stec.h inc/mystring.h inc/tick.h inc/array_stec.h
	$(CC) -Iinc $(CFLAGS) -c $<

array_stec.o : src/array_stec.c inc/array_stec.h inc/rc.h inc/mystring.h
	$(CC) -Iinc $(CFLAGS) -c $<


.PHONY : clean

clean :
	rm -rf ./*.exe ./*.out ./*.o ./*.pch ./*.gch ./*.gcov ./*.gcda ./*.gcno ./*.h.gcov
