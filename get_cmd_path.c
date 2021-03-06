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

static int	check_env_content(t_minfo *info, char *tmp, char **str)
{
	int i;

	i = 0;
	while (info->env[i])
	{
		if (!ft_strncmp(info->env[i], tmp, ft_strlen(tmp)))
		{
			free(*str);
			*str = NULL;
			*str = ft_strsub(info->env[i], ft_strlen(tmp) + 1, \
				((int)ft_strlen(info->env[i]) - ft_strlen(tmp) - 1));
			return (1);
		}
		i++;
	}
	return (0);
}

void		check_dollor_sign(char **str, t_minfo *info)
{
	int		i;
	char	*tmp;
	int		find;

	i = 0;
	tmp = NULL;
	find = 0;
	if (*str[0] == '$')
	{
		tmp = ft_strsub(*str, 1, (ft_strlen(*str) - 1));
		if (!check_env_content(info, tmp, str))
		{
			free(*str);
			*str = NULL;
			*str = ft_strdup("");
		}
	}
	free(tmp);
}

void		add_cmd(char *pre, char *cmd, char **path)
{
	char	*tmp;

	tmp = ft_strjoin(pre, "/");
	*path = ft_strjoin(tmp, cmd);
	free(tmp);
}

char		*ck_cmd(t_minfo *info)
{
	struct stat	sb;
	int			i;
	char		*new_path;

	i = 0;
	if (info->env_path && ft_strcmp(info->env_path, ""))
	{
		deep_free(info->pre_path);
		info->pre_path = ft_strsplit(info->env_path, ':');
		free(info->env_path);
		info->env_path = NULL;
	}
	else
		return (NULL);
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

int			get_cmd_path(t_minfo *info)
{
	struct stat s;

	if (ft_strcmp(info->cmd, "/") && ft_strchr(info->cmd, '/'))
	{
		info->cmd_path = ft_strdup(info->cmd);
		if (stat(info->cmd_path, &s) == -1)
		{
			ft_fprintf(2, "minishell: no such file or directory: %s\n", \
				info->cmd_path);
			return (0);
		}
		if (!access(info->cmd_path, X_OK))
			return (0);
		else
		{
			ft_fprintf(2, "minishell: permission denied: %s\n", \
				info->cmd);
			return (0);
		}
	}
	else if (info->env && ck_cmd(info))
		return (0);
	else
		return (1);
	return (0);
}
