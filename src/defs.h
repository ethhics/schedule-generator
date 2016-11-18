/*
 * defs.h - Defines all functions, structs, and constants used in the software
 *
 * MIT License - Copyright (c) 2016 Zach Scott
 *
 * This software is subject to the terms and conditions defined in the file
 * 'LICENSE', which should be included with this package.
 */

#ifndef SCHEDULE_HEADER
#define SCHEDULE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 256
#define MAX_CLASSES 256

#define NUM_TOKENS 6
#define DEPT_LEN 5
#define DAYS_LEN 4

typedef struct {
	unsigned int H, M;
} Time;

typedef struct {
	char *days;
	Time *start, *end;
} Class;

typedef struct {
	int id;
	char *dept;
	int course;

	unsigned int num_classes;
	Class **classes;
} Entry;

typedef struct {
	char *dept;
	int course;

	unsigned int selected_entry;
	unsigned int num_entries;
	Entry **entries;
} Course;

typedef struct {
	unsigned int num_courses;
	Course **courses;
} List;

typedef struct {
	unsigned int num_entries;
	Entry **entries;
} Schedule;

/* input.c */
void split_input_line(char **tokens, char *buffer);
void parse_copy_tokens(char **tokens, char **prev_tokens);

/* parse.c */
Course* get_course(List *course_list, char **tokens);
Entry* get_entry(Course *course, char **tokens);
Class* get_class(Entry *entry, char **tokens);

/* schedule.c */
void* get_next_schedule(Schedule *schedule, List *course_list);
int schedule_conflict(Schedule *schedule);
void print_schedule(Schedule *schedule);

#endif
