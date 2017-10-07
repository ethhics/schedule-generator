/*
 * input.c - Takes raw user input and formats it for use in structs and arrays
 *
 * MIT License - Copyright (c) 2017 Zach Scott
 *
 * This software is subject to the terms and conditions defined in the file
 * 'LICENSE', which should be included with this package.
 */

#include "defs.h"

/***********************************************
 * Name:
 * 	initialize_tokens
 * Description:
 * 	Initializes the tokens in token array
 * Inputs:
 * 	tokens
 * Outputs:
 * 	None
 ***********************************************/
void initialize_tokens(char **tokens)
{
	int i;
	for (i = 0; i < NUM_TOKENS; ++i) {
		tokens[i] = malloc(sizeof(*tokens[i]) * TOKEN_LENGTHS[i]);
	}
}

/***********************************************
 * Name:
 * 	strsplit
 * Description:
 * 	A rewrite of strok(). Doesn't output zero-length tokens when the
 * 	delimeter is repeated
 * Inputs:
 * 	str, token
 * Outputs:
 * 	starting location of next token (char*)
 ***********************************************/
char *strsplit(const char *str, const char token)
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

/***********************************************
 * Name:
 * 	split_input_line
 * Description:
 * 	Splits a line of input into an array of tokens
 * Inputs:
 * 	tokens, buffer
 * Outputs:
 * 	None
 ***********************************************/
void split_input_line(char **tokens, char *buffer)
{
	strcpy(tokens[0], strsplit(buffer, ' '));
	strcpy(tokens[1], strsplit(NULL, ' '));
	strcpy(tokens[2], strsplit(NULL, ' '));
	strcpy(tokens[3], strsplit(NULL, ' '));
	strcpy(tokens[4], strsplit(NULL, '-'));
	strcpy(tokens[5], strsplit(NULL, '\n'));
}

/***********************************************
 * Name:
 * 	parse_copy_tokens
 * Description:
 * 	Replaces copy tokens with the previous token for that slot.
 * Inputs:
 * 	tokens, prev_tokens
 * Outputs:
 * 	None
 ***********************************************/
void parse_copy_tokens(char **tokens, char **prev_tokens)
{
	int i;

	for (i = 0; i < 6; ++i) {
		if (strchr(tokens[i], '~') != NULL) {
			strcpy(tokens[i], prev_tokens[i]);
		}
	}
}
