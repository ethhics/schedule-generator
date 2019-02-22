/*
 * Copyright © 2019 Zach Scott under the MIT License
 *
 * This software is subject to the terms and conditions defined in the file
 * 'LICENSE', which should be included with this package.
 */

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../defs.h"

extern int classes_overlap(Class *c1, Class *c2, char day);

void test_classes_overlap()
{
	Class *c1 = malloc(sizeof(*c1));
	Class *c2 = malloc(sizeof(*c2));
	Class **cl = malloc(sizeof(*cl) * 2);

	c1->days = malloc(sizeof(*c1->days) * DAYS_LEN);
	c1->empty = 0;
	c2->days = malloc(sizeof(*c2->days) * DAYS_LEN);
	c2->empty = 0;
	strcpy(c1->days, "MWF");
	strcpy(c2->days, "TR");

	cl[0] = c1;
	cl[1] = c2;

	assert(!classes_overlap(c1, c2, 'M'));
	assert(!classes_overlap(c1, c2, 'T'));
	assert(!classes_overlap(c1, c2, 'W'));
	assert(!classes_overlap(c1, c2, 'R'));
	assert(!classes_overlap(c1, c2, 'F'));

	free(c1->days);
	free(c1);
	free(c2->days);
	free(c2);
	free(cl);
}

bool schedule_test()
{
	/* TODO: write all schedule tests */
	/* test_classes_overlap();
	test_entries_overlap();
 	test_schedule_overlap();
	test_schedule_conflict();
	test_get_next_schedule();
	test_print_schedule(); */
	return true;
}
