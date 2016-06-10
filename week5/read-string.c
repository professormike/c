#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *
read_string(void)
/*
 * Read in one line of text from the user and return a pointer to that
 * string. We make NO assumptions on the maximum length of the string.
 * The string will be allocated on the heap
 */
{
	size_t length = 0;
	char *string = malloc(length * sizeof *string);
	char inputted_char;
	while (scanf("%c", &inputted_char) == 1 && inputted_char != '\n') {
		string = realloc(string, ++length * sizeof *string);
		string[length - 1] = inputted_char;
	}
	// NUL-terminate the string and then return it
	string = realloc(string, ++length * sizeof *string);
	string[length - 1] = '\0';
	return string;
}

int
main(void)
{
	// 'array' is a pointer to an array, where each element is a
	// string (i.e., a pointer to an array of characters)
	size_t num_strings = 0;
	char **array = malloc(num_strings * sizeof *array);
	char *inputted_string;
	do {
		inputted_string = read_string();
		array = realloc(array, ++num_strings * sizeof *array);
		array[num_strings - 1] = inputted_string;
	} while (strlen(inputted_string) > 0);	// keep looping while the
											// string is not empty
	// get rid of the last (empty) string
	free(inputted_string);
	array = realloc(array, --num_strings * sizeof *array);

	for (size_t i = 0; i < num_strings; i++) {
		printf("%s\n", array[i]);
	}
	
	for (size_t i = 0; i < num_strings; i++) {
		free(array[i]);
	}
	free(array);
	return 0;
}
