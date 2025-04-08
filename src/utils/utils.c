/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:26:56 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/08 21:26:37 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(const char *src, int n)
{
	int		i;
	char	*smt;
	int		len;

	len = ft_strlen(src);
	i = 0;
	if (n > len)
		n = len;
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

char	*ft_strnstr( char *big,char *little, size_t len)
{
	size_t	little_len;

	little_len = ft_strlen(little);
	if (*little == '\0')
		return ((char *)big);
	while (*big && len-- >= little_len)
	{
		if (ft_strncmp(big, little, little_len) == 0)
			return ((char *)big);
		big++;
	}
	return (NULL);
}

void	freearray(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
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

// void *ft_realloc(void *ptr, size_t new_size)
// {
//     void *new_ptr;

//     if (!ptr)
//         return malloc(new_size);
//     if (new_size == 0)
//     {
//         free(ptr);
//         return NULL;
//     }
//     new_ptr = malloc(new_size);
//     if (!new_ptr)
//         return NULL;
//     memcpy(new_ptr, ptr, new_size);
//     free(ptr);
//     return new_ptr;
// }

void	**safe_expand_array(void **ptr, size_t old_count, size_t new_count)
{
	void	**new_ptr;

	new_ptr = malloc(sizeof(void *) * new_count);
	if (!new_ptr)
		return (NULL);

	for (size_t i = 0; i < old_count; i++)
		new_ptr[i] = ptr[i];
	for (size_t i = old_count; i < new_count; i++)
		new_ptr[i] = NULL;

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