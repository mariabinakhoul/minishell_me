/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:26:34 by nhaber            #+#    #+#             */
/*   Updated: 2025/05/30 20:00:02 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*convert_to_list(char **envp)
{
	t_env	*head;
	t_env	*curr;
	t_env	*new_node;
	int		i;

	i = 0;
	head = NULL;
	curr = NULL;
	while (envp[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->data = ft_strdup(envp[i]);
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
	return (head);
}

void	print_env(t_env *head)
{
	while (head != NULL)
	{
		printf("%s\n", head->data);
		head = head->next;
	}
}

char	**convert_to_2d(t_env *head)
{
	int		count;
	t_env	*tmp;
	int		i;
	char	**converted_env;

	i = 0;
	count = 0;
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
		converted_env[i] = ft_strdup(head->data);
		i++;
		head = head->next;
	}
	converted_env[i] = NULL;
	return (converted_env);
}

void	print2d(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

int args_found(t_env *head, char **args)
{
	t_env *temp;
	char **value;
	char **new;

	temp = head;
	new = ft_split(args[1], '=');
	while (temp)
	{
		value = ft_split(temp->data, '=');
		// printf("%sffff\n", new[0]);
		if (ft_strncmp(value[0], new[0], ft_strlen(value[0])) == 0)
		{
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void update_value(t_env *head, char **args)
{
	t_env *temp;
	char **value;
	char	*new_val;
	char **new;

	temp = head;
	value = ft_split(temp->data, '=');
	new = ft_split(args[1], '=');
	while (temp && ft_strncmp(value[0], new[0], ft_strlen(value[0])) != 0)
	{
		temp = temp->next;
		if (temp)
			value = ft_split(temp->data, '=');
	}
	if (!new[1])
	{
		free_2d(new);
		return ;
	}
	value[1] = ft_strdup(new[1]);
	new_val = ft_strjoin(value[0], "=");
	new_val = ft_strjoin(new_val, value[1]);
	temp->data = ft_strdup(new_val);
}

char *ft_strjoin_free(char *s1, char *s2, int free_s1, int free_s2)
{
	char *joined;
	
	if (!s1 || !s2)
		return (NULL);
	joined = ft_strjoin(s1, s2);  // your existing ft_strjoin
	if (free_s1)
		free(s1);
	if (free_s2)
		free(s2);
	return (joined);
}

// void update_value(t_env *head, char **args)
// {
// 	t_env *temp;
// 	char **value;
// 	char	*new_val;
// 	char **new;

// 	temp = head;
// 	new = ft_split(args[1], '=');
// 	if (!new[1]) // no '=' in the argument
// 	{
// 		// Free whatever you need here
// 		free_2d(new);
// 		return;
// 	}

// 	while (temp)
// 	{
// 		value = ft_split(temp->data, '=');
// 		if (ft_strncmp(value[0], new[0], ft_strlen(value[0])) == 0)
// 		{
// 			char *old = temp->data;
// 			new_val = ft_strjoin(value[0], "=");
// new_val = ft_strjoin_free(ft_strjoin(value[0], "="), value[1], 1, 0);
// 			temp->data = ft_strdup(new_val);
// 			free(old);
// 			free(new_val);
// 			free_2d(value);
// 			break;
// 		}
// 		free_2d(value);
// 		temp = temp->next;
// 	}
// 	free_2d(new);
// }


t_env	*create_node(t_env *head, char **args)
{
	t_env	*new_node;
	t_env	*tmp;

	if (args_found(head, args) == 0)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (head);
		new_node->data = ft_strdup(args[1]);
		new_node->next = NULL;
		if (!head)
			return (new_node);
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	else
	{
		update_value(head, args);
	}
	return (head);
}

char	**set_env(char **envp)
{
	t_env	*env_list;
	char	**new_env;

	env_list = convert_to_list(envp);
	new_env = convert_to_2d(env_list);
	free_list(env_list);
	return (new_env);
}

void	ft_env(char **envp)
{
	char	**environment;
	int		i;

	i = 0;
	environment = set_env(envp);
	// while (environment[i])
	// {
	// 	printf("%s\n", environment[i]);
	// 	i++;
	// }
	// free_2d(environment);
	// environment = set_env(envp);
    for (i = 0; environment[i]; i++)
    {
        /* only print entries that actually contain an '=' */
        if (ft_strchr(environment[i], '='))
            printf("%s\n", environment[i]);
    }
    free_2d(environment);
}
