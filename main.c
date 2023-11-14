#include "main.h"

/**
* main - Entry point of the program
* @argc: Number of command line arguments
* @argv: Array of command line argument strings
*
* Return: Always 0 (Success)
*/
int main(int argc, char **argv)
{
	char *prompt = "#cisfun$ ";

	char *line, **arguments;

	int i;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = read_input(prompt);
		arguments = tokenize_input(line);

		if (arguments[0] != NULL)
		{
			execute_command(arguments);
		}

		free(line);
		for (i = 0; arguments[i] != NULL; i++)
		{
			free(arguments[i]);
		}

		free(arguments);
	}

	return (0);
}
