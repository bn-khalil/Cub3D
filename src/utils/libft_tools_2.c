/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:48:06 by kben-tou          #+#    #+#             */
/*   Updated: 2025/07/01 16:30:43 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*p;

	p = (char *)malloc(ft_strlen(s1) + 1);
	if (!p)
		return (NULL);
	i = -1;
	while (s1[++i])
		p[i] = s1[i];
	p[i] = '\0';
	return (p);
}

long	ft_atoi(const char *str)
{
	int		i;
	long	store;
	int		si;

	i = 0;
	si = 1;
	store = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			si *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		store = store * 10 + (str[i++] - '0');
	return (store * si);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	s;
	size_t	e;
	size_t	i;
	char	*res;

	s = 0;
	e = 0;
	i = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (s1[s] && ft_strchr(set, s1[s]))
		s++;
	e = ft_strlen(s1);
	while (e > s && ft_strchr(set, s1[e - 1]))
		e--;
	res = (char *)malloc((e - s) + 1);
	if (!res)
		return (NULL);
	while (e > s)
		res[i++] = s1[s++];
	res[i] = '\0';
	free(s1);
	return (res);
}
