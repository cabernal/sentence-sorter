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
        printf("Triggered reallocation...\n");
        unsigned int new_buff_size = sentences->size + BUFF_SIZE;
        sentences->contents = (char **)realloc(sentences->contents, new_buff_size);
        sentences->size = new_buff_size;;
        printf("Done reallocation...\n");
    }
    // insert sentence and update number of elements
    unsigned int insert_index = sentences->num_elements;
    sentences->contents[insert_index] = sentence;
    sentences->num_elements++;
}

char* get_next_sentence(FILE *fp){
    //allocate sentence buffer
    char* sentence_buff = (char *)malloc(BUFF_SIZE * sizeof(char));
    int i, c;

    for(i = 0; ((c = fgetc(fp)) != EOF); i++){
        //reallocate to accomodate for null character and remaining of sentence
        if (i == BUFF_SIZE - 1){
            //TODO: reallocate buffer (increase size)
        }
        //if at end of sentence, return sentence
        if (c == '.'){
            sentence_buff[i] = c;
            return sentence_buff;
        }
        sentence_buff[i] = c;
    }
    sentence_buff[i + 1] = '\0'; 
    //TODO: clean up excess memory
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

void sort_sentences(sentences_t sentences){
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
        sentences_t sentences;
        initialize_sentences_struct(&sentences);
        insert_sentence(&sentences, "sentence 1");
        insert_sentence(&sentences, "sentence 2");
        insert_sentence(&sentences, "sentence 3");
        insert_sentence(&sentences, "sentence 4");
        printf("Size: %i\n", sentences.size);
        printf("Numelems: %i\n", sentences.num_elements);
        print_sentences(&sentences);
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
