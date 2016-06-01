#include <ctype.h>
#include <string.h>

char *
first_space(char *s)
{
	size_t len = strlen(s);
	for (size_t i = 0; i < len; i++) {
		if (isspace(s[i])) {
			return &s[i];
		}
	}
	return NULL;
	/*
	while (*s != '\0') {
		if (isspace(*s)) {
			return s;
		} else {
			s++;
		}
	}
	return NULL;
	*/
}
