/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 00:46:29 by lwang             #+#    #+#             */
/*   Updated: 2017/05/04 00:46:34 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_env(char **env, char **dst)
{
	int		i;

	i = 0;
	while (*env++)
		i++;
	ft_printf("env line toal is %d\n", i);
	dst = (char**)malloc(sizeof(char*) * (i + 1));
	if (!dst)
		return (NULL);
	while (*env++)
		*dst++ = ft_strdup(*env);//..
	*dst = NULL;//////////////////..............segfault somewherre
}

void	add_cmd(char *pre, char *cmd, char **path)
{
	char	*tmp;

	tmp = ft_strjoin(pre, "/");
	*path = ft_strjoin(tmp, cmd);
	free(tmp);
}

void	ck_cmd(t_minfo *info)
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
}

void	handle_env_path(t_minfo *info)
{
	int		i;

	i = 0;
	while (info->env[i])
	{
		if (!ft_strncmp(info->env[i], "PATH", 4))
			info->env_path = ft_strsub(info->env[i], 5, ((int)ft_strlen(info->env[i]) - 4));//..
		if (!ft_strncmp(info->env[i], "HOME", 4))
			info->home = ft_strsub(info->env[i], 5, ((int)ft_strlen(info->env[i]) - 4));//..
		i++;
	}
	info->pre_path = ft_strsplit(info->env_path, ':');
	ck_cmd(info);
}

int		get_info(int ac, char **av, char **env, t_minfo *info)
{
	if (!(info->av = (char**)malloc(sizeof(char*))))
		return (1);
	if (!info)
		return (1);
	info->ac = ac;
	copy_env(env, info->env);
	while (*++av)
		*(info->av)++ = ft_strdup(*av);//..
	*(info->av) = NULL;
	if (info->av[0])
		info->cmd = ft_strdup(av[0]);//..
	else
		info->cmd = NULL;
	if (env && info->env)
		handle_env_path(info);
	else
		return (1);
	return (0);
}