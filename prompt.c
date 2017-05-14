/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 00:05:44 by lwang             #+#    #+#             */
/*   Updated: 2017/05/14 00:05:46 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_prompt(int sign, t_minfo *info, char *pwd, char *cur)
{
	if (sign)
	{
		recheck_env_path(info);
		if (info->home && !ft_strcmp(pwd, info->home))
			ft_printf(RED"$~ "CLN);
		else
			ft_printf(RED"$%s> "CLN, cur ? cur : pwd);
	}
	else
	{
		recheck_env_path(info);
		if (info->home && !ft_strcmp(pwd, info->home))
			ft_printf(GREE"$~ "CLN);
		else
			ft_printf(GREE"$%s> "CLN, cur ? cur : pwd);
	}
}

void		handle_prompt(int sign, t_minfo *info)
{
	char	buf[MAX_PATH_LENGTH + 1];
	char	*pwd;
	char	**tmp;
	char	*cur;

	pwd = getcwd(buf, MAX_PATH_LENGTH);
	cur = NULL;
	tmp = NULL;
	if ((ft_strcmp(pwd, "/")))
	{
		tmp = ft_strsplit(pwd, '/');
		if (!tmp)
			cur = ft_strdup("/");
		cur = ft_strdup(tmp[get_len(tmp) - 1]);
	}
	print_prompt(sign, info, pwd, cur);
	deep_free(tmp);
	free(cur);
}
