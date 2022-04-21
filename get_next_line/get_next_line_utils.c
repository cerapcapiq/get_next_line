/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:39:17 by abasarud          #+#    #+#             */
/*   Updated: 2022/04/21 12:41:19 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int ch)
{
	if ((unsigned char)ch == 0)
		return ((char *)(str + ft_strlen(str)));
	while (*str)
	{
		if (*str == (unsigned char)ch)
			return ((char *)str);
		str++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[j++] = s2[i];
		i++;
	}
	str[j] = 0;
	return (str);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		i++;
	}
	return (i);
}

char	*ft_get_line(char *s1)
{
	int		i;
	char	*str;

	i = 0;
	if (!s1[i])
		return (NULL);
	while (s1[i] && s1[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		str[i] = s1[i];
		i++;
	}
	if (s1[i] == '\n')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_new_left_str(char *s1)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (s1[i] && s1[i] != '\n')
		i++;
	if (s1[i])
	{
		free (s1);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen (s1) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while  (s1[i])
		str[j++] = s1[i++];
	str[j] = '\0';
	free (s1);
	return (str);
}
