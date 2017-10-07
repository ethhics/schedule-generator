#include <stdio.h>

extern int input_test();

extern int parse_test();

extern int schedule_test();

int main()
{
	if (input_test())
		puts("Tests of input.c completed successfully.");
	if (parse_test())
		puts("Tests of parse.c completed successfully.");
	if (schedule_test())
		puts("Tests of schedule.c completed successfully.");
	return 0;
}