/*
 * input.c - Takes raw user input and formats it for use in structs and arrays
 *
 * MIT License - Copyright (c) 2016 Zach Scott
 *
 * This software is subject to the terms and conditions defined in the file
 * 'LICENSE', which should be included with this package.
 */

#include "defs.h"

void split_input_line(char **tokens, char *buffer)
{
	tokens[0] = strtok(buffer, " ");
	tokens[1] = strtok(NULL, " ");
	tokens[2] = strtok(NULL, " ");
	tokens[3] = strtok(NULL, " ");
	tokens[4] = strtok(NULL, "-");
	tokens[5] = strtok(NULL, "\n");
}

void parse_copy_tokens(char **tokens, char **prev_tokens)
{
	int i;

	for (i = 0; i < 6; ++i) {
		if (strchr(tokens[i], '~') != NULL) {
			/* So if this is the case, don't have room to copy the token.
			 * Instead, have it point to the previous */
			tokens[i] = prev_tokens[i];
		}
	}
}
