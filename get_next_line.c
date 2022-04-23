/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:53:44 by abasarud          #+#    #+#             */
/*   Updated: 2022/04/23 13:27:24 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *s1, char *buf)
{
	char	*buff;

	buff = ft_strjoin(s1, buf);
	free(s1);
	return (buff);
}

char	*ft_read_to_left_str(int fd, char *s1)
{
	char	*buff;
	int		rd_bytes;

	if (!s1)
		s1 = ft_calloc(1, 1);
	buff = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	rd_bytes = 1;
	while (rd_bytes > 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		s1 = ft_free(s1, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (s1);
}

char	*ft_get_line(char *s1)
{
	int		i;
	char	*str;

	i = 0;
	if (!s1[i])
		return (0);
	while (s1[i] && s1[i] != '\n')
		i++;
	str = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		str[i] = s1[i];
		i++;
	}
	if (s1[i] && s1[i] == '\n')
	{
		str[i] = '\n';
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
	if (!s1[i])
	{
		free(s1);
		return (0);
	}
	str = ft_calloc((ft_strlen(s1) + 1), sizeof(char));
	i++;
	j = 0;
	while (s1[i])
	{
		str[j++] = s1[i++];
	}
	free (s1);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*s1;

	if (fd < 0 || BUFFER_SIZE == 0 || read(fd, 0, 0) < 0)
		return (0);
	s1 = ft_read_to_left_str(fd, s1);
	if (!s1)
		return (NULL);
	str = ft_get_line(s1);
	s1 = ft_new_left_str(s1);
	return (str);
}
