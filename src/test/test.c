/*
 * Copyright © 2019 Zach Scott under the MIT License
 *
 * This software is subject to the terms and conditions defined in the file
 * 'LICENSE', which should be included with this package.
 */

#include <stdio.h>
#include <stdbool.h>

extern bool input_test(), parse_test(), schedule_test();

int
main()
{
	printf("input.c - ");
	if (input_test())
		printf("passed!\n");
	printf("parse.c - ");
	if (parse_test())
		printf("passed!\n");
	printf("schedule.c - ");
	if (schedule_test())
		printf("passed!\n");
	return 0;
}
