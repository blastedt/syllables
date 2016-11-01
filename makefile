include makefile.cfg

OUT = $(ROOT)/out
SRC = $(ROOT)/src
INC = $(ROOT)/include

CFLAGS = -std=c99 -Wall -I$(INC)

syllables: out outbin outtests $(OUT)/bin/syllables.exe

$(OUT)/%.o: $(ROOT)/src/%.c
		gcc $(CFLAGS) -o $@ -c $<

$(OUT)/bin/syllables.exe: $(OUT)/LinkedList.o $(OUT)/Syllable.o $(OUT)/Model.o
		gcc $(CFLAGS) -o $@ $^

$(OUT)/tests/LinkedList_tests.exe: $(OUT)/LinkedList.o $(OUT)/LinkedList_tests.o
		gcc $(CFLAGS) -o $@ $^


tests: out outbin outtests $(OUT)/tests/LinkedList_tests.exe

outtests:	out
	mkdir $(OUT)/tests

outbin:	out
	mkdir $(OUT)/bin
out:
	mkdir $(OUT)

all: out outbin syllables tests
