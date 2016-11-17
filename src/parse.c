/*
 * parse.c - Parses formatted user input into usable structs and arrays
 *
 * MIT License - Copyright (c) 2016 Zach Scott
 *
 * This software is subject to the terms and conditions defined in the file
 * 'LICENSE', which should be included with this package.
 */

#include "defs.h"

/* TOKENS STRUCTURE:
 * ID DEPT COURSE DAYS START-END
 * [0] [1]   [2]  [3]  [4]   [5] */

void parse_time(Time *t, char *str)
{
	int H = atoi(strtok(str, ":"));
	int M = atoi(strtok(NULL, ""));

	if (H < 0) { H = 0; }
	if (M < 0) { M = 0; }

	t->H = (unsigned int) H;
	t->M = (unsigned int) M;
}

Course* get_course(List *course_list, char **tokens)
{
	Course **courses = course_list->courses;
	Course *cur_course;
	unsigned int i;
	int first_empty = -1;
	char *dept = tokens[1];
	int course = atoi(tokens[2]);

	for (i = 0; i < course_list->num_courses; ++i) {
		cur_course = courses[i];
		if (cur_course->dept == NULL) {
			if (first_empty == -1) { first_empty = (int) i; }
			continue;
		}
		if (strcmp(cur_course->dept, dept) == 0) {
			if (cur_course->course == course) {
				/* We already have this course! */
				return cur_course;
			}
		}
	}

	/* The course isn't in our list yet, so make it, add it, and return it */
	cur_course = (Course*) malloc(sizeof(Course));
	cur_course->dept = (char*) malloc(sizeof(char) * DEPT_LEN);
	strcpy(cur_course->dept, dept);
	cur_course->course = course;
	cur_course->entries = (Entry**) malloc(sizeof(Entry*) * MAX_ENTRIES);
	cur_course->num_entries = 0;

	courses[first_empty] = cur_course;

	return cur_course;
}

Entry* get_entry(Course *course, char **tokens)
{
	Entry **entries = course->entries;
   	Entry *cur_entry;
	unsigned int i;
	int first_empty = -1;
	int id = atoi(tokens[0]);

	for (i = 0; i < MAX_ENTRIES; ++i) {
		cur_entry = entries[i];
		if (cur_entry == NULL) {
			if (first_empty == -1) { first_empty = (int) i; }
			continue;
		}
		if (cur_entry->id == id) {
			/* We already have this entry! */
			return cur_entry;
		}
	}

	/* The entry isn't in our list yet, so make it, add it, and return it */
	cur_entry = (Entry*) malloc(sizeof(Entry));
	cur_entry->id = id;
	cur_entry->classes = (Class**) malloc(sizeof(Class*) * MAX_CLASSES);
	cur_entry->num_classes = 0;
	cur_entry->dept = (char*) malloc(sizeof(char) * DEPT_LEN);
	strcpy(cur_entry->dept, course->dept);
	cur_entry->course = course->course;

	entries[first_empty] = cur_entry;
	course->num_entries++;

	return cur_entry;
}

Class* get_class(Entry *entry, char **tokens)
{
	Class **classes = entry->classes;
   	Class *cur_class;
	unsigned int i;
	int first_empty = -1;
	char *days = tokens[3];
	char *start_str = tokens[4];
	char *end_str = tokens[5];
	Time *start, *end;
	start = (Time*) malloc(sizeof(Time));
	end = (Time*) malloc(sizeof(Time));
	parse_time(start, start_str);
	parse_time(end, end_str);

	for (i = 0; i < MAX_CLASSES; ++i) {
		cur_class = classes[i];
		if (cur_class == NULL) { 
			if (first_empty == -1) { first_empty = (int) i; }
			continue;
		}
		if (strcmp(cur_class->days, days) == 0) {
			if (cur_class->start->H == start->H &&
			    cur_class->start->M == start->M) {
				if (cur_class->end->H == end->H &&
					cur_class->end->M == end->M) {
					/* We already have this class! Though we shouldn't... */
					free(start);
					free(end);
					return NULL;
				}
			}
		}
	}

	/* The entry isn't in our list yet, so make it, add it, and return it */
	cur_class = (Class*) malloc(sizeof(Class));
	cur_class->days = (char*) malloc(sizeof(char) * 6);
	strcpy(cur_class->days, days);
	cur_class->start = start;
	cur_class->end = end;

	classes[first_empty] = cur_class;
	entry->num_classes++;

	return cur_class;
}
