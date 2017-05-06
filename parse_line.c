/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:30:51 by lwang             #+#    #+#             */
/*   Updated: 2017/05/05 17:30:53 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_av(char **av, t_minfo *info)
{
	int 	i;

	i = 0;
	if (!(info->av = (char**)malloc(sizeof(char*) * MAX_PATH_LENGTH)))
		return (1);
	while (av[i])
	{
		info->av[i] = ft_strdup(av[i]);//..
		i++;
	}
	info->av[i] = NULL;
	return (0);
}

void	parse_line(t_minfo *info, char *line)
{
	char **av;

	av = line_split(line);
	get_av(av, info);
	if (info->av[0])
		info->cmd = ft_strdup(info->av[0]);//..
	else
		info->cmd = "";
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
