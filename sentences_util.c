#include "sentences_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize_sentences_struct(sentences_t *sentences){
    sentences->size = BUFF_SIZE;
    sentences->num_elements = 0;
    sentences->contents = (char **)malloc(BUFF_SIZE * sizeof(char *));
}

void insert_sentence(sentences_t *sentences, char* sentence){
    // reallocate if we have exceeded the buffer size
    if(sentences->num_elements== BUFF_SIZE){
        unsigned int new_buff_size = sentences->size + BUFF_SIZE;
        sentences->contents = (char **)realloc(sentences->contents, new_buff_size);
        sentences->size = new_buff_size;;
    }
    // insert sentence and update number of elements
    unsigned int insert_index = sentences->num_elements;
    sentences->contents[insert_index] = sentence;
    sentences->num_elements++;
}

char* get_next_sentence(FILE *fp){
    //allocate sentence buffer
    char* sentence_buff = (char *)malloc(BUFF_SIZE * sizeof(char));
    //memset(sentence_buff, '\0', sizeof(BUFF_SIZE * sizeof(char)));
    unsigned int i, c, buff_size;
    buff_size = BUFF_SIZE;

    for(i = 0; ((c = fgetc(fp)) != EOF); i++){
        //reallocate to accomodate for null character and remaining of sentence
        if (i == (buff_size - 1)){
            buff_size += buff_size;
            //check for out-of-mem error
            sentence_buff = (char *)realloc(sentence_buff, buff_size);;
        }
        //if at end of sentence, return sentence
        if (c == '.'){
            sentence_buff[i] = c;
            return sentence_buff;
        }

        if (c == '\n' || c == '\t'){
            sentence_buff[i] = ' ';
			continue;
        }
        sentence_buff[i] = c;
    }
    sentence_buff[i + 1] = '\0'; 
    return sentence_buff;
    
}

void populate_sentences_struct(sentences_t *sentences, FILE *fp){
    while(!feof(fp)){
        insert_sentence(sentences, get_next_sentence(fp));
    }
}

void print_sentences(sentences_t* sentences){
    int i;
    for(i = 0; i < sentences->num_elements; i++){
        printf("%s\n", sentences->contents[i]);
    }
}

int sentence_cmp(const void *s1, const void *s2){
    const char *sentence1 = *(const char**)s1;
    const char *sentence2 = *(const char**)s2;;
    return strcmp(sentence1, sentence2);
}

void sort_sentences(sentences_t *sentences){
    qsort(sentences->contents, sentences->num_elements, sizeof(char *), sentence_cmp);
}

void deallocate_sentences(sentences_t *sentences){
    int i;
    for(i = 0; i < sentences->num_elements; i++){
        free(sentences->contents[i]);
    }
    free(sentences->contents);
}
