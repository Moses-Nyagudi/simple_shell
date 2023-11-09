#include "main.h"

/**
 * main - Simple shell implementation.
 *
 * @argc: Number of command line arguments.
 * @argv: Array of command line arguments.
 *
 * @return: 0 on success.
 */

int main(int argc, char **argv)
{
    char *prompt = "(Enter your command) $ ";
    char *line = NULL, *line_copy = NULL;
    size_t line_length = 0;
    ssize_t chars_read;
    const char *delimiters = " \n";
    int i, num_tokens = 0;
    char **arguments, *token;

    /* Suppress unused variable warning */
    (void)argc;
    (void)argv;

    while (1)
    {
        printf("%s", prompt);
        chars_read = getline(&line, &line_length, stdin);

        if (chars_read == -1)
        {
            printf("Exiting shell...\n");
            break;
        }

        line_copy = strdup(line);

        token = strtok(line, delimiters);

        while (token != NULL)
        {
            num_tokens++;
            token = strtok(NULL, delimiters);
        }
        num_tokens++;

        arguments = (char **)malloc(sizeof(char *) * (num_tokens + 1));

        token = strtok(line_copy, delimiters);

        for (i = 0; token != NULL; i++)
        {
            arguments[i] = strdup(token);
            token = strtok(NULL, delimiters);
        }
        arguments[i] = NULL;

        execute_command(arguments);

    
        free(line_copy);
        for (i = 0; i < num_tokens; i++)
        {
            free(arguments[i]);
        }
        free(arguments);
    }


    free(line);

    return 0;
}
