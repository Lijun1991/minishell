/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_buildin_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 21:06:30 by lwang             #+#    #+#             */
/*   Updated: 2017/05/08 21:06:33 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	buitin_cmd_echo(t_minfo *info)
{
	int		i;

	i = 1;
	while (info->av[i])
	{
		ft_printf(info->av[i + 1] ? "%s " : "%s\n", info->av[i]);
		i++;
	}
}

char	*ft_strcjoin(const char *a, const char *b, char c)
{
	int		i;
	int		j;
	int		size;
	char	*dst;

	i = 0;
	j = 0;
	if (!a || !b)
		return (NULL);
	size = strlen(a) + strlen(b);
	dst = (char*)malloc(sizeof(char) * (size + 2));
	if (!dst)
		return (NULL);
	while (a[i])
	{
		dst[i] = a[i];
		i++;
	}
	dst[i] = c;
	i++;
	while (b[j])
	{
		dst[i + j] = b[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}

void	buidin_setenv(t_minfo *info, const char *env_key, const char *env_value)
{
	int		i;
	char	*new_env_kv;

	i = 0;
	new_env_kv = ft_strcjoin(env_key, env_value, '=');
	while (info->env[i])
	{
		if (!ft_strncmp(info->env[i], env_key, ft_strlen(env_key)))
		{
			free(info->env[i]);
			info->env[i] = ft_strdup(new_env_kv);
			return ;
		}
		i++;
	}
	info->env[i] = ft_strdup(new_env_kv);
	i++;
	info->env[i] = NULL;
}


int	buitin_cmd_cd(t_minfo *info)
{
	char	buf[MAX_PATH_LENGTH + 1];
	char	*pwd;
	int		err;

	if (info->av[2])
		ft_fprintf(2, "cd: string not in pwd: %s\n", info->av[1]);

	pwd = getcwd(buf, MAX_PATH_LENGTH);
	if (!(err = access(info->av[1], X_OK | R_OK)))
	{
		if (!(err = chdir(info->av[1])))
		{
			buidin_setenv(info, "OLDPWD", pwd);
			buidin_setenv(info, "PWD", getcwd(buf, MAX_PATH_LENGTH));
		}
	}
	else
		ft_fprintf(2, "%s: Permission denied.\n", info->av[1]);
	return (err);
}

void	buitin_cmd_setenv(t_minfo *info)
{
	char **tmp;

	if (info->av[2])
		return ;
	tmp  = ft_strsplit(info->av[1], '=');
	buidin_setenv(info, tmp[0], tmp[1]);
}



