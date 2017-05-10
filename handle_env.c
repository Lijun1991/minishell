/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: THISISLWA <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 14:01:53 by THISISLWA         #+#    #+#             */
/*   Updated: 2017/05/09 14:01:55 by THISISLWA        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	buidin_setenv(t_minfo *info, const char *env_key, const char *env_value)
{
	int		i;
	char	*new_env_kv;
	int		find;
	char	**new_env;

	i = 0;
	find = 0;
	new_env = NULL;
	if (env_value)
		new_env_kv = ft_strcjoin(env_key, env_value, '=');
	else
		new_env_kv = ft_strjoin(env_key, "=");
	while (info->env[i])
	{
		if (!ft_strncmp(info->env[i], env_key, ft_strlen(env_key)))
		{
			find = 1;
			free(info->env[i]);
			info->env[i] = ft_strdup(new_env_kv);
			return ;
		}
		i++;
	}
	if (!find)
	{
		new_env = (char**)malloc(sizeof(char*) * (i + 1));
		i = 0;
		while (info->env[i])
		{
			new_env[i] = ft_strdup(info->env[i]);
			i++;
		}
		new_env[i] = ft_strdup(new_env_kv);
		new_env[++i] = NULL;
	}
	info->env = new_env;
}

int		buitin_cmd_setenv(t_minfo *info)
{
	char **tmp;

	if (info->av[2])
		return (1);
	tmp  = ft_strsplit(info->av[1], '=');
	if (check_str(info->av[1], '=') || !tmp || !tmp[0])
		return (1);
	buidin_setenv(info, tmp[0], tmp[1]);
	return (0);
}

int	buitin_cmd_unsetenv(t_minfo *info)
{
	int		i;
	int		j;
	char	**new_env;
	int		find;

	i = 0;
	find = 0;
	if (info->av[2])
		return (1);
	while (info->env[i])
	{
		if (!ft_strncmp(info->av[1], info->env[i], ft_strlen(info->av[1])))
			find = 1;
		i++;
	}
	if (find)
	{
		new_env = (char**)malloc(sizeof(char*) * (i));
		i = 0;
		j = 0;
		while (info->env[i])
		{
			if (ft_strncmp(info->av[1], info->env[i], ft_strlen(info->av[1])))
			{
				new_env[j] = ft_strdup(info->env[i]);
				j++;
			}
			i++;
		}
		new_env[j] = NULL;
		info->env = new_env;
	}
	return (0);
}

int		print_env(t_minfo *info)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 1;
	tmp = NULL;
	while (info->av[j])
	{
		tmp = ft_strsplit(info->av[j], '=');
		buidin_setenv(info, tmp[0], tmp[1]);
		j++;
	}
	while (info->env[i])
	{
		ft_printf("%s\n", info->env[i]);
		i++;
	}
	return (0);
}

int		buitin_cmd_env(t_minfo *info)
{
	int i;
	char	**env;

	//check if the last av = a commad
	// if it does, copy av into execve with tne new env
	//otherwise if its not command but a key=value
	//just display that.

	i = 0;
	while (info->av[i])
		i++;
	// if 

}







