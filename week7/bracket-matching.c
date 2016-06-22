#include <stdio.h>
#include <stdlib.h>

struct stack {
	char *brackets;
	size_t num_brackets;
};

void
push(struct stack *s, char bracket)
{
	s->brackets = realloc(s->brackets, ++s->num_brackets *
		sizeof *s->brackets);
	s->brackets[s->num_brackets - 1] = bracket;
}

char
pop(struct stack *s)
{
	if (s->num_brackets == 0) {
		return '\0';	// return NUL character
	}
	char bracket = s->brackets[s->num_brackets - 1];
	s->brackets = realloc(s->brackets, --s->num_brackets *
		sizeof *s->brackets);
	return bracket;
}

int
main(void)
{
	struct stack s = { .brackets = malloc(0), .num_brackets = 0 };
	char c;
	while (scanf("%c", &c) == 1 && c != '\n') {
		if (c == '(' || c == '[') {
			push(&s, c);
		} else if (c == ')') {
			if (pop(&s) != '(') {
				printf("bad\n");
				free(s.brackets);
				return 0;
			}
		} else if (c == ']') {
			if (pop(&s) != '[') {
				printf("bad\n");
				free(s.brackets);
				return 0;
			}
		}
	}
	if (s.num_brackets == 0) {
		printf("good\n");
	} else {
		printf("bad\n");
	}
	free(s.brackets);
	return 0;
}




