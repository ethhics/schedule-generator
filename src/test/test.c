/*
 * Copyright © 2019 Zach Scott under the MIT License
 *
 * This software is subject to the terms and conditions defined in the file
 * 'LICENSE', which should be included with this package.
 */

#include <stdio.h>
#include <stdbool.h>

extern bool input_test();

extern bool parse_test();

extern bool schedule_test();

int
main()
/* run tests */
{
	if (input_test())
		puts("Tests of input.c completed successfully.");
	if (parse_test())
		puts("Tests of parse.c completed successfully.");
	if (schedule_test())
		puts("Tests of schedule.c completed successfully.");
	return 0;
}
