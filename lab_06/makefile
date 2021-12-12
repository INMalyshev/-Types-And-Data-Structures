CC := gcc

CFLAGS := -std=c99 -Werror -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -pedantic

app.exe : main.o interior_hash_table.o binary_tree.o text_file.o shape.o
	$(CC) -o $@ $^ $(COV)

main.o : src/main.c inc/binary_tree.h inc/interior_hash_table.h
	$(CC) -Iinc $(CFLAGS) -c $<

interior_hash_table.o : src/interior_hash_table.c inc/interior_hash_table.h
	$(CC) -Iinc $(CFLAGS) -c $<

binary_tree.o : src/binary_tree.c inc/binary_tree.h
	$(CC) -Iinc $(CFLAGS) -c $<

text_file.o : src/text_file.c inc/text_file.h
	$(CC) -Iinc $(CFLAGS) -c $<

shape.o : src/shape.c inc/shape.h inc/text_file.h inc/binary_tree.h inc/interior_hash_table.h
	$(CC) -Iinc $(CFLAGS) -c $<

.PHONY : clean

clean :
	rm -rf ./*.exe ./*.out ./*.o ./*.pch ./*.gch ./*.gcov ./*.gcda ./*.gcno ./*.h.gcov
