/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 23:08:17 by lwang             #+#    #+#             */
/*   Updated: 2017/05/07 23:08:20 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_space_helper(char *line, int start, int end)
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
		if (line[i] != '\0')
			i++;
		while (line[i] != '"' && line[i] != '\0')
			i++;
		end = i;
		if (line[i] != '\0')
			i++;
		if (end != 0)
			fill_space_helper(line, start, end);
	}
}

void	cut_quos_refill_space(char **tmp)
{
	int i;
	char	*p2;
	char	*av;

	av = *tmp;
	i = -1;
	while (av[++i])
		if (av[i] == 01)
			av[i] = ' ';
		else if (av[i] == 02)
			av[i] = '\t';
		else if (av[i] == 03)
			av[i] = '\v';
		else if (av[i] == 04)
			av[i] = '\r';
	if (av[0] == '"' && (p2 = ft_strchr(&av[1], '"')))
	{
		*p2 = '\0';
		av = ft_strdup(av + 1);
		free(*tmp);
		*tmp = av;
	}
}

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
		return (NULL);
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

