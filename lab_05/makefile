CC := gcc

CFLAGS := -std=c99 -Werror -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -pedantic

app.exe : main.o simulation.o queue.o tick.o array_queue.o shape.o
	$(CC) -o $@ $^ $(COV)

main.o : src/main.c inc/simulation.h inc/tick.h inc/array_queue.h
	$(CC) -Iinc $(CFLAGS) -c $<

simulation.o : src/simulation.c inc/simulation.h inc/rc.h inc/queue.h
	$(CC) -Iinc $(CFLAGS) -c $<

queue.o : src/queue.c inc/queue.h inc/rc.h
	$(CC) -Iinc $(CFLAGS) -c $<

tick.o : src/tick.c
	$(CC) -Iinc $(CFLAGS) -c $<

array_queue.o : src/array_queue.c inc/array_queue.h inc/rc.h
	$(CC) -Iinc $(CFLAGS) -c $<

shape.o : src/shape.c inc/rc.h inc/tick.h inc/simulation.h
	$(CC) -Iinc $(CFLAGS) -c $<

.PHONY : clean

clean :
	rm -rf ./*.exe ./*.out ./*.o ./*.pch ./*.gch ./*.gcov ./*.gcda ./*.gcno ./*.h.gcov
