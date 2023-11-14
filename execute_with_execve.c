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

		/*Check if the command exists before forking*/
		if (actual_command)
		{
			/* Fork only if the command exists*/
			pid_t pid = fork();

			if (pid == -1)
			{
				perror("Error in fork");
			}
			else if (pid == 0)
			{
				/*Child process*/
				if (execve(actual_command, arguments, NULL) == -1)
				{
					perror("Error");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				/*Parent process*/
				int status;

				waitpid(pid, &status, 0);
			}
		}
		else
		{
			fprintf(stderr, "%s: command not found\n", command);
		}
	}
}
