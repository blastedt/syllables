%.o: %.c
		gcc -std=c99 -Wall -c $<

syllables.exe: LinkedList.o main.o
		gcc -std=c99 -Wall -o $@ $^

.PHONY: clean
clean:
	del *.o