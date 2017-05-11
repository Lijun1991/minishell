/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:30:51 by lwang             #+#    #+#             */
/*   Updated: 2017/05/08 00:32:32 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**handle_qoated(char *line)
{
	char **av;
	char **tmp;

	change_space(line);
	av = line_split(line);
	tmp = av;
	while (*tmp)
	{
		if (**tmp == '"')
			cut_quos_refill_space(tmp);
		tmp++;
	}
	return (av);
}

void	parse_line(t_minfo *info)
{
	char **av;

	av = NULL;
	av = handle_qoated(info->line);
	info->av = av;
	if (info->av[0])
		info->cmd = ft_strdup(info->av[0]);
	else
		info->cmd = ft_strdup("");
}


