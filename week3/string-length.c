#include <stdio.h>

int
string_length(char const *s)
/*
 * 's' is the pointer to the beginning of a string. It is char const *
 *		to indicate that we promise we will not modify the character
 *		data that we're pointing to
 */
{
	int len = 0;
	while (s[len] != '\0') {		// check for the NUL character
		len++;
	}
	return len;
}

int
main(void)
{
	char x[50];
	fgets(x, sizeof x, stdin);
	printf("%d\n", string_length(x));
	return 0;
}
