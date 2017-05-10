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

