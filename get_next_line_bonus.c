/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:27:31 by ramzi             #+#    #+#             */
/*   Updated: 2021/05/04 11:29:58 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	count_newline(char *saved)
{
	int	i;

	i = 0;
	while (saved[i])
	{
		if (saved[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	find_line(char **saved, char **line, int a)
{
	char	*tmp;
	int		len;

	(*saved)[a] = '\0';
	*line = ft_strdup(*saved);
	len = ft_strlen(*saved + a + 1);
	if (len == 0)
	{
		free(*saved);
		*saved = 0;
		return (1);
	}
	tmp = ft_strdup(*saved + a + 1);
	free(*saved);
	*saved = tmp;
	return (1);
}

int	check_line(char **saved, char **line, int read_bytes)
{
	int	i;

	if (read_bytes < 0)
		return (-1);
	i = count_newline(*saved);
	if ((*saved) && i >= 0)
		return (find_line(saved, line, i));
	else if (*saved)
	{
		*line = *saved;
		*saved = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*saved[FD_MAX];
	char		buff[BUFFER_SIZE + 1];
	int			read_bytes;				
	int			i;						

	if ((fd < 0) || fd > FD_MAX || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	read_bytes = BUFFER_SIZE;
	while (read_bytes)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes < 0)
			return (-1);
		buff[read_bytes] = '\0';
		saved[fd] = ft_strjoin(saved[fd], buff);
		i = count_newline(saved[fd]);
		if (i >= 0)
			return (find_line(&saved[fd], line, i));
	}
	return (check_line(&saved[fd], line, read_bytes));
}
