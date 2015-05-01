CC = gcc

all: sort_sentences simple_test

sentences_util.o: sentences_util.c sentences_util.h
	gcc -Wall -c $<

sort_sentences: sort_sentences.c sentences_util.o
	gcc -Wall -o $@ $< sentences_util.o

simple_test: simple_test.c sentences_util.o
	gcc -Wall -o $@ $< sentences_util.o


clean:
	rm sort_sentences simple_test sentences_util.o
