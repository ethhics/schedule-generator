#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../defs.h"

void clean_up(List *course_list)
{
	Course *cur_course;
	Entry **cur_entries;
	Entry *cur_entry;
	Class **cur_classes;
	Class *cur_class;
	unsigned int i, j, k;

	for (i = 0; i < course_list->num_courses; ++i) {
		cur_course = course_list->courses[i];

		if (!is_empty(cur_course)) {
			cur_entries = cur_course->entries;
			for (j = 0; j < MAX_ENTRIES; ++j) {
				cur_entry = cur_entries[j];

				if (!is_empty(cur_entry)) {
					cur_classes = cur_entry->classes;
					for (k = 0; k < MAX_CLASSES; ++k) {
						cur_class = cur_classes[k];

						if (!is_empty(cur_class)) {
							free(cur_class->days);
							free(cur_class->start);
							free(cur_class->end);
						}

						free(cur_class);
					}
					free(cur_entry->dept);
					free(cur_entry->classes);
				}

				free(cur_entry);
			}
			free(cur_course->dept);
			free(cur_course->entries);
		}

		free(cur_course);
	}
	free(course_list->courses);
	free(course_list);
}

int main()
{
	char goodt1[] = "12:34";
	char goodt2[] = "23:45";
	char badt1[]  = "24:00";
	char badt2[]  = "14:60";

	List *l = (List*) malloc(sizeof(List));
	Course *c;
	Entry *e;
	Class *cl;

	Time *t = (Time*) malloc(sizeof(Time));

	char tok1[] = "11111";
	char tok2[] = "MATH";
	char tok3[] = "111";
	char tok4[] = "MWF";
	char tok5[] = "08:00";
	char tok6[] = "08:50";

	char *tokens[6];
	tokens[0] = tok1;
	tokens[1] = tok2;
	tokens[2] = tok3;
	tokens[3] = tok4;
	tokens[4] = tok5;
	tokens[5] = tok6;

	parse_time(t, goodt1);
	assert(t->H == 12);
	assert(t->M == 34);

	parse_time(t, goodt2);
	assert(t->H == 23);
	assert(t->M == 45);

	parse_time(t, badt1);
	assert(t->H == 24);
	assert(t->M == 0);
	
	parse_time(t, badt2);
	assert(t->H == 14);
	assert(t->M == 60);

	free(t);

	l->num_courses = 1;
	l->courses = (Course**) malloc(sizeof(Course*));
	l->courses[0] = (Course*) malloc(sizeof(Course));
	l->courses[0]->empty = 1;

	c = get_course(l, tokens);
	assert(strcmp(c->dept, "MATH") == 0);
	assert(c->course == 111);
	e  = get_entry(c, tokens);
	assert(e->id == 11111);
	assert(strcmp(e->dept, "MATH") == 0);
	assert(e->course == 111);
	cl = get_class(e, tokens);
	assert(strcmp(cl->days, "MWF") == 0);
	assert(cl->start->H == 8);
	assert(cl->start->M == 0);
	assert(cl->end->H == 8);
	assert(cl->end->M == 50);

	clean_up(l);

	puts("Tests of parse.c completed successfully.");
	return 0;
}
