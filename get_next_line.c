/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrolland <nrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:14:35 by nrolland          #+#    #+#             */
/*   Updated: 2024/11/09 19:36:49 by nrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	return (after);
}

char	*ft_before(char *buffer)
{
	char	*before;
	int 	i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	before = ft_calloc(i + 1, sizeof(char));
	if (!before)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n')
	{
		before[i] = buffer[i];
		i++;
	}
	before[i] = buffer[i];
	return (before);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char	*buf;
	int		r;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_calloc(BUFFER_SIZE + 1 , sizeof(char));
	if (!buffer)
		return (NULL);
	buf = ft_calloc(BUFFER_SIZE + 1 , sizeof(char));
	if (!buf)
		return (NULL);
	r = 0;
	while (!ft_strchr(buffer, '\n'))
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r <= 0)
			return (NULL);
		buffer = ft_strjoin(buffer, buf);
	}
	buf = ft_before(buffer);
	buffer = ft_after(buffer);
	return (buf);
}

#include <stdio.h>
int main(void)
{
	// int fd;
	// fd = open("slalut.txt", O_RDONLY);
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));

    int fd = open("slalut.txt", O_RDONLY);
    char    *str = get_next_line(fd);
    while (str != NULL)
    {
        printf("%s\n", str);
        free(str);
        str = get_next_line(fd);
    }
    close(fd);
}
