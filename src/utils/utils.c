/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:26:56 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/03/19 20:55:26 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(const char *src, int n)
{
	int		i;
	char	*smt;

	i = 0;
	smt = (char *)malloc(sizeof(char) * (n + 1));
	if (smt == NULL)
		return (NULL);
	while (i < n)
	{
		smt[i] = src[i];
		i++;
	}
	smt[i] = '\0';
	return (smt);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && (s1[i] == s2[i]))
		i++;
	if (s1[i] == s2[i])
		return (0);
	else
		return (s1[i] - s2[i]);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

void *ft_realloc(void *ptr, size_t new_size)
{
    void *new_ptr;

    if (!ptr)
        return malloc(new_size);
    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }
    new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;
    memcpy(new_ptr, ptr, new_size);
    free(ptr);
    return new_ptr;
}

void free_ast(t_ast *node)
{
    if (!node)
        return;
    free_ast(node->left);
    free_ast(node->right);
    if (node->params)
        free(node->params);
    free(node);
}