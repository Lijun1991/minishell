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

int		buitin_cmd_setenv(t_minfo *info)
{
	char **tmp;

	if (info->av[2])
		return (1);
	tmp  = ft_strsplit(info->av[1], '=');
	if (check_str(info->av[1], '=') || !tmp || !tmp[0])
	{
		deep_free(tmp);
		return (1);
	}
	buitin_setenv(info, tmp[0], tmp[1]);
	deep_free(tmp);
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

	i = 0;
	j = 1;
	if (info->cmd_env)
	{
		while (info->cmd_env[i])
		{
			ft_printf("%s\n", info->cmd_env[i]);
			i++;
		}
	}
	else
	{
		while (info->env[i])
		{
				ft_printf("%s\n", info->env[i]);
			i++;
		}
	}
	return (0);
}

int		buitin_cmd_env(t_minfo *info)
{
	int		i;
	int		j;
	int		len;
	struct stat s;
	int		err;

	i = 1;
	len = 0;
	j = 0;
	err = 0;
	handle_env_path(info);

	if (!ft_strcmp(info->env_path, ""))
	{
		ft_fprintf(2, "minishell: command not found: %s\n", info->cmd);
		return (1);
	}
	while (info->av[len])
		len++;
	if (len == 1 && ft_strcmp(info->env_path, ""))
		print_env(info);
	else if (len > 1 && ft_strchr(info->av[len - 1], '/'))
	{
		info->cmd_env = (char**)malloc(sizeof(char*) * (len - 1));
		while (info->av[i] && i < len - 1)
		{
			ft_printf("info->av[i] is %s\n", info->av[i]);
			if ((err = check_str(info->av[i], '=')))
				return (err);
			info->cmd_env[j] = ft_strdup(info->av[i]);
			j++;
			i++;
		}
		info->cmd_env[j] = NULL;

		err = stat(info->av[len - 1], &s);
		if (err == -1)
			ft_fprintf(2, "cd: no such file or directory: %s\n", info->av[len - 1]);
		// else if (!S_ISDIR(s.st_mode))
		// 	ft_fprintf(2, "cd: not a directory: %s\n", info->av[len - 1]);
		else if (!(err = access(info->av[len - 1], X_OK)))
		{
			info->cmd_path = ft_strdup(info->av[len - 1]);
			exc_command(info);
		}
		else
			ft_fprintf(2, "%s: Permission denied.\n", info->av[len - 1]);
	}
	else
		ft_fprintf(2, "None support situation\n");
	return(err);
}






