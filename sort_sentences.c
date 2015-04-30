#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

const int BUFF_SIZE = 4096;

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

    return sentence_buff;
    
}

int main(int argc, char *argv[]){
    char *usage_msg = "usage: sort_sentences <input-file>";
    char *error_msg = "ERROR: %s\n";
    
    // Check for proper command usage
    if (argc != 2){
        printf("%s\n", usage_msg);
        return -1;
    }

    char *filename = argv[1];
    char* current_sentence;
    FILE *fp;

    if ((fp = fopen(filename, "r"))){
        while(!feof(fp)){
            printf("%s\n", get_next_sentence(fp));
        }
    }
    else{
        printf(error_msg, strerror(errno));
        return -1;
    }

    // TODO: check for error
    fclose(fp);
}
