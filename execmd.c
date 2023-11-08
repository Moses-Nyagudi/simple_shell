#include "main.h"

/**
 * execute_command - Execute a command with arguments using execve
 *
 * This function takes an array of command line arguments, where the first
 * argument is the command to be executed. It attempts to execute the
 * specified command using the `execve` system call. If an error occurs,
 * it prints an error message using `perror`.
 *
 * @arguments: An array of strings representing the command and its arguments.
 */

void execute_command(char **arguments)
{
	char *command = NULL, *actual_command = NULL;

	if (arguments)
	{
		command = arguments[0];
		actual_command = get_location(command);

		if (execve(actual_command, arguments, NULL) == -1)
		{
			perror("Error:");
		}
	}
}
