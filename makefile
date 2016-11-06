include makefile.cfg

OUT = $(ROOT)/out
SRC = $(ROOT)/src
INC = $(ROOT)/include

CFLAGS = -std=c99 -Wall -I$(INC)
TESTINC = -I$(SRC)/tests/include

.PHONY: syllables
syllables: directories $(OUT)/bin/syllables.exe

$(OUT)/%_tests.o:	$(ROOT)/src/tests/%_tests.c
		gcc $(CFLAGS) $(TESTINC) -o $@ -c $<

$(OUT)/%.o: $(ROOT)/src/%.c
		gcc $(CFLAGS) -o $@ -c $<

$(OUT)/bin/syllables.exe:	$(OUT)/LinkedList.o $(OUT)/Syllable.o $(OUT)/Model.o
		gcc $(CFLAGS) -o $@ $^

$(OUT)/tests/%_tests.exe:	$(OUT)/%.o $(OUT)/%_tests.o
		gcc $(CFLAGS) -o $@ $^

$(OUT)/tests/LinkedList_tests.exe: $(OUT)/LinkedList.o $(OUT)/LinkedList_tests.o
		gcc $(CFLAGS) -o $@ $^

.PHONY: tests
tests: directories $(OUT)/tests/LinkedList_tests.exe $(OUT)/tests/Syllable_tests.exe

.PHONY: directories
directories: out/tests out/bin out

$(OUT)/tests:
	mkdir -p $(OUT)/tests

$(OUT)/bin:
	mkdir -p $(OUT)/bin

$(OUT):
	mkdir -p $(OUT)

.PHONY: all
all: directories syllables tests
