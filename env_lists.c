#include "main.h"

/**
 * _myenv - prints the current environment.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myenv(info_t *info)
{
    print_list_str(info->env);
    return 0;
}

/**
 * _getenv - gets the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Environment variable name.
 *
 * Return: The value of the environment variable.
 */
char *_getenv(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *p;

    while (node)
    {
        p = starts_with(node->str, name);
        if (p && *p)
            return p;
        node = node->next;
    }
    return NULL;
}

/**
 * _mysetenv - Initializes a new environment variable or modifies an existing one.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _mysetenv(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return 1;
    }
    if (_setenv(info, info->argv[1], info->argv[2]))
        return 0;
    return 1;
}

/**
 * _myunsetenv - Removes an environment variable.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myunsetenv(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return 1;
    }
    for (i = 1; i < info->argc; i++)
        _unsetenv(info, info->argv[i]);

    return 0;
}

/**
 * populate_env_list - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int populate_env_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    info->env = node;
    return 0;
}

/**
 * get_environ - Returns the string array copy of our environ.
 * @info: Structure containing potential arguments.
 *
 * Return: String array copy of the environ.
 */
char **get_environ(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return info->environ;
}

/**
 * _unsetenv - Removes an environment variable.
 * @info: Structure containing potential arguments.
 * @var: The environment variable to remove.
 *
 * Return: 1 if the variable is deleted, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
    list_t *node = info->env;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return 0;

    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), i);
            i = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        i++;
    }
    return info->env_changed;
}

/**
 * _setenv - Initializes a new environment variable or modifies an existing one.
 * @info: Structure containing potential arguments.
 * @var: The environment variable to initialize or modify.
 * @value: The value of the environment variable.
 *
 * Return: Always 0.
 */
int _setenv(info_t *info, char *var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var || !value)
        return 0;

    buf = malloc(_strlen(var) + _strlen(value) + 2);
    if (!buf)
        return 1;
    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);
    node = info->env;
    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return 0;
        }
        node = node->next;
    }
    add_node_end(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;
    return 0;
}
