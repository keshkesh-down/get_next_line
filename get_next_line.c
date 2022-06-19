/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksejmironov <aleksejmironov@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 00:11:26 by sgendel           #+#    #+#             */
/*   Updated: 2022/06/19 19:47:51 by aleksejmiro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*make_line(char **str, int chars, char **buf)
{
	int		i;
	char	*line;
	char	*tmp;

	free(*buf);
	tmp = 0;
	if (chars < 0 || *str == 0)
		return (0);
	if (!chars && !ft_strchr(*str, '\n'))
	{
		line = ft_strdup(*str);
		free(*str);
		*str = 0;
		return (line);
	}
	i = 0;
	while ((*str)[i] != '\n')
		i++;
	line = ft_substr(*str, 0, i + 1);
	if ((int)ft_strlen(*str) - i - 1 >= 1)
		tmp = ft_substr(*str, i + 1, ft_strlen(*str) - i - 1);
	free(*str);
	*str = tmp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buf;
	char		*tmp;
	int			count;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	count = read(fd, buf, BUFFER_SIZE);
	while (count > 0)
	{
		buf[count] = '\0';
		if (str)
			tmp = ft_strjoin(str, buf);
		else
			tmp = ft_strdup(buf);
		str = tmp;
		if (ft_strchr(str, '\n'))
			break ;
		count = read(fd, buf, BUFFER_SIZE);
	}
	return (make_line(&str, count, &buf));
}

// int main(void)
// {
// 	int fd;
// 	int a;
// 	char *str;

// 	str = malloc(sizeof (char) * 1000);
// 	fd = open("text.txt", O_RDONLY);
// 	while ((str = get_next_line(fd)) != 0)
// 	{
// 		printf("%s", str);
// 		free(str);
// 	}
// 	free(str);
// 	return(0);
// }
