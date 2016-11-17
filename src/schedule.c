/*
 * schedule.c - Handles schedules and their operations
 *
 * MIT License - Copyright (c) 2016 Zach Scott
 *
 * This software is subject to the terms and conditions defined in the file
 * 'LICENSE', which should be included with this package.
 */

#include "defs.h"

Class* get_class_for_day(Entry *e, char day)
{
	Class **classes = e->classes;
	unsigned int i;
	for (i = 0; i < e->num_classes; ++i) {
		if (classes[i] == NULL) { continue; }
		if (strchr(classes[i]->days, day) != NULL) {
			return classes[i];
		}
	}
	return NULL;
}

int class_times_overlap(Class *c1, Class *c2)
{
	Time *s1, *e1, *s2, *e2;
	
	s1 = c1->start;
	e1 = c1->end;
	s2 = c2->start;
	e2 = c2->end;

	if (s1->H > e2->H || s2->H > e1->H) {
		return 0;
	} else if (s1->H == e2->H) {
		if (s1->M > e2->M) {
			return 0;
		}
	} else if (s2->H == e1->H) {
		if (s2->M > e1->M) {
			return 0;
		}
	}
	return 1;
}

int schedule_conflict(Schedule *sched)
{
	Entry **schedule = sched->entries;
	unsigned int i, j, k;
	char days[] = "MTWRF";

	for (i = 0; i < strlen(days); ++i) {
		/* Iterate over each day */
		for (j = 0; j < sched->num_entries; ++j) {
			if (schedule[j] == NULL) { continue; }
			for (k = j+1; k < sched->num_entries; ++k) {
				/* Pick 2 entities, get their class for the current day, and
				 * if the times overlap return 1 (they do conflict) */
				Class *c1 = get_class_for_day(schedule[j], days[i]);
				Class *c2 = get_class_for_day(schedule[k], days[i]);
				if (c1 == NULL || c2 == NULL) {
					continue;
				}
				if (class_times_overlap(c1, c2) == 1) {
					return 1;
				}
			}
		}
	}
	return 0;
}

void* get_next_schedule(Schedule *sched, List *course_list)
{
	Course **courses = course_list->courses;
	Entry **schedule = sched->entries;
	unsigned int i;
	int increment_flag = 1;
	static int first_time = 1;

	sched->num_entries = course_list->num_courses;

	if (first_time) {
		for (i = 0; i < course_list->num_courses; ++i) {
			schedule[i] = courses[i]->entries[0];
		}
		first_time = 0;
		return (void*) 0x1;
	}

	for (i = 0; i < course_list->num_courses; ++i) {
		if (increment_flag) {
			courses[i]->selected_entry++;
			increment_flag = 0;
		}
		/* If current course has reached last entry, reset and increment next */
		if (courses[i]->selected_entry == courses[i]->num_entries) {
			if (i == course_list->num_courses - 1) {
				/* If this is the last course and we're at the last entry and
				 * trying to increment again, we've reached the end. Return */
				return NULL;
			}
			courses[i]->selected_entry = 0;
			increment_flag = 1;	
		}
		schedule[i] = courses[i]->entries[courses[i]->selected_entry];
	}
	return (void*) 0x1;
}

void print_schedule(Schedule *sched)
{
	Entry **schedule = sched->entries;
	unsigned int i, j;
	Class **classes;

	puts("~~~~~~~POTENTIAL SCHEDULE~~~~~~~");
	for (i = 0; i < sched->num_entries; ++i) {
		classes = schedule[i]->classes;
		printf("%s %d: %d\n", schedule[i]->dept, schedule[i]->course, schedule[i]->id);
		for (j = 0; j < schedule[i]->num_classes; ++j) {
			if (classes[j] == NULL) { continue; }
			printf("\t%-3s %02d:%02d-%02d:%02d\n", classes[j]->days,
			       classes[j]->start->H, classes[j]->start->M,
			       classes[j]->end->H, classes[j]->end->M);
		}
	}
	puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
}
