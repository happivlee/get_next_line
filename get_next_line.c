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
	//static char storage[BUFF_SIZE + 1];
	//char buf[BUF_SIZE + 1];

	static char *storage = NULL;
	if (storage == NULL)
		storage = ft_strnew(BUFF_SIZE);
	//ft_bzero(tmp, ft_strlen(tmp));
	//checks for errors
	if (fd < 0 || line == NULL || read(fd, storage, 0) < 0)
		return (-1);
	*line = NULL;
	//tmp = NULL;
	while (!ft_strchr(storage, '\n'))
	{
		if (!storage[0])
		{
			if (!read(fd, storage, BUFF_SIZE))
				return (0);
		}
		//it there's no \n in the current storage
		if (!(match = ft_strchr((const char *)storage, '\n')))
		{
			//line already contains chars
			if (*line)
			{
				ft_strcpy(tmp, *line);
				//free(*line);
				*line = ft_strnew(ft_strlen(*line) + ft_strlen(storage));
				*line = ft_strcat(tmp, storage);
			}
			//if line is null
			else
			{
				*line = ft_strnew(ft_strlen(storage));
				ft_strcpy(*line, storage);
			}
			//printf("storage while looking for nl contains: %s\n", storage);
			ft_bzero(storage, ft_strlen(storage));
		}
	}
		//if a \n is found in the current storage..
		match = ft_strchr((const char *)storage, '\n');
		match_word = ft_strsub((const char *)storage, 0, match - storage); //when new line is first thing read in storage, match_word = 0
		//match_word[ft_strlen(match_word)] = '\0'; //is this adding a null???
		if (*line)
		{
			tmp = ft_strdup(*line);
			//ft_strcpy(tmp, *line);
			//free(*line);
			*line = ft_strnew(ft_strlen(*line) + (match - storage));
			*line = ft_strjoin(tmp, match_word);
			//(*line)[ft_strlen(*line)] = '\0';
		}
		else
			//*line = ft_strnew(match - storage);
			*line = match_word;
		// if (match_word == NULL) //trying to say if match_word is "" 		//Q: Why does this not work?
		// 	ft_memmove(storage, match + 1, 1);
		//printf("storage before memmove contains: %s\n", storage);
		// printf("1st char before memmove: %c\n", storage[0]);
		// printf("2nd char before memmove: %c\n", storage[1]);
		// printf("3rd char before memmove: %c\n", storage[2]);
		// printf("4th char before memmove: %c\n", storage[3]);
		if (match - storage == 0) //this works to increment the pointer by 1!!! may not need lines 74-75
			ft_memmove(storage, match + 1, ft_strlen(match));
		else
			ft_memmove(storage, match + 1, ft_strlen(match - 1)); //when nl is first char,
		//printf("storage after memmove contains: %s\n", storage);
		// printf("1st char after memmove: %c\n", storage[0]);
		// printf("2nd char after memmove: %c\n", storage[1]);
		// printf("3rd char after memmove: %c\n", storage[2]);
		// printf("4th char after memmove: %c\n", storage[3]);
		//ft_bzero(tmp, ft_strlen(tmp));
		ft_memdel((void *)&tmp);
		//free(tmp);
		return (1);
}
//do I need to free tmp?
int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		ret;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		write(2, "error opening file", ft_strlen("error opening file"));
	while ((ret = get_next_line(fd, &line)))
	{
		ft_putstr(line);
		ft_putchar('\n');

		/*
		printf("ret: %d\n", ret);
		if (ret == -1)
		{
			printf("error - returning -1\n");
			return (-1);
		}
		printf("the line that will be printed: %s\n", line);*/
	}
	return (0);
}
