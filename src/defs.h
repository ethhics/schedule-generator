/*
 * Copyright © 2019 Zach Scott under the MIT License
 *
 * This software is subject to the terms and conditions defined in the file
 * 'LICENSE', which should be included with this package.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ENTRIES 256
#define MAX_CLASSES 256

#define NUM_TOKENS 6
#define ID_LEN 7
#define DEPT_LEN 7
#define COURSE_LEN 7
#define DAYS_LEN 7
#define START_LEN 7
#define END_LEN 7

static const long unsigned int TOKEN_LENGTHS[] = {ID_LEN, DEPT_LEN,
						  COURSE_LEN, DAYS_LEN,
						  START_LEN, END_LEN};

typedef struct
{
	unsigned int H, M;
} Time;

typedef struct
{
	bool empty;

	char *days;
	Time *start;
	Time *end;
} Class;

typedef struct
{
	bool empty;

	int id;
	char *dept;
	int course;

	unsigned int num_classes;
	Class **classes;
} Entry;

typedef struct
{
	bool empty;

	char *dept;
	int course;

	unsigned int selected_entry;
	unsigned int num_entries;
	Entry **entries;
} Course;

typedef struct
{
	unsigned int num_courses;
	Course **courses;
} List;

typedef struct
{
	unsigned int num_entries;
	Entry **entries;
} Schedule;

/* input.c global functions */
void initialize_tokens(char **tokens);

char *strsplit(const char *str, char token);

void split_input_line(char **tokens, char *buffer);

void parse_copy_tokens(char **tokens, char **prev_tokens);

/* parse.c global functions */
bool is_empty(void *thing);

void parse_time(Time *t, char *str);

Course *get_course(List *course_list, char **tokens);

Entry *get_entry(Course *course, char **tokens);

Class *get_class(Entry *entry, char **tokens);

/* schedule.c global functions */
int get_next_schedule(Schedule *schedule, List *course_list);

bool schedule_conflict(Schedule *schedule);

void print_schedule(Schedule *schedule);
