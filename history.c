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

int _myhelp(info_t *info)
{
  printf("help call works. Function not yet implemented \n");
  return (0);
}

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

int unset_alias(info_t *info, char *str)
{
  list_t *node = info->alias;
  while (node)
  {
    if (strcmp(node->str, str) == 0)
    {
      free(node->str);
      free(node);
      info->alias = node->next;
      return (0);
    }
    node = node->next;
  }
  return (1);
}

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
  ssize_t r = 0;
  size_t len_p = 0;

  if (!*len) /* if nothing is left in the buffer, fill it */
  {
    free(*buf);
    *buf = NULL;
    signal(SIGINT, sigintHandler);
#if USE_GETLINE
    r = getline(buf, &len_p, stdin);
#else
    r = _getline(info, buf, &len_p);
#endif
    if (r > 0)
    {
      if ((*buf)[r - 1] == '\n')
      {
        (*buf)[r - 1] = '\0');