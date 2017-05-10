/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 10:08:48 by lwang             #+#    #+#             */
/*   Updated: 2017/05/05 10:08:50 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	deep_free(char **dst)
{
	int i;

	i = 0;
	if (dst)
		while (dst[i])
		{
			free(dst[i]);
			i++;
		}
	free(dst);
	dst = NULL;
}

void	free_for_loop(t_minfo *info)
{
	deep_free(info->av);
	info->av = NULL;
	free(info->cmd);
	info->cmd = NULL;
	free(info->cmd_path);
	info->cmd_path = NULL;
	free(info->line);
	info->line = NULL;
}

void	free_everything(t_minfo *info)
{
	if (info->av)
		deep_free(info->av);
	info->av = NULL;
	free(info->cmd);
	info->cmd = NULL;
	free(info->cmd_path);
	info->cmd_path = NULL;
	deep_free(info->env);
	free(info->home);
	info->home = NULL;
	free(info->env_path);
	info->env_path = NULL;
	deep_free(info->pre_path);
	free(info->line);
	// get_next_line(-42, NULL);
}