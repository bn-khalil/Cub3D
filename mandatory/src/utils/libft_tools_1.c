/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:24:09 by kben-tou          #+#    #+#             */
/*   Updated: 2025/07/05 20:15:20 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	should_skip(const char *s, char c, int *count, int *i)
{
	int		is_in;

	is_in = 0;
	while (s[(*i)])
	{
		if (s[(*i)] != c && is_in == 0)
		{
			(*count)++;
			is_in = 1;
		}
		else if (s[(*i)] == c)
			is_in = 0;
		(*i)++;
	}
}

static int	words_count(const char *s, char c, int skip_separator)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (skip_separator)
		should_skip(s, c, &count, &i);
	else
	{
		if (s[0] == '\0')
			return (0);
		while (s[i])
		{
			if (s[i] == c)
				count++;
			i++;
		}
		return (count + 1);
	}
	return (count);
}

static char	*fill(char *p, const char *s, int i, int len_chrs)
{
	int		k;

	k = 0;
	while (k < len_chrs)
	{
		p[k] = s[i + k];
		k++;
	}
	p[k] = '\0';
	return (p);
}

static char	*store_next_word(const char *s, int *i, char c, \
int skip_separator)
{
	char	*p;
	int		char_count;

	char_count = 0;
	if (skip_separator)
		while (s[*i] && s[*i] == c)
			(*i)++;
	while (s[*i + char_count] && s[*i + char_count] != c)
		char_count++;
	p = (char *)malloc(char_count + 1);
	if (!p)
		return (NULL);
	fill(p, s, *i, char_count);
	*i += char_count;
	if (!skip_separator && s[*i] == c)
		(*i)++;
	return (p);
}

char	**ft_split(char *s, char c, int skip_separator)
{
	char	**p;
	int		i;
	int		j;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = words_count(s, c, skip_separator);
	p = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < word_count)
	{
		p[j] = store_next_word(s, &i, c, skip_separator);
		if (!p[j])
		{
			ft_free_2d(p);
			return (NULL);
		}
	}
	p[j] = NULL;
	free(s);
	return (p);
}
