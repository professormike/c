#include <stdio.h>
#include <string.h>

int
main(void)
{
	char s[100];
	fgets(s, sizeof s, stdin);
	s[strlen(s) - 1] = '\0';	// get rid of the annoying newline
	for (size_t i = strlen(s) - 1; i >= 0; i--) {
		printf("%c", s[i]);
	}
	printf("\n");
	return 0;
}
