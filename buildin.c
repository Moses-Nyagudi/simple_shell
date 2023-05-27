#include "main.h"

/**
 * exit_shell - exits the shell
 * @info: Structure containing potential arguments
 *
 * Return: exits with a given exit status
 *         (0) if info->argv[0] != "exit"
 */
int exit_shell(info_t *info)
{
    int exit_status;

    if (info->argv[1])  /* If there is an exit argument */
    {
        exit_status = validate_exit_status(info->argv[1]);
        if (exit_status == -1)
        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return 1;
        }
        info->err_num = exit_status;
        return -2;
    }
    info->err_num = -1;
    return -2;
}

/**
 * change_directory - changes the current directory of the process
 * @info: Structure containing potential arguments
 *
 * Return: Always 0
 */
int change_directory(info_t *info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
        _puts("TODO: >>getcwd failure emsg here<<\n");
    if (!info->argv[1])
    {
        dir = get_environment_variable(info, "HOME=");
        if (!dir)
            chdir_ret = /* TODO: what should this be? */
                chdir((dir = get_environment_variable(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!get_environment_variable(info, "OLDPWD="))
        {
            _puts(s);
            _putchar('\n');
            return 1;
        }
        _puts(get_environment_variable(info, "OLDPWD="));
        _putchar('\n');
        chdir_ret = /* TODO: what should this be? */
            chdir((dir = get_environment_variable(info, "OLDPWD=")) ? dir : "/");
    }
    else
        chdir_ret = chdir(info->argv[1]);
    if (chdir_ret == -1)
    {
        print_error(info, "can't cd to ");
        _eputs(info->argv[1]);
        _eputchar('\n');
    }
    else
    {
        set_environment_variable(info, "OLDPWD", get_environment_variable(info, "PWD="));
        set_environment_variable(info, "PWD", getcwd(buffer, 1024));
    }
    return 0;
}

/**
 * help_command - provides help information
 * @info: Structure containing potential arguments
 *
 * Return: Always 0
 */
int help_command(info_t *info)
{
    char **arg_array;

    arg_array = info->argv;
    _puts("help call works. Function not yet implemented \n");
    if (0)
        _puts(*arg_array); /* temp att_unused workaround */
    return 0;
}


/**
 * display_history - displays the history list, one command per line,
 *                   preceded with line numbers starting at 0.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int display_history(info_t *info)
{
    print_list(info->history);
    return 0;
}

/**
 * unset_alias - removes an attrib from the attrib list.
 * @info: Structure containing potential arguments.
 * @str: The string attrib.
 *
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
    char *p, c;
    int ret;

    p = _strchr(str, '=');
    if (!p)
        return 1;
    c = *p;
    *p = '\0';
    ret = delete_node_at_index(&(info->attrib), get_node_index(info->attrib, node_starts_with(info->attrib, str, -1)));
    *p = c;
    return ret;
}

/**
 * set_alias - sets an attrib to a string.
 * @info: Structure containing potential arguments.
 * @str: The string attrib.
 *
 * Return: Always 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
    char *p;

    p = _strchr(str, '=');
    if (!p)
        return 1;
    if (!*++p)
        return unset_alias(info, str);

    unset_alias(info, str);
    return add_node_end(&(info->attrib), str, 0) == NULL;
}

/**
 * print_alias - prints an attrib string.
 * @node: The attrib node.
 *
 * Return: Always 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        p = _strchr(node->str, '=');
        for (a = node->str; a <= p; a++)
            _putchar(*a);
        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");
        return 0;
    }
    return 1;
}

/**
 * alias_command - mimics the attrib buildin (man attrib).
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int alias_command(info_t *info)
{
    int i = 0;
    char *p = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->attrib;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return 0;
    }

    for (i = 1; info->argv[i]; i++)
    {
        p = _strchr(info->argv[i], '=');
        if (p)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starts_with(info->attrib, info->argv[i], '='));
    }

    return 0;
}
