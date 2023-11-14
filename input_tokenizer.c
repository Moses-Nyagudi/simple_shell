
#include "main.h"

/**
* tokenize_input - Tokenizes the input string into an array of strings
* @input: The input string to be tokenized
*
* Return: An array of strings containing the tokens
*/

char **tokenize_input(char *input)
{
	int i, num_tokens = 0;

	const char *delimiters = " \n";

	char **arguments, *token, *input_copy;

	input_copy = strdup(input);
	token = strtok(input, delimiters);
	while (token != NULL)
	{
		num_tokens++;
		token = strtok(NULL, delimiters);
	}

	num_tokens++;
	arguments = (char **)malloc(sizeof(char *) * (num_tokens + 1));
	token = strtok(input_copy, delimiters);
	for (i = 0; token != NULL; i++)
	{
		arguments[i] = strdup(token);
		token = strtok(NULL, delimiters);
	}

	arguments[i] = NULL;
	free(input_copy);

	return (arguments);
}
