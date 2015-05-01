#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

const unsigned int BUFF_SIZE = 4096;

typedef struct sentences{
    unsigned int size;
    unsigned int num_elements;
    char **contents;
} sentences_t;

//initialize_sentences_struct(sentence_list);
//insert_sentence(sentence_list, get_next_sentence(fp));
//populate_sentences_struct(sentences_list, fp);
//sort_sentences(sentene_list);
//print_sentences(sentence_list);

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


//initialize_sentences_struct(sentence_list);
//insert_sentence(sentence_list, get_next_sentence(fp));
//populate_sentences_struct(sentences_list, fp);
//sort_sentences(sentene_list);
//print_sentences(sentence_list);

int main(int argc, char *argv[]){
    char *usage_msg = "usage: sort_sentences <input-file>";
    char *error_msg = "ERROR: %s\n";
    
    // Check for proper command usage
    if (argc != 2){
        printf("%s\n", usage_msg);
        return -1;
    }

    char *filename = argv[1];
    FILE *fp;

    if ((fp = fopen(filename, "r"))){
        /*
        sentences_t sentences;
        initialize_sentences_struct(&sentences);
        insert_sentence(&sentences, "f sentence");
        insert_sentence(&sentences, "a sentence");
        insert_sentence(&sentences, "z sentence");
        insert_sentence(&sentences, "q sentence");
        printf("Size: %i\n", sentences.size);
        printf("Numelems: %i\n", sentences.num_elements);
        print_sentences(&sentences);
        printf("Sorting...\n");
        sort_sentences(&sentences);
        printf("Done sorting.\n");
        print_sentences(&sentences);
        */
        sentences_t sentences;
        initialize_sentences_struct(&sentences);
        populate_sentences_struct(&sentences, fp);
        sort_sentences(&sentences);
        print_sentences(&sentences);
        deallocate_sentences(&sentences);
    }
    else{
        printf(error_msg, strerror(errno));
        return -1;
    }

    // TODO: check for error
    //      free memory
    fclose(fp);
    return 0;
}
