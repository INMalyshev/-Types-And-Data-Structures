CC := gcc

CFLAGS := -std=c99 -Werror -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -pedantic

interior_hash_table.o : src/interior_hash_table.c inc/interior_hash_table.h
	$(CC) -Iinc $(CFLAGS) -c $<


.PHONY : clean

clean :
	rm -rf ./*.exe ./*.out ./*.o ./*.pch ./*.gch ./*.gcov ./*.gcda ./*.gcno ./*.h.gcov
