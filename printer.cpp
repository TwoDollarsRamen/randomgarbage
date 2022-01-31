/* Program to print out all the words that can be typed using only
 * the left hand on a standard QWERTY keyboard. */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

char* str_to_lower(char* in) {
	for (char* c = in; *c; c++) {
		*c = tolower((unsigned char)*c);
	}

	return in;
}

int main() {
	FILE* file = fopen("words.txt", "r");
	if (!file) {
		fprintf(stderr, "Failed to read `words.txt'.\n");
		return 1;
	}

	const char* letters = "qazwsxedcrfvtgb";

	char line[1024];

	size_t word_count = 0;

	while (fgets(line, sizeof(line), file)) {
		str_to_lower(line);

		size_t len = strlen(line);

		if (line[len - 1] == '\n') {
			line[len - 1] = '\0';
		}

		bool allowed = true;

		for (const char* c = line; *c; c++) {
			if (!strchr(letters, *c)) {
				allowed = false;
				break;
			}
		}

		if (allowed) {
			printf("%s\n", line);
			word_count++;
		}
	}

	printf("Number of words that can be typed with the left hand: %zu\n", word_count);

	fclose(file);
}