#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

void execute_command(char **arguments);
char *get_location(char *command);
char **tokenize_input(char *input);
char *read_input(const char *prompt);

#endif /* MAIN_H */
