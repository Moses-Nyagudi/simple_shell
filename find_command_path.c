#include "main.h"

/**
* get_location - Locates the full path of a command in the PATH environment.
* @command: The command to locate.
*
* Return: A pointer to the full path if found, otherwise NULL.
*/

char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;

	int command_length, directory_length;

	struct stat buffer;

	/*If the command contains a '/' character, assume it's an absolute or*/
	if (strchr(command, '/') != NULL)
	{
		return (strdup(command));
	}

	path = getenv("PATH");
	if (path)
	{
		path_copy = strdup(path);
		command_length = strlen(command);
		path_token = strtok(path_copy, ":");
		while (path_token != NULL)
		{
			directory_length = strlen(path_token);
			file_path = malloc(command_length + directory_length + 2);
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");
			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);
	}
	return (NULL);
}
