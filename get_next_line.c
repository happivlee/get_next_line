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

int	get_next_line(const int fd, char **line)
{
	char		*match;
	char		*match_word;
	//char		tmp[BUFF_SIZE + 1];
	char		*tmp;
	char		*free_tmp;
	//static char storage[BUFF_SIZE + 1];
	//char buf[BUF_SIZE + 1];

	static char *storage = NULL;
	if (storage == NULL)
		storage = ft_strnew(BUFF_SIZE);
	if (fd < 0 || line == NULL || read(fd, storage, 0) < 0)
		return (-1);
	*line = NULL;
	tmp = NULL;
	while (!ft_strchr(storage, '\n'))
	{
		if (!storage[0])
		{
			if (!read(fd, storage, BUFF_SIZE))
			{
			 	if (*line)
				 	return (1); //checks to see if line has content
				else
					return (0);
			}
		}
		//it there's no \n in the current storage
		if (!(match = ft_strchr((const char *)storage, '\n')))
		{
			//line already contains chars
			if (*line)
			{
				free_tmp = *line;
				*line = ft_strjoin(*line, storage);
				free(free_tmp);
			}
			//if line is null
			else
			{
				*line = ft_strnew(ft_strlen(storage));
				ft_strcpy(*line, storage);
			}
			ft_bzero(storage, ft_strlen(storage));
		}
	}
		//if a \n is found in the current storage..
		match = ft_strchr((const char *)storage, '\n');
		match_word = ft_strsub((const char *)storage, 0, match - storage);
		if (*line)
		{
			free_tmp = *line;
			*line = ft_strjoin(*line, match_word);
			free(free_tmp);

		}
		else
			*line = match_word;
		if (match - storage == 0)
			ft_memmove(storage, match + 1, ft_strlen(match));
		else
			ft_memmove(storage, match + 1, ft_strlen(match - 1));
		ft_memdel((void *)&tmp);
		ft_memdel((void *)&match_word);
		return (1);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		ret;
	int		lines;

	fd = open(argv[1], O_RDONLY);
	lines = 0;
	if (fd == -1)
		write(2, "error opening file", ft_strlen("error opening file"));
	while ((ret = get_next_line(fd, &line)))
	{
		ft_putstr(line);
		ft_putchar('\n');
		lines++;
		//free(line);
		/*
		printf("ret: %d\n", ret);
		if (ret == -1)
		{
			printf("error - returning -1\n");
			return (-1);
		}
		printf("the line that will be printed: %s\n", line);*/
	}
	printf("total lines printed: %d\n", lines);
	while(1);
	// leaks();
	return (0);
}
