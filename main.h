#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

void execute_command(char **arguments);
char *get_location(char *command);


#endif /* MAIN_H */
