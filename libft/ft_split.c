/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:50:51 by mabi-nak          #+#    #+#             */
/*   Updated: 2024/09/21 05:54:43 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	int	count;
	int	i;
	int	word_flag;

	count = 0;
	i = 0;
	word_flag = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		while (str[i] != c && str[i])
		{
			word_flag = 1;
			i++;
		}
		if (word_flag)
			count++;
		word_flag = 0;
	}
	return (count);
}

static int	ft_word_len(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*ft_get_word(const char *str, int len)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) *(len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static char	**populate_split_array(char const *s,
	char c, char **strs, int words)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	while (s[i] && j < words)
	{
		while (s[i] == c)
			i++;
		len = ft_word_len(s + i, c);
		if (len)
		{
			strs[j] = ft_get_word(s + i, len);
			j++;
		}
		i += len;
	}
	strs[j] = NULL;
	return (strs);
}

char	**ft_split(char const *str, char c)
{
	int		words;
	char	**array;

	if (!str)
		return (NULL);
	words = count_words(str, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	if (!populate_split_array(str, c, array, words))
	{
		free (array);
		return (NULL);
	}
	return (array);
}
