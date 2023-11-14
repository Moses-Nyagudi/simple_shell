#include "main.h"

/**
* read_input - Reads a line of input from the user
* @prompt: The prompt to display before reading input
*
* Return: A pointer to the input line
*/
char *read_input(const char *prompt)
{
	char *line = NULL;

	size_t line_length = 0;
	ssize_t chars_read;

	printf("%s", prompt);
	chars_read = getline(&line, &line_length, stdin);


	if (chars_read == -1)
	{
		perror("Error");
		free(line);
		exit(0);
	}

	if (line[chars_read - 1] == '\n')
	{
		line[chars_read - 1] = '\0';
	}

	return (line);
}
