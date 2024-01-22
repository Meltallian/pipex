/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:07:27 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/22 10:33:46 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdbool.h"

static size_t	word_count(const char *s, const char c)
{
	size_t	i;
	size_t	j;
	size_t	index;
	bool	is_trig;

	i = 0;
	j = 0;
	index = 0;
	is_trig = false;
	while (s[i])
	{
		if (s[i] == 39)
			is_trig = !is_trig;
		if (s[i] != c && index == 0)
		{
			index = 1;
			j++;
		}
		else if (s[i] == c && !is_trig)
			index = 0;
		i++;
	}
	return (j);
}

static char	*ft_buff(const char *str, size_t start, size_t end)
{
	char	*buff;
	int		i;

	i = 0;
	buff = (char *)malloc((end - start + 1) * sizeof(char));
	if (!buff)
		return (0);
	while (start < end)
		buff[i++] = str[start++];
	buff[i] = '\0';
	return (buff);
}

void	helper_split_2(size_t *i, size_t *j, bool *is_trig, int *index)
{
	*i = 0;
	*j = 0;
	*is_trig = false;
	*index = -1;
}

int	helper2_split_2(const char *s, char **split)
{
	if (!s)
		return (0);
	if (!split)
		return (0);
	return (1);
}

char	**ft_split_2(const char *s, const char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;
	bool	is_trig;

	helper_split_2(&i, &j, &is_trig, &index);
	split = ft_calloc((word_count(s, c) + 1), sizeof(char *));
	if (helper2_split_2(s, split) == 0)
		return (0);
	while (i <= ft_strlen(s))
	{
		if (s[i] == 39)
			is_trig = !is_trig;
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0 && !is_trig)
		{
			split[j++] = ft_buff(s, index, i);
			index = -1;
		}
		i++;
	}
	return (split);
}
