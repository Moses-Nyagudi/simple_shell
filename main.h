#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;
#define BUFFER_SIZE 1024

void execute_external_command(char **arguments);
void execute_builtin_command(char *command);
void execute_command(char **arguments);
char *get_location(char *command);
char **tokenize_input(char *input);
char *read_input(const char *prompt);
char *custom_getline(void);
void init_custom_getline(void);
char *read_custom_getline(void);
#endif /* MAIN_H */
