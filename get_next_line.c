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

// char 	*readit(fd)
// {
// 	if (!storage[fd][0])
// 	{
// 		if (!read(fd, storage[fd], BUFF_SIZE))
// 		{
// 			if (*line)
// 				return (1); //checks to see if line has content
// 			else
// 				return (0);
// 		}
// 	}
// }

static void	copy_before_match(char **line, char **storage, const int fd)
{
	char		*free_tmp;

	if (*line)
	{
		free_tmp = *line;
		*line = ft_strjoin(*line, storage[fd]);
		free(free_tmp);
	}
	else
	{
		*line = ft_strnew(ft_strlen(storage[fd]));
		ft_strcpy(*line, storage[fd]);
	}
	ft_bzero(storage[fd], ft_strlen(storage[fd]));
}

// static void	copy_after_match(char **line, char *match_word)
// {
// 	char		*free_tmp;
//
// 	if (*line)
// 	{
// 		free_tmp = *line;
// 		*line = ft_strjoin(*line, match_word);
// 		free(free_tmp);
// 	}
// 	else
// 		*line = match_word;
// }

static void	copy_after_match(char **line, char **storage, const int fd)
{
	char		*free_tmp;
	char		*rest;

	rest = ft_strsub((const char *)storage[fd], 0, match - storage[fd]);
	if (*line)
	{
		free_tmp = *line;
		*line = ft_strjoin(*line, rest);
		free(free_tmp);
	}
	else
		*line = rest;
	ft_memdel((void *)&rest);
}

int	get_next_line(const int fd, char **line)
{
	char		*match;
	char		*rest;
	char		*free_tmp;
	static char *storage[9999];

	if (fd < 0 || line == NULL || fd > 9999 || read(fd, storage[fd], 0) < 0)
		return (-1);
	if (storage[fd] == NULL)
		storage[fd] = ft_strnew(BUFF_SIZE);
	*line = NULL;
	while (!ft_strchr(storage[fd], '\n'))
	{
		if (!storage[fd][0])
		{
			if (!read(fd, storage[fd], BUFF_SIZE))
			{
			 	if (*line)
				 	return (1);
				else
					return (0);
			}
		}
		if (!(match = ft_strchr((const char *)storage[fd], '\n')))
			copy_before_match(line, storage, fd);
	}
		match = ft_strchr((const char *)storage[fd], '\n');
		rest = ft_strsub((const char *)storage[fd], 0, match - storage[fd]);
		copy_after_match(&line, &storage, fd);
		if (*line)
		{
			free_tmp = *line;
			*line = ft_strjoin(*line, rest);
			free(free_tmp);
		}
		else
			*line = rest;
		if (match - storage[fd] == 0)
			ft_memmove(storage[fd], match + 1, ft_strlen(match));
		else
			ft_memmove(storage[fd], match + 1, ft_strlen(match - 1));
		//ft_memdel((void *)&rest);
		return (1);
}

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;
// 	int		ret;
// 	int		lines;
//
// 	fd = open(argv[1], O_RDONLY);
// 	lines = 0;
// 	if (fd == -1)
// 		write(2, "error opening file", ft_strlen("error opening file"));
// 	while ((ret = get_next_line(fd, NULL)))
// 	{
// 		ft_putstr(line);
// 		ft_putchar('\n');
// 		lines++;
// 	}
// 	printf("number of lines: %d\n", lines);
// 	return (0);
// }
