#include "sentences_util.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

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
        populate_sentences_struct(&sentences, fp);
        sort_sentences(&sentences);
        print_sentences(&sentences);
        deallocate_sentences(&sentences);
    }
    else{
        printf(error_msg, strerror(errno));
        return -1;
    }

    fclose(fp);
    return 0;
}
