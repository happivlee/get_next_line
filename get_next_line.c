/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:03:12 by vlee              #+#    #+#             */
/*   Updated: 2018/05/08 18:26:38 by vlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <stdio.h>

int	get_next_line(const int fd, char **line)
{
	char		*match;
	char		*match_word;
	char		*tmp;
	static char storage[BUFF_SIZE + 1];
	//char buf[BUF_SIZE + 1];
	storage[0] = '\0';
	*line = NULL;
	tmp = NULL;
	while (!ft_strchr(storage, '\n'))
	{
		if (!*storage)
		{
			if (!read(fd, storage, BUFF_SIZE))
				return (0);
		}
		if (!(match = ft_strchr((const char *)storage, '\n')))
		{
			tmp = ft_strcpy(tmp, *line);
			*line = ft_strnew(ft_strlen(*line) + ft_strlen(storage));
			*line = ft_strcat(tmp, storage);
			ft_bzero(storage, ft_strlen(storage));
		}
		else
		{
			if (*line)
			{
				tmp = ft_strcpy(tmp, *line);
				*line = ft_strnew(ft_strlen(*line) + (match - storage));
			}
			else
				*line = ft_strnew(match - storage);
			match_word = ft_strsub((const char *)storage, 0, match - storage);
			*line = ft_strjoin(tmp, match_word);
			ft_memmove(storage, match + 1, ft_strlen(match - 1));
			return (1);
		}
	}
	return (-1);
}

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;
//
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd == -1)
// 		write(2, "error opening file", ft_strlen("error opening file"));
// 	while (get_next_line(fd, &line) > 0)
// 	{
// 		printf("%s\n", line);
// 	}
// 	return (0);
// }
