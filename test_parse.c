/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:05:41 by lwang             #+#    #+#             */
/*   Updated: 2017/05/05 17:08:40 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/libft.h"
// # define WHITE_SPACE(a) (a == ' ' || a == '\t' || a == '\v' || a == '\r')

// int			line_wordcount(char *str)
// {
// 	int		i;
// 	int		j;

// 	i = -1;
// 	j = 0;
// 	while (str[++i])
// 		if (!WHITE_SPACE(str[i]) && (WHITE_SPACE(str[i + 1]) || str[i + 1] == '\0'))
// 			j++;
// 	return (j);
// }

// char		**line_split(char const *s)
// {
// 	char	**dst;
// 	int		len;
// 	int		i;
// 	int		j;

// 	if (!s)
// 		return (0);
// 	dst = (char**)malloc(sizeof(char*) * (line_wordcount((char*)s) + 1));
// 	if (!dst)
// 		return (0);
// 	i = -1;
// 	j = 0;
// 	len = 0;
// 	while (s[++i])
// 	{
// 		if (!WHITE_SPACE(s[i]))
// 			len++;
// 		if (!WHITE_SPACE(s[i]) && (WHITE_SPACE(s[i]) || s[i + 1] == '\0'))
// 		{
// 			dst[j++] = ft_strsub(s, i - len + 1, len);
// 			len = 0;
// 		}
// 	}
// 	dst[j] = 0;
// 	return (dst);
// }

int			line_wordcount(char *str)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\v' && str[i] != '\r' && \
			(str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\v' || str[i + 1] == '\r' || str[i + 1] == '\0'))
			j++;
	return (j);
}

char		**line_split(char const *s)
{
	char	**dst;
	int		len;
	int		i;
	int		j;

	if (!s)
		return (0);
	dst = (char**)malloc(sizeof(char*) * (line_wordcount((char*)s) + 1));
	if (!dst)
		return (0);
	i = -1;
	j = 0;
	len = 0;
	while (s[++i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\v' && s[i] != '\r')
			len++;
		if (s[i] !=  ' ' && s[i] != '\t' && s[i] != '\v' && s[i] != '\r' \
			&& (s[i + 1] == ' ' || s[i + 1] == '\t' || s[i + 1] == '\v' || s[i + 1] == '\r' || s[i + 1] == '\0'))
		{
			dst[j++] = ft_strsub(s, i - len + 1, len);
			len = 0;
		}
	}
	dst[j] = 0;
	return (dst);
}

void	fill_space_helper(char *line, int start, int end)
{
	while (line[start] != '\0' && start <= end)
	{
		if (line[start] == ' ')
			line[start] = 01;
		else if (line[start] == '\t')
			line[start] = 02;
		else if (line[start] == '\v')
			line[start] = 03;
		else if (line[start] == '\r')
			line[start] = 04;
		start++;
	}
}

void	change_space(char *line)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = 0;
	while (line[i] != '\0')
	{
		while (line[i] != '"' && line[i] != '\0')
			i++;
		start = i;
		i++;
		while (line[i] != '"' && line[i] != '\0')
			i++;
		end = i;
		i++;
		if (end != 0)
		{
			fill_space_helper(line, start, end);
		}
	}
}

void	refill_space(char *av)
{
	int i;

	i = 0;
	while (av[i])
	{
		if (av[i] == 01)
			av[i] = ' ';
		else if (av[i] == 02)
			av[i] = '\t';
		else if (av[i] == 03)
			av[i] = '\v';
		else if (av[i] == 04)
			av[i] = '\r';
		i++;
	}
}

int main(void)
{
	char *line;
	char **av;

	get_next_line(0, &line);
	change_space(line);
	av = line_split(line);
	while (*av)
	{
		if (**av == '"')
			refill_space(*av);
		// ft_printf("%s\n", *av++);
	}
}
