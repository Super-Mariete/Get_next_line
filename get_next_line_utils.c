/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-ped <made-ped@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:03:49 by made-ped          #+#    #+#             */
/*   Updated: 2023/12/27 18:40:37 by made-ped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*p;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	p = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!p)
		return (NULL);
	while (*s1)
		*p++ = *s1++;
	while (*s2)
		*p++ = *s2++;
	*p = '\0';
	return (p - (len_s1 + len_s2));
}

char	*ft_strchr(const char *str, int c)
{
	char	*p_str;
	char	cc;
	int		i;

	p_str = (char *)str;
	cc = c;
	i = 0;
	while (p_str[i] != cc)
	{
		if (p_str[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)p_str + i);
}

size_t	ft_strlen(const char *string)
{
	size_t	i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*p;
	int		i;

	i = 0;
	p = malloc(ft_strlen(str) + 1);
	if (!p)
		return (NULL);
	while (str[i])
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
