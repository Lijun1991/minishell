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

int		buitin_cmd_echo(t_minfo *info)
{
	int		i;

	i = 1;
	recheck_env_path(info);
	while (info->av[i])
	{
		check_dollor_sign(&info->av[i], info);
		ft_printf(info->av[i + 1] ? "%s " : "%s\n", info->av[i]);
		i++;
	}
	return (0);
}

int		buitin_cmd_cd(t_minfo *info)
{
	char		buf[MAX_PATH_LENGTH + 1];
	char		*pwd;
	struct stat	s;
	char		*dir;

	pwd = getcwd(buf, MAX_PATH_LENGTH);
	recheck_env_path(info);
	if (!info->home || !ft_strcmp(info->home, ""))
		info->home = ft_strdup(pwd);
	dir = !info->av[1] ? info->home : info->av[1];
	if ((info->err = stat(dir, &s) == -1))
		ft_fprintf(2, "cd: no such file or directory: %s\n", dir);
	else if (!S_ISDIR(s.st_mode))
		ft_fprintf(2, "cd: not a directory: %s\n", dir);
	else if (!(info->err = access(dir, X_OK | R_OK)))
	{
		if (!(info->err = chdir(dir)))
		{
			buitin_setenv(info, "OLDPWD", pwd);
			buitin_setenv(info, "PWD", getcwd(buf, MAX_PATH_LENGTH));
		}
	}
	else
		ft_fprintf(2, "%s: Permission denied.\n", dir);
	return (info->err);
}

int		buitin_cmd_env(t_minfo *info)
{
	int	len;

	len = 0;
	while (info->av[len])
		len++;
	if (len == 1)
		print_env(info);
	else if (len > 1 && ft_strchr(info->av[len - 1], '/'))
	{
		if (handle_executable_file(info, len))
			return (1);
	}
	else
	{
		ft_fprintf(2, "None support\n");
		info->sign = 1;
	}
	return (0);
}

int		buitin_cmd_setenv(t_minfo *info)
{
	char **tmp;

	if (info->av[2])
	{
		ft_fprintf(2, "setenv err\n");
		return (1);
	}
	tmp = ft_strsplit(info->av[1], '=');
	if (check_str(info->av[1], '=') || !tmp || !tmp[0])
	{
		deep_free(tmp);
		return (1);
	}
	buitin_setenv(info, tmp[0], tmp[1]);
	deep_free(tmp);
	return (0);
}

int		buitin_cmd_unsetenv(t_minfo *info)
{
	int		i;
	int		j;
	char	**new_env;

	if (info->av[2])
		return (1);
	if (ck_env_content(info, &i) && !(j = 0))
	{
		new_env = (char**)malloc(sizeof(char*) * (i));
		i = 0;
		while (info->env[i])
		{
			if (ft_strncmp(info->av[1], info->env[i], ft_strlen(info->av[1])))
			{
				new_env[j] = ft_strdup(info->env[i]);
				j++;
			}
			free(info->env[i]);
			i++;
		}
		new_env[j] = NULL;
		free(info->env);
		info->env = new_env;
	}
	return (0);
}
