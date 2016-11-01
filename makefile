%.o: %.c
		gcc -std=c99 -Wall -c $<

syllables.exe: LinkedList.o Syllable.o Model.o
		gcc -std=c99 -Wall -o $@ $^

LinkedList_tests.exe: LinkedList.o LinkedList_tests.o
		gcc -std=c99 -Wall -o $@ $^

syllables: syllables.exe

tests: LinkedList_tests.exe

.PHONY: clean
clean:
	del *.o