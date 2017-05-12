/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:38:01 by lwang             #+#    #+#             */
/*   Updated: 2017/05/11 14:38:04 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd(char *pre, char *cmd, char **path)
{
	char	*tmp;

	tmp = ft_strjoin(pre, "/");
	*path = ft_strjoin(tmp, cmd);
	free(tmp);
}

char	*ck_cmd(t_minfo *info)
{
	struct stat	sb;
	int			i;
	char		*new_path;

	i = 0;
	while (info->pre_path[i])
	{
		add_cmd(info->pre_path[i], info->cmd, &new_path);
		if (stat(new_path, &sb) != -1)
			info->cmd_path = ft_strdup(new_path);
		free(new_path);
		i++;
	}
	return (info->cmd_path);
}

int		handle_env_path(t_minfo *info)
{
	int		i;
	int		find;

	i = 0;
	find = 0;
	while (info->env[i])
	{
		if (!ft_strncmp(info->env[i], "PATH", 4))
		{
			find = 1;
			info->env_path = ft_strsub(info->env[i], 5, ((int)ft_strlen(info->env[i]) - 5));
		}
		if (!ft_strncmp(info->env[i], "HOME", 4))
			info->home = ft_strsub(info->env[i], 5, ((int)ft_strlen(info->env[i]) - 5));
		i++;
	}
	if (find)
		info->pre_path = ft_strsplit(info->env_path, ':');
	else
		return (1);
	return (0);
}
