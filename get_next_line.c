/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:03:12 by vlee              #+#    #+#             */
/*   Updated: 2018/05/22 18:47:45 by vlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <stdio.h>

static void move_all_from_buffer(char **line, char *buf)
{
	char		*free_tmp;

	free_tmp = *line;
	*line = ft_strjoin(*line, buf);
	free(free_tmp);
	ft_bzero(buf, ft_strlen(buf));
}

static int move_up_to_newline_from_buffer(char **line, char *buf)
{
	char		*free_tmp;
	char *i_newline;
	char *what_to_copy;

	i_newline = ft_strchr((const char *)buf, '\n');
	if (!i_newline)
		return (-1);
	what_to_copy = ft_strsub((const char *)buf, 0, i_newline - buf);
	free_tmp = *line;
	*line = ft_strjoin(*line, what_to_copy);
	free(free_tmp);
	if (i_newline - buf == 0)
		ft_memmove(buf, i_newline + 1, ft_strlen(i_newline));
	else
		ft_memmove(buf, i_newline + 1, ft_strlen(i_newline - 1));
	ft_memdel((void *)&what_to_copy);
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	char				*i_newline;
	static char *storage[9999];
	int					bytes_read;

	if (fd < 0 || line == NULL || fd > 9999 || read(fd, storage[fd], 0) < 0)
		return (-1);
	if (storage[fd] == NULL)
		storage[fd] = ft_strnew(BUFF_SIZE);
	*line = NULL;
	while (!ft_strchr(storage[fd], '\n'))
	{
		if (!storage[fd][0])
		{
			if (!(bytes_read = read(fd, storage[fd], BUFF_SIZE)))
					return (*line) ? 1 : 0;
			else if (bytes_read > 0 && bytes_read < BUFF_SIZE)
					ft_bzero(storage[fd] + bytes_read, BUFF_SIZE - bytes_read);
		}
		if (!(i_newline = ft_strchr((const char *)storage[fd], '\n')))
			move_all_from_buffer(line, storage[fd]);
	}
	if (move_up_to_newline_from_buffer(line, storage[fd]) == -1)
		return (-1);
	return (1);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		ret;
	int		lines;

	fd = open(argv[1], O_RDONLY);
	printf("fd: %d\n", fd);
	lines = 0;
	if (fd == -1)
		write(2, "error opening file", ft_strlen("error opening file"));
	while ((ret = get_next_line(fd, &line)))
	{
		ft_putstr(line);
		ft_putchar('\n');
		lines++;
	}
	printf("number of lines: %d\n", lines);
	return (0);
}
