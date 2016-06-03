#include <stdio.h>
#include <stdlib.h>	// for malloc()
#include <string.h>	// for strncpy()
#include <stdbool.h>	// for the constant "true"

struct student {
	char name[50];
	int student_no;
	double percentage;	// the student's grade, from 0 to 100
};

struct student *
new_student(char const *name, int no, double perc)
{
	struct student *s = malloc(sizeof *s);
	s->student_no = no;
	s->percentage = perc;
	strncpy(s->name, name, sizeof s->name);	// copy the string into s->name
	return s;
}

char
letter_grade(struct student const *s)
{
	if (s->percentage >= 80) {
		return 'A';
	} else if (s->percentage >= 70) {
		return 'B';
	} else if (s->percentage >= 60) {
		return 'C';
	} else if (s->percentage >= 50) {
		return 'D';
	} else {
		return 'F';
	}
}

int
main(void)
{
	while (true) {
		printf("Enter the student's name: ");
		char name[50];
		fgets(name, sizeof name, stdin);
		if (name[1] == '\0') {	// user just hit enter
			break;
		}
		printf("Enter the student number: ");
		int no;
		scanf("%d", &no);
		printf("Enter the grade (0-100): ");
		double perc;
		scanf("%lf", &perc);
		getchar();	// consume the newline character after the number
		struct student *s = new_student(name, no, perc);
		printf("%c\t%d\t%s\n", letter_grade(s), s->student_no, s->name);
		free(s);
		free(s);
	}
	return 0;
}






