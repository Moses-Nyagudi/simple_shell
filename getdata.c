#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a give exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
  int exitcheck;

  if (info->argv[1]) /* if there is an exit argument */
  {
    exitcheck = atoi(info->argv[1]);
    if (exitcheck == -1)
    {
      info->status = 2;
      printf("Illegal number: %s\n", info->argv[1]);
      return (1);
    }
    info->err_num = exitcheck;
    return (-2);
  }
  info->err_num = -1;
  return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function protype.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
  char *s, *dir, buffer[1024];
  int chdir_ret;

  s = getcwd(buffer, 1024);
  if (!s)
    printf("TODO: >>getcwd failure emsg here<<\n");
  if (!info->argv[1])
  {
    dir = getenv("HOME");
    if (!dir)
      chdir_ret = chdir("/");
    else
      chdir_ret = chdir(dir);
  }
  else if (strcmp(info->argv[1], "-") == 0)
  {
    if (!getenv("OLDPWD"))
    {
      printf("%s\n", s);
      return (1);
    }
    printf("%s\n", getenv("OLDPWD"));
    chdir_ret = chdir(getenv("OLDPWD"));
  }
  else
    chdir_ret = chdir(info->argv[1]);
  if (chdir_ret == -1)
  {
    printf("can't cd to %s\n", info->argv[1]);
  }
  else
  {
    setenv("OLDPWD", getenv("PWD"), 1);
    setenv("PWD", getcwd(buffer, 1024), 1);
  }
  return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
  printf("help call works. Function not yet implemented \n");
  return (0);
}

/**
 * _myhistory - displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
  list_t *node = info->history;
  int i = 0;

  while (node)
  {
    printf("%d: %s\n", i++, node->str);
    node = node->next;
  }
  return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)