/*
 * Copyright © 2019 Zach Scott under the MIT License
 *
 * This software is subject to the terms and conditions defined in the file
 * 'LICENSE', which should be included with this package.
 */

#include "defs.h"

bool
classes_overlap(Class *c1, Class *c2, char day)
/* checks if classes have overlapping times */
{
	Time *s1, *e1, *s2, *e2;

	if (is_empty(c1) || is_empty(c2)) { return 0; }
	if (strchr(c1->days, day) == NULL || strchr(c2->days, day) == NULL) {
		return false;
	}

	s1 = c1->start;
	e1 = c1->end;
	s2 = c2->start;
	e2 = c2->end;

	if (s1->H > e2->H || s2->H > e1->H) {
		return 0;
	} else if (s1->H == e2->H) {
		if (s1->M > e2->M) {
			return false;
		}
	} else if (s2->H == e1->H) {
		if (s2->M > e1->M) {
			return false;
		}
	}
	return true;
}

bool
entries_overlap(Entry *e1, Entry *e2, char day)
/* checks if entries have overlapping classes */
{
	Class **classes1 = e1->classes;
	Class **classes2 = e2->classes;
	unsigned int i, j;

	if (is_empty(e1) || is_empty(e2)) { return 0; }
	for (i = 0; i < e1->num_classes; ++i) {
		for (j = 0; j < e2->num_classes; ++j) {
			if (classes_overlap(classes1[i], classes2[j], day)) {
				return true;
			}
		}
	}
	return false;
}


bool
schedule_overlap(Schedule *sched, char day)
/* checks if a schedule has overlaps on the given day */
{
	Entry **schedule = sched->entries;
	unsigned int i, j;
	for (i = 0; i < sched->num_entries; ++i) {
		for (j = i + 1; j < sched->num_entries; ++j) {
			if (entries_overlap(schedule[i], schedule[j], day)) {
				return 1;
			}
		}
	}
	return 0;
}

bool
schedule_conflict(Schedule *sched)
/* checks if a schedule has conflicts */
{
	unsigned int i;
	char days[] = "MTWRF";

	for (i = 0; i < strlen(days); ++i) {
		/* Iterate over each day */
		if (schedule_overlap(sched, days[i])) {
			return true;
		}
	}
	return false;
}

int
get_next_schedule(Schedule *sched, List *course_list)
/* gets the next schedule */
{
	Course **courses = course_list->courses;
	Entry **schedule = sched->entries;
	unsigned int i;
	bool increment_flag = true;
	static bool first_time = true;

	sched->num_entries = course_list->num_courses;

	if (first_time) {
		for (i = 0; i < course_list->num_courses; ++i) {
			schedule[i] = courses[i]->entries[0];
			courses[i]->selected_entry = 0;
		}
		first_time = false;
		return 1;
	}

	for (i = 0; i < course_list->num_courses; ++i) {
		if (increment_flag) {
			courses[i]->selected_entry++;
			increment_flag = false;
		}
		/* If current course has reached last entry,
		 * reset and increment next */
		if (courses[i]->selected_entry == courses[i]->num_entries) {
			if (i == course_list->num_courses - 1) {
				/* If this is the last course
				 * and we're at the last entry and
				 * trying to increment again,
				 * we've reached the end. Return */
				return 0;
			}
			courses[i]->selected_entry = 0;
			increment_flag = true;
		}
		schedule[i] = courses[i]->entries[courses[i]->selected_entry];
	}
	return 1;
}

void
print_schedule(Schedule *sched)
/* prints a schedule */
{
	Entry **schedule = sched->entries;
	unsigned int i, j;
	Class **classes;

	puts("~~~~~~~POTENTIAL SCHEDULE~~~~~~~");
	for (i = 0; i < sched->num_entries; ++i) {
		classes = schedule[i]->classes;
		printf("%s %d: %d\n", schedule[i]->dept, schedule[i]->course,
		       schedule[i]->id);
		for (j = 0; j < schedule[i]->num_classes; ++j) {
			if (classes[j] == NULL) { continue; }
			printf("\t%-3s %02d:%02d-%02d:%02d\n", classes[j]->days,
			       classes[j]->start->H, classes[j]->start->M,
			       classes[j]->end->H, classes[j]->end->M);
		}
	}
	puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
}
