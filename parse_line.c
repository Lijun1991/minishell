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

/*
int		get_av(char **av, t_minfo *info)
{
	int 	i;
	int		j;

	i = 1;
	j = 0;
	if (!(info->av = (char**)malloc(sizeof(char*) * MAX_PATH_LENGTH)))
		return (1);
	while (av[i])
	{
		info->av[j] = ft_strdup(av[i]);//..
		i++;
		j++;
	}
	info->av[j] = NULL;
	return (0);
}
*/
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
			refill_space(*tmp);
		// ft_printf("av is %s\n", *(*av)++);
		tmp++;
	}
	return (av);
}

void	parse_line(t_minfo *info, char *line)
{
	char **av;

	av = NULL;
	av = handle_qoated(line);

	info->av = av;
	//ft_printf("av[0] is %s\n", av[0]);
	//if (av[1])
	//	get_av(av, info);
	//ft_printf("happened.\n");
	// ft_printf("info->cmd is %s, and path is %s\n", info->cmd, info->cmd_path);
	
	if (info->av[0])
		info->cmd = ft_strdup(info->av[0]);//..
	else
		info->cmd = "";
	ck_cmd(info);
}

