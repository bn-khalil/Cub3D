#include "../../inc/cub3d.h"

static size_t	words_count(const char *s, char c, int skip_separator)
{
	size_t	i = 0;
	size_t	count = 0;

	if (skip_separator)
	{
		size_t	is_in = 0;
		while (s[i])
		{
			if (s[i] != c && is_in == 0)
			{
				count++;
				is_in = 1;
			}
			else if (s[i] == c)
				is_in = 0;
			i++;
		}
	}
	else
	{
		if (s[0] == '\0')
			return 0;
		while (s[i])
		{
			if (s[i] == c)
				count++;
			i++;
		}
		return count + 1;
	}
	return count;
}

static void	mem_free(char **p)
{
	size_t	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}

static char	*fill(char *p, const char *s, size_t i, size_t len_chrs)
{
	size_t	k;

	k = 0;
	while (k < len_chrs)
	{
		p[k] = s[i + k];
		k++;
	}
	p[k] = '\0';
	return (p);
}

static char	*store_next_word(const char *s, size_t *i, char c, int skip_separator)
{
	char	*p;
	size_t	char_count;

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
	size_t	i;
	size_t	j;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = words_count(s, c, skip_separator);
	p = malloc((word_count + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	i = 0;
	j = 0;
	while (j < word_count)
	{
		p[j] = store_next_word(s, &i, c, skip_separator);
		if (!(p[j]))
		{
			mem_free(p);
			return (NULL);
		}
		j++;
	}
	p[j] = NULL;
	free(s);
	return (p);
}