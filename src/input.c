/*
 * Copyright © 2019 Zach Scott under the MIT License
 *
 * This software is subject to the terms and conditions defined in the file
 * 'LICENSE', which should be included with this package.
 */

#include "defs.h"

void
initialize_tokens(char **tokens)
/* initialize the tokens in a token array */
{
	int i;
	for (i = 0; i < NUM_TOKENS; ++i) {
		tokens[i] = malloc(sizeof(*tokens[i]) * TOKEN_LENGTHS[i]);
	}
}

char *
strsplit(const char *str, const char token)
/* strtok() without zero-length tokens on delimeter repeat */
{
	/* This is basically a rewrite of strtok() so that it doesn't suck */
	static char *start;
	char *first_instance;
	char *next_char;
	char *initial;

	/* If NULL is passed then use the current location */
	if (str != NULL) {
		start = malloc(sizeof(*start) * (strlen(str) + 1));
		strcpy(start, str);
	}

	/* Set initial to ignore leading whitespace */
	for (initial = start; *initial != '\0'; ++initial) {
		if (*initial != token) {
			break;
		}
	}

	first_instance = strchr(initial, token);
	if (first_instance == NULL)
		first_instance = initial;

	for (next_char = first_instance; *next_char != '\0'; ++next_char) {
		if (*next_char != token) {
			/* We've found the first character after the split that isn't
			 * the same as the delimiter */
			start = next_char;
			break;
		}
		*next_char = '\0';
	}

	return initial;
}

void
split_input_line(char **tokens, char *buffer)
/* lex a line of input into a token array */
{
	strcpy(tokens[0], strsplit(buffer, ' '));
	strcpy(tokens[1], strsplit(NULL, ' '));
	strcpy(tokens[2], strsplit(NULL, ' '));
	strcpy(tokens[3], strsplit(NULL, ' '));
	strcpy(tokens[4], strsplit(NULL, '-'));
	strcpy(tokens[5], strsplit(NULL, '\n'));
}

void
parse_copy_tokens(char **tokens, char **prev_tokens)
/* replaces copy tokens with the correct previous value */
{
	int i;

	for (i = 0; i < 6; ++i) {
		if (strchr(tokens[i], '~') != NULL) {
			strcpy(tokens[i], prev_tokens[i]);
		}
	}
}
