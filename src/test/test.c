#include <stdio.h>
#include <stdbool.h>

extern bool input_test();

extern bool parse_test();

extern bool schedule_test();

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