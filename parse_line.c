/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:30:51 by lwang             #+#    #+#             */
/*   Updated: 2017/05/11 21:21:45 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_qoute(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '"')
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (0);
	else
		return (1);
	return (0);
}

static char	**handle_qoated(char *line)
{
	char **av;
	char **tmp;

	if (count_qoute(line))
		return (NULL);
	change_space(line);
	av = line_split(line);
	if (!av)
		return (NULL);
	tmp = av;
	while (*tmp)
	{
		if (**tmp == '"')
			cut_quos_refill_space(tmp);
		tmp++;
	}
	return (av);
}

static void	repalce_tilde_sign(char **str, t_minfo *info)
{
	char *tmp;

	tmp = NULL;
	if ((tmp = ft_strchr(*str, '~')))
	{
		tmp = ft_strsub(*str, 1, ft_strlen(*str) - 1);
		if (info->home)
		{
			free(*str);
			*str = NULL;
			*str = ft_strjoin(info->home, tmp);
		}
		else
			*str = ft_strdup("");
	}
	free(tmp);
}

int			parse_line(t_minfo *info)
{
	char	**av;
	int		i;

	i = 0;
	recheck_env_path(info);
	av = NULL;
	av = handle_qoated(info->line);
	if (!av)
		return (1);
	while (av[i])
	{
		repalce_tilde_sign(&av[i], info);
		i++;
	}
	info->av = av;
	if (info->av[0])
		info->cmd = ft_strdup(info->av[0]);
	else
		info->cmd = ft_strdup("");
	return (0);
}
