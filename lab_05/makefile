CC := gcc

CFLAGS := -std=c99 -Werror -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -pedantic

app.exe : main.o
	$(CC) -o $@ $^ $(COV)

main.o : src/main.c
	$(CC) -Iinc $(CFLAGS) -c $<

simulation.o : src/simulation.c inc/simulation.h inc/rc.h inc/queue.h
	$(CC) -Iinc $(CFLAGS) -c $<

queue.o : src/queue.c inc/queue.h inc/rc.h
	$(CC) -Iinc $(CFLAGS) -c $<

.PHONY : clean

clean :
	rm -rf ./*.exe ./*.out ./*.o ./*.pch ./*.gch ./*.gcov ./*.gcda ./*.gcno ./*.h.gcov
