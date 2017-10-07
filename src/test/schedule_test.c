#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../defs.h"

extern int classes_overlap(Class *c1, Class *c2, char day);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
void test_classes_overlap()
{
	Class *c1 = malloc(sizeof(Class));
	Class *c2 = malloc(sizeof(Class));
	Class **cl = malloc(sizeof(Class *) * 2);
	
	c1->days = malloc(sizeof(char) * DAYS_LEN);
	c1->empty = 0;
	c2->days = malloc(sizeof(char) * DAYS_LEN);
	c2->empty = 0;
	strcpy(c1->days, "MWF");
	strcpy(c2->days, "TR");

	cl[0] = c1;
	cl[1] = c2;
	
	assert(classes_overlap(c1, c2, 'M') == 0);
	assert(classes_overlap(c1, c2, 'T') == 0);
	assert(classes_overlap(c1, c2, 'W') == 0);
	assert(classes_overlap(c1, c2, 'R') == 0);
	assert(classes_overlap(c1, c2, 'F') == 0);

	free(c1->days);
	free(c1);
	free(c2->days);
	free(c2);
	free(cl);
}
#pragma clang diagnostic pop

int schedule_test()
{
	/* test_classes_overlap();
	test_entries_overlap();
 	test_schedule_overlap();
	test_schedule_conflict();
	test_get_next_schedule();
	test_print_schedule(); */
	return 1;
}
