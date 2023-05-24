#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * IsInteractive - Returns true if shell is in interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int IsInteractive(info_t *info)
{
  // Check if standard input is a terminal and the read file descriptor is less than 3
  int fd = isatty(STDIN_FILENO);
  return fd && fd <= 2;
}

/**
 * IsDelimiter - Checks if character is a delimiter
 * @c: the char to check
 * @delim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int IsDelimiter(char c, char *delim)
{
  // Iterate over the delimiter string
  while (*delim) {
    // If the current character is in the delimiter string, return true
    if (*delim++ == c) {
      return 1;
    }
  }

  // Otherwise, return false
  return 0;
}

/**
 * IsAlphabetic - Checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int IsAlphabetic(int c)
{
  // Check if the character is between a and z or A and Z
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/**
 * attrib - Converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int attrib(char *s) {
  int sign = 1, i = 0, result = 0;

  while (s[i] != '\0') {
    if (s[i] == '-') {
      sign = -1;
    } else if (isdigit(s[i])) {
      result = result * 10 + s[i] - '0';
    } else {
      break;
    }
    i++;
  }

  return sign * result;
}

int main(int argc, char *argv[]) {
  // Check if the user has provided any arguments
  if (argc == 1) {
    printf("Usage: attrib <string>\n");
    return 1;
  }

  // Convert the string to an integer
  int value = attrib(argv[1]);

  // Print the value
  printf("The value is %d\n", value);

  return 0;
}