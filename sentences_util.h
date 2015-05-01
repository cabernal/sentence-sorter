#include <stdio.h>

// 4KB buffer size
#define BUFF_SIZE 4096

// Sentences structure
typedef struct sentences {
    // Buffer size (bytes)
    unsigned int size;
    // Number of sentence
    unsigned int num_elements;
    // List of sentences
    char **contents;
} sentences_t;

void initialize_sentences_struct(sentences_t *sentences);

void insert_sentence(sentences_t *sentences, char* sentence);

char* get_next_sentence(FILE *fp);

void populate_sentences_struct(sentences_t *sentences, FILE *fp);

void print_sentences(sentences_t* sentences);

int sentence_cmp(const void *s1, const void *s2);

void sort_sentences(sentences_t *sentences);

void deallocate_sentences(sentences_t *sentences);
