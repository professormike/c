#include <stdio.h>

struct student {
	char name[50];
	int student_number;
};

int
main(void)
{
	// type name			variable name
	struct student			students[3];
	for (size_t i = 0; i < sizeof students / sizeof *students; i++) {
		printf("Please enter the student's name:\n");
		fgets(students[i].name, sizeof students[i].name, stdin);
		printf("Please enter the student's student number:\n");
		scanf("%d", &students[i].student_number);
		getchar();	// consume the newline character after the number
	}
	for (size_t i = 0; i < sizeof students / sizeof *students; i++) {
		printf("%d\t%s\n", students[i].student_number, students[i].name);
	}
	return 0;
}
