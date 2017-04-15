/*
 * main.c - Controls the flow of the program
 *
 * MIT License - Copyright (c) 2017 Zach Scott
 *
 * This software is subject to the terms and conditions defined in the file
 * 'LICENSE', which should be included with this package.
 */

#include "defs.h"

void clean_up(List *course_list, Schedule *sched)
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

	free(sched->entries);
	free(sched);
}

void safe_fputs(char *str, FILE *f)
{
	if (f != NULL) {
		fputs(str, f);
	}
}

int main(int argc, char *argv[])
{
	char buffer[256];
	List *course_list;
	Course *cur_course;
	Entry *cur_entry;
	Class *cur_class;
	char **line_tokens;
	char **previous_tokens;
	unsigned int i;
	int j;
	Schedule *cur_schedule;
	int using_file = (argc == 2);
	FILE *input_location = stdin;
	FILE *output_location = stdout;

	if (using_file) {
		/* Read from file */
		input_location = fopen(argv[1], "r");
		/* Output "input" text to nowhere */
		output_location = NULL;
	}
	safe_fputs("How many courses are you taking? ", output_location);
	fgets(buffer, 255, input_location);
	j = atoi(buffer);
	if (j < 0) {
		puts("You can't have negative courses!");
		return -1;
	}
	course_list = (List *) malloc(sizeof(List));
	course_list->num_courses = (unsigned int) j;
	course_list->courses = (Course **) malloc(sizeof(Course *) * course_list->num_courses);
	for (i = 0; i < course_list->num_courses; ++i) {
		course_list->courses[i] = (Course *) malloc(sizeof(Course));
		course_list->courses[i]->empty = 1;
	}

	safe_fputs("Enter a class in this format:\n", output_location);
	safe_fputs("00000 ABCD 123 MWF 08:00-08:50\n", output_location);
	safe_fputs("You can copy a section from the one above by using '~'\n", output_location);
	safe_fputs("Type 'done' when finished.\n", output_location);

	line_tokens = (char **) malloc(sizeof(char *) * NUM_TOKENS);
	previous_tokens = (char **) malloc(sizeof(char *) * NUM_TOKENS);
	for (i = 0; i < NUM_TOKENS; ++i) {
		line_tokens[i] = (char *) malloc(sizeof(char) * TOKEN_LENGTHS[i]);
		previous_tokens[i] = (char *) malloc(sizeof(char) * TOKEN_LENGTHS[i]);
	}

	/* Get and parse input */
	while (1) {
		fgets(buffer, 255, input_location);

		/* If it's empty, end the loop */
		if (strcmp(buffer, "done\n") == 0) {
			break;
		}

		split_input_line(line_tokens, buffer);
		parse_copy_tokens(line_tokens, previous_tokens);

		/* Get a course */
		cur_course = get_course(course_list, line_tokens);

		/* Get an entry from the course */
		cur_entry = get_entry(cur_course, line_tokens);

		/* Add a class for the entry */
		cur_class = get_class(cur_entry, line_tokens);

		if (cur_class == NULL) {
			/* This class has already been entered */
			puts("You've already entered that class!");
		}

		/* Update the previous tokens for next loop */
		for(i = 0; i < NUM_TOKENS; ++i) {
			strcpy(previous_tokens[i], line_tokens[i]);
		}
	}
	if (argc == 2) { fclose(input_location); }
	for (i = 0; i < NUM_TOKENS; ++i) {
		free(line_tokens[i]);
		free(previous_tokens[i]);
	}
	free(line_tokens);
	free(previous_tokens);

	/* Generate some schedules */
	puts("Generating schedules...");
	cur_schedule = (Schedule *) malloc(sizeof(Schedule));
	cur_schedule->entries = (Entry **) malloc(sizeof(Entry *) * course_list->num_courses);

	while (get_next_schedule(cur_schedule, course_list)) {
		if (schedule_conflict(cur_schedule) == 0) {
			print_schedule(cur_schedule);
		}
	}

	/* Clean up */
	clean_up(course_list, cur_schedule);

	return 0;
}
