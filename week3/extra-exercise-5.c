#include <ctype.h>

char *
first_space(char *s)
{
	while (*s != '\0') {
		if (isspace(*s)) {
			return s;
		} else {
			s++;
		}
	}
	return NULL;
}
