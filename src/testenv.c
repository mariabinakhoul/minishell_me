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

}