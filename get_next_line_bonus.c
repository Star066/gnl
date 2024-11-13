/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:14:35 by nrolland          #+#    #+#             */
/*   Updated: 2024/11/12 15:41:57 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;
	char	check;

	i = 0;
	check = c;
	str = (char *)s;
	while (str[i])
	{
		if (str[i] == check)
			return (str + i);
		i++;
	}
	if (str[i] != check)
		return (0);
	return (str + i);
}

char	*ft_after(char *buffer)
{
	char	*after;
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[i + y])
		y++;
	after = ft_calloc(y + 1, sizeof(char));
	if (!after)
		return (NULL);
	y = 0;
	while (buffer[i])
	{
		after[y] = buffer[i];
		i++;
		y++;
	}
	free(buffer);
	return (after);
}

char	*ft_before(char *buffer)
{
	char	*before;
	int		i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	before = ft_calloc(i + 1, sizeof(char));
	if (!before)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		before[i] = buffer[i];
		i++;
	}
	before[i] = buffer[i];
	return (before);
}

char	*ft_read(int fd, char *buffer)
{
	int		r;
	char	*buf;

	r = 0;
	while (!ft_strchr(buffer, '\n'))
	{
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buf)
			return (NULL);
		r = read(fd, buf, BUFFER_SIZE);
		if (r <= 0)
		{
			free(buf);
			if (buffer[0] == '\0' || r == -1)
			{
				free(buffer);
				return (NULL);
			}
			break ;
		}
		buffer = ft_strjoin(buffer, buf);
		free(buf);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer[fd])
		return (NULL);
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	buf = ft_before(buffer[fd]);
	buffer[fd] = ft_after(buffer[fd]);
	return (buf);
}
