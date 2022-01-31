/* Program to print all the words that can be typed on
 * alternating hands. */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

char* str_to_lower(char* in) {
	for (char* c = in; *c; c++) {
		*c = tolower((unsigned char)*c);
	}

	return in;
}

/* Macro!!!
 *
 * Because I was too lazy to make a function
 * that takes left and allowed as references... */
#define left_or_right(c_) \
	do { \
		if (strchr(letters_l, (c_))) { \
			left = true; \
		} else if (strchr(letters_r, (c_))) { \
			left = false; \
		} else { \
			allowed = false; \
		} \
	} while (0)

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
			left_or_right(*line);
		}

		size_t len = strlen(line);

		if (line[len - 1] == '\n') { /* Get rid of the newline. */
			line[len - 1] = '\0';
		}

		for (const char* c = line + 1; *c; c++) {
			int old_left = left;
			left_or_right(*c);
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