/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:22:57 by lwang             #+#    #+#             */
/*   Updated: 2016/12/20 17:37:12 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	free_stdin(char **stock)
{
	free(stock[0]);
	stock[0] = NULL;
	return (-1);
}

int			check_stock_nl(char **stock, char **line, int fd)
{
	char *check;
	char *tmp;

	check = ft_strchr(stock[fd], (int)'\n');
	if (check != NULL)
	{
		*check = '\0';
		*line = ft_strdup(stock[fd]);
		if (!*line)
			return (-1);
		tmp = ft_strdup(check + 1);
		free(stock[fd]);
		stock[fd] = NULL;
		stock[fd] = ft_strdup(tmp);
		free(tmp);
		tmp = NULL;
		return (2);
	}
	return (0);
}

int			check_buf_nl(char **buf, char **stock, char **line, int fd)
{
	char *check;

	check = ft_strchr(*buf, (int)'\n');
	if (check != NULL)
	{
		*check = '\0';
		*line = ft_strmerge(stock[fd], *buf);
		if (!(*line))
			return (-1);
		stock[fd] = ft_strdup(check + 1);
		free(*buf);
		*buf = NULL;
		return (2);
	}
	return (0);
}

int			the_end(int fd, char *buf, char **stock, char **line)
{
	free(buf);
	buf = NULL;
	if (stock[fd] == NULL || ft_strcmp(stock[fd], "") == 0)
	{
		free(stock[fd]);
		stock[fd] = NULL;
		return (0);
	}
	*line = ft_strdup(stock[fd]);
	if (!(*line))
		return (-1);
	free(stock[fd]);
	stock[fd] = NULL;
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	int			ret;
	char		*buf;
	static char	*stock[MAX_FD];

	if (fd == -42 || fd < 0 || fd > MAX_FD || line == NULL)
		return (fd == -42 ? free_stdin(stock) : -1);
	if (stock[fd] != NULL)
		if (check_stock_nl(stock, line, fd) == 2)
			return (1);
	if (!stock[fd])
		stock[fd] = ft_strdup("");
	buf = ft_strnew(BUFF_SIZE + 1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (check_buf_nl(&buf, stock, line, fd) == 2)
			return (1);
		stock[fd] = ft_strmerge(stock[fd], buf);
		free(buf);
		buf = ft_strnew(BUFF_SIZE);
	}
	if (ret == -1)
		return (-1);
	return (the_end(fd, buf, stock, line));
}
