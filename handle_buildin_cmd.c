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
	while (info->av[i])
	{
		ft_printf(info->av[i + 1] ? "%s " : "%s\n", info->av[i]);
		i++;
	}
	return (0);
}


int	buitin_cmd_cd(t_minfo *info)
{
	char	buf[MAX_PATH_LENGTH + 1];
	char	*pwd;
	struct stat	s;
	int		err;
	char	*dir;

	pwd = getcwd(buf, MAX_PATH_LENGTH);
	dir = info->av[1] == NULL ? info->home : info->av[1];

	err = stat(dir, &s);
	if (err == -1)
		ft_fprintf(2, "cd: no such file or directory: %s\n", dir);
	else if (!S_ISDIR(s.st_mode))
		ft_fprintf(2, "cd: not a directory: %s\n", dir);
	else if (!(err = access(dir, X_OK | R_OK)))
	{
		if (!(err = chdir(dir)))
		{
			buitin_setenv(info, "OLDPWD", pwd);
			buitin_setenv(info, "PWD", getcwd(buf, MAX_PATH_LENGTH));
		}
	}
	else
		ft_fprintf(2, "%s: Permission denied.\n", dir);
	return (err);
}

