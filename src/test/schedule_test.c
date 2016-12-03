#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../defs.h"

extern Class *get_class_for_day(Entry *e, char day);

void test_gcfd()
{
	Entry *e = (Entry *) malloc(sizeof(Entry));
	Class *c1 = (Class *) malloc(sizeof(Class));
	Class *c2 = (Class *) malloc(sizeof(Class));
	Class **cl = (Class **) malloc(sizeof(Class *) * 2);
	
	c1->days = (char *) malloc(sizeof(char) * DAYS_LEN);
	c1->empty = 0;
	c2->days = (char *) malloc(sizeof(char) * DAYS_LEN);
	c2->empty = 0;
	strcpy(c1->days, "MWF");
	strcpy(c2->days, "TR");

	cl[0] = c1;
	cl[1] = c2;
	
	e->classes = cl;
	e->num_classes = 2;
	assert(strcmp(get_class_for_day(e, 'M')->days, "MWF") == 0);
	assert(strcmp(get_class_for_day(e, 'T')->days, "TR") == 0);
	assert(strcmp(get_class_for_day(e, 'W')->days, "MWF") == 0);
	assert(strcmp(get_class_for_day(e, 'R')->days, "TR") == 0);
	assert(strcmp(get_class_for_day(e, 'F')->days, "MWF") == 0);

	free(c1->days);
	free(c1);
	free(c2->days);
	free(c2);
	free(cl);
	free(e);
}

int main()
{
	test_gcfd(); /*
	test_cto();
	test_sc();
	test_gns();
	test_ps(); */
	puts("Tests of schedule.c completed successfully.");
	return 0;
}
