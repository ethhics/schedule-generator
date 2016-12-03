/*
 * input.c - Takes raw user input and formats it for use in structs and arrays
 *
 * MIT License - Copyright (c) 2016 Zach Scott
 *
 * This software is subject to the terms and conditions defined in the file
 * 'LICENSE', which should be included with this package.
 */

#include "defs.h"

char* strsplit(char *str, char *token)
{
	/* This is basically a rewrite of strtok() so that it doesn't suck */
	static char *start;
	char *first_instance;
	char *next_char;
	char *initial;

	/* If NULL is passed then use the current location */
	if (str != NULL) start = str;

	/* Set initial to ignore leading whitespace */
	for (initial = start; *initial != '\0'; ++initial) {
		if (*initial != *token) {
			break;
		}
	}

	first_instance = strchr(initial, *token);

	for (next_char = first_instance; *next_char != '\0'; ++next_char) {
		if (*next_char != *token) {
			/* We've found the first character after the split that isn't
			 * the same as the delimiter */
			start = next_char;
			break;
		}
		*next_char = '\0';
	}

	return initial;
}

void split_input_line(char **tokens, char *buffer)
{
	strcpy(tokens[0], strsplit(buffer, " "));
	strcpy(tokens[1], strsplit(NULL, " "));
	strcpy(tokens[2], strsplit(NULL, " "));
	strcpy(tokens[3], strsplit(NULL, " "));
	strcpy(tokens[4], strsplit(NULL, "-"));
	strcpy(tokens[5], strsplit(NULL, "\n"));
}

void parse_copy_tokens(char **tokens, char **prev_tokens)
{
	int i;

	for (i = 0; i < 6; ++i) {
		if (strchr(tokens[i], '~') != NULL) {
			strcpy(tokens[i], prev_tokens[i]);
		}
	}
}
