#include "../includes/minishell.h"

t_env *convert_to_list(char **envp)
{
    t_env *head = NULL;
    t_env *curr = NULL;
    t_env *new_node;
    int i = 0;

    while (envp[i])
    {
        new_node = malloc(sizeof(t_env));
        if (!new_node)
            return NULL;
        new_node->data = strdup(envp[i]);
        new_node->next = NULL;
        if (!head)
        {
            head = new_node;
            curr = head;
        }
        else
        {
            curr->next = new_node;
            curr = new_node;
        }
        i++;
    }
    return head;
}


void print_env(t_env *head)
{
    while (head != NULL)
    {
        printf("%s\n", head->data);
        head = head->next;
    }
}

char **convert_to_2d(t_env *head)
{
    int count;
    t_env *tmp;
    int i;
    char **converted_env;

    i = 0;
    count =  0;
    tmp = head;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    converted_env = malloc((count + 1) * sizeof(char *));
    if (!converted_env)
        return (NULL);
    while (head)
    {
        converted_env[i] = strdup(head->data);
        i++;
        head = head->next;
    }
    converted_env[i] = NULL;
    return (converted_env);
}



void print2d(char **array)
{
    int i = 0;
    while (array[i])
    {
        printf("%s\n", array[i]);
        i++;
    }
}