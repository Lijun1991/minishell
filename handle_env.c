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

void	buitin_setenv(t_minfo *info, const char *env_key, const char *env_value)
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
			free(new_env_kv);
			return ;
		}
		i++;
	}
	if (!find)
	{
		new_env = (char**)malloc(sizeof(char*) * (i + 2));
		i = 0;
		while (info->env[i])
		{
			new_env[i] = ft_strdup(info->env[i]);
			free(info->env[i]);
			i++;
		}
		free(info->env);
		new_env[i] = ft_strdup(new_env_kv);
		free(new_env_kv);
		new_env[++i] = NULL;
	}
	info->env = new_env;
}

int		get_cmd_env(t_minfo *info, int len)
{
	int	err;
	int	i;
	int	j;

	err = 0;
	i = 1;
	j = 0;
	info->cmd_env = (char**)malloc(sizeof(char*) * (len - 1));
	while (info->av[i] && i < len - 1)
	{
		if ((err = check_str(info->av[i], '=')))
			return (err);
		info->cmd_env[j] = ft_strdup(info->av[i]);
		j++;
		i++;
	}
	info->cmd_env[j] = NULL;
	return (0);
}

int		handle_executable_file(t_minfo *info, int len)
{
	int			err;
	struct stat	s;

	err = 0;
	if (get_cmd_env(info, len))
		return (1);
	err = stat(info->av[len - 1], &s);
	if (err == -1)
	{
		ft_fprintf(2, "minishell: no such file or directory: %s\n", info->av[len - 1]);
		info->sign = 1;
	}
	else if (!(err = access(info->av[len - 1], X_OK)))
	{
		info->cmd_path = ft_strdup(info->av[len - 1]);
		exc_command(info);
	}
	else
	{
		ft_fprintf(2, "%s: Permission denied.\n", info->av[len - 1]);
		info->sign = 1;
	}
	return (0);
}
