/* Program to print all the words that can be typed on
 * alternating hands. */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

static char* str_to_lower(char* in) {
	for (char* c = in; *c; c++) {
		*c = tolower((unsigned char)*c);
	}

	return in;
}

static void check_hand(const char* letters_l, const char* letters_r, char c, char* left, bool* allowed) {
	if (strchr(letters_l, c)) { 
		*left = true; 
	} else if (strchr(letters_r, c)) { 
		*left = false; 
	} else { 
		*allowed = false; 
	}
}

int main() {
	FILE* file = fopen("words.txt", "r");
	if (!file) {
		fprintf(stderr, "Failed to read `words.txt'.\n");
		return 1;
	}

	const char* letters_l = "qazwsxedcrfvtgb";
	const char* letters_r = "yhnujmikolp";

	char line[1024];

	size_t word_count = 0;

	char left = 2;
	while (fgets(line, sizeof(line), file)) {
		str_to_lower(line);

		bool allowed = true;

		if (left == 2) {
			check_hand(letters_l, letters_r, *line, &left, &allowed);
		}

		size_t len = strlen(line);

		if (line[len - 1] == '\n') { /* Get rid of the newline. */
			line[len - 1] = '\0';
		}

		for (const char* c = line + 1; *c; c++) { /* First character has already been checked. */
			int old_left = left;
			check_hand(letters_l, letters_r, *c, &left, &allowed);
			if (old_left == left) {
				allowed = false;
			}
		}

		if (allowed) {
			printf("%s\n", line);
			word_count++;
		}
	}

	printf("Number of words that can be typed with alternating hands: %zu\n", word_count);

	fclose(file);
}