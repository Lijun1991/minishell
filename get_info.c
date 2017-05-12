/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 00:46:29 by lwang             #+#    #+#             */
/*   Updated: 2017/05/08 00:30:31 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		copy_env(char **env, t_minfo *info)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	if (!(info->env = (char**)malloc(sizeof(char*) * (i + 1))))
		return (1);
	i = 0;
	while (env[i])
	{
		info->env[i] = ft_strdup(env[i]);//..
		i++;
	}
	info->env[i] = NULL;
	return (0);
}


int		get_info(char **av, char **env, t_minfo *info)
{
	if (!info)
		return (1);
	if (av[1])
		return (1);
	if (copy_env(env, info))
		return (1);
	handle_env_path(info);
	return (0);
}

