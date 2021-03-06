include makefile.cfg

OUT = $(ROOT)/out
OUTTESTS = $(OUT)/tests
OUTBIN = $(OUT)/bin
SRC = $(ROOT)/src
SRCTESTS = $(SRC)/tests
INC = $(ROOT)/include
TESTINC = -I$(SRC)/tests/include

CC = gcc
CFLAGS = -std=c99 -Wall -I$(INC)


.PHONY: syllables
syllables: directories $(OUTBIN)/syllables.exe

$(OUT)/%_tests.o:	$(SRCTESTS)/%_tests.c
		$(CC) $(CFLAGS) $(TESTINC) -o $@ -c $<

$(OUT)/%.o: $(SRC)/%.c
		$(CC) $(CFLAGS) -o $@ -c $<

$(OUTBIN)/syllables.exe:	$(OUT)/LinkedList.o $(OUT)/Syllable.o $(OUT)/Model.o
		$(CC) $(CFLAGS) -o $@ $^

$(OUTTESTS)/%_tests.exe:	$(OUT)/%.o $(OUT)/%_tests.o
		$(CC) $(CFLAGS) -o $@ $^

.PHONY: tests
tests: directories $(OUTTESTS)/LinkedList_tests.exe $(OUTTESTS)/Syllable_tests.exe

.PHONY: directories
directories: $(OUTTESTS) $(OUTBIN) $(OUT)

$(OUTTESTS):
	mkdir $(OUTTESTS)

$(OUTBIN):
	mkdir $(OUTBIN)

$(OUT):
	mkdir $(OUT)

.PHONY: all
all: directories syllables tests
