#include "sentences_util.h"

int main(){
	sentences_t sentences;
	initialize_sentences_struct(&sentences);
	insert_sentence(&sentences, "sentence 4");
	insert_sentence(&sentences, "sentence 2");
	insert_sentence(&sentences, "sentence 3");
	insert_sentence(&sentences, "sentence 1");

	printf("Total Size: %i bytes\n", sentences.size);
	printf("Number of Sentences: %i\n", sentences.num_elements);
	print_sentences(&sentences);

	printf("Sorting Sentences...\n");
	sort_sentences(&sentences);
	printf("Done Sorting.\n");
	print_sentences(&sentences);

	return 0;
}


