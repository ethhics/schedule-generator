#include <assert.h>
#include <string.h>

#include "../defs.h"

void update_tokens(char **tok, char **prev)
{
	int i;
	for (i = 0; i < 6; ++i) {
		strcpy(prev[i], tok[i]);
	}
}

int input_test()
{
	char good1[] = "12345 MATH 111 MWF 08:00-08:50\n";
	char copy1[] = "  ~     ~   ~  TR  15:40-16:00\n";
	char good2[] = "33331 ENGR 111  R  23:23-23:59\n";
	char copy2[] = "33332 LANG 253  ~    ~  -  ~  \n";
	char bad1[]  = "0000  MATH 222 MWF 08:00-09:00\n";
	char bad2[]  = "00000 MAT  222 MWF 08:00-09:00\n";

	char *tokens[6];
	char *prev_tokens[6];

	initialize_tokens(tokens);
	initialize_tokens(prev_tokens);

	/* good1 */
	split_input_line(tokens, good1);
	assert(strcmp(tokens[0], "12345") == 0);
	assert(strcmp(tokens[1], "MATH") == 0);
	assert(strcmp(tokens[2], "111") == 0);
	assert(strcmp(tokens[3], "MWF") == 0);
	assert(strcmp(tokens[4], "08:00") == 0);
	assert(strcmp(tokens[5], "08:50") == 0);
	update_tokens(tokens, prev_tokens);

	/* copy1 */
	split_input_line(tokens, copy1);
	parse_copy_tokens(tokens, prev_tokens);
	assert(strcmp(tokens[0], "12345") == 0);
	assert(strcmp(tokens[1], "MATH") == 0);
	assert(strcmp(tokens[2], "111") == 0);
	assert(strcmp(tokens[3], "TR") == 0);
	assert(strcmp(tokens[4], "15:40") == 0);
	assert(strcmp(tokens[5], "16:00") == 0);
	update_tokens(tokens, prev_tokens);

	/* good2 */
	split_input_line(tokens, good2);
	assert(strcmp(tokens[0], "33331") == 0);
	assert(strcmp(tokens[1], "ENGR") == 0);
	assert(strcmp(tokens[2], "111") == 0);
	assert(strcmp(tokens[3], "R") == 0);
	assert(strcmp(tokens[4], "23:23") == 0);
	assert(strcmp(tokens[5], "23:59") == 0);
	update_tokens(tokens, prev_tokens);

	/* copy2 */
	split_input_line(tokens, copy2);
	parse_copy_tokens(tokens, prev_tokens);
	assert(strcmp(tokens[0], "33332") == 0);
	assert(strcmp(tokens[1], "LANG") == 0);
	assert(strcmp(tokens[2], "253") == 0);
	assert(strcmp(tokens[3], "R") == 0);
	assert(strcmp(tokens[4], "23:23") == 0);
	assert(strcmp(tokens[5], "23:59") == 0);
	update_tokens(tokens, prev_tokens);

	/* bad1 */
	split_input_line(tokens, bad1);
	assert(strcmp(tokens[0], "0000") == 0);
	assert(strcmp(tokens[1], "MATH") == 0);
	assert(strcmp(tokens[2], "222") == 0);
	assert(strcmp(tokens[3], "MWF") == 0);
	assert(strcmp(tokens[4], "08:00") == 0);
	assert(strcmp(tokens[5], "09:00") == 0);
	update_tokens(tokens, prev_tokens);

	/* bad2 */
	split_input_line(tokens, bad2);
	assert(strcmp(tokens[0], "00000") == 0);
	assert(strcmp(tokens[1], "MAT") == 0);
	assert(strcmp(tokens[2], "222") == 0);
	assert(strcmp(tokens[3], "MWF") == 0);
	assert(strcmp(tokens[4], "08:00") == 0);
	assert(strcmp(tokens[5], "09:00") == 0);
	update_tokens(tokens, prev_tokens);

	return 1;
}
