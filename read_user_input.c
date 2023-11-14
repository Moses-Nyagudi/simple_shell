#include "main.h"

/**
* read_input - Reads a line of input from the user
* @prompt: The prompt to display before reading input
*
* Return: A pointer to the input line
*/
char *read_input(const char *prompt)
{
	printf("%s", prompt);
	return (custom_getline());
}
