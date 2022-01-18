CC := gcc

CFLAGS := -std=c99 -Werror -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -pedantic

app.exe : main.o graph.o tick.o
	$(CC) -o $@ $^ $(COV)

main.o : src/main.c inc/graph.h inc/tick.h
	$(CC) -Iinc $(CFLAGS) -c $<

graph.o : src/graph.c inc/graph.h
	$(CC) -Iinc $(CFLAGS) -c $<

tick.o : src/tick.c inc/tick.h
	$(CC) -Iinc $(CFLAGS) -c $<


.PHONY : clean

clean :
	rm -rf ./*.exe ./*.out ./*.o ./*.pch ./*.gch ./*.gcov ./*.gcda ./*.gcno ./*.h.gcov
