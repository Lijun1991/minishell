/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 13:43:36 by lwang             #+#    #+#             */
/*   Updated: 2017/05/09 13:43:38 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcjoin(const char *a, const char *b, char c)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 0;
	if (!a || !b)
		return (NULL);
	dst = (char*)malloc(sizeof(char) * (ft_strlen(a) + ft_strlen(b) + 2));
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

int		check_str(char *str, char c)
{
	int		i;
	char	*check;

	i = 0;
	if (!(check = ft_strchr(str, c)))
	{
		ft_fprintf(2, "env: %s: No such file or directory\n", str);
		return (1);
	}
	if (str[0] == c)
	{	
		ft_fprintf(2, "zsh: %s not found", check);
		return (1);
	}
	return (0);
}

void	recheck_env_path(t_minfo *info)
{
	free(info->env_path);
	free(info->home);
	info->home = NULL;
	info->env_path = NULL;
	handle_env_path(info);
}

void	handle_prompt(int sign, t_minfo *info)
{
	char	buf[MAX_PATH_LENGTH + 1];
	char	*pwd;

	pwd = getcwd(buf, MAX_PATH_LENGTH);
	if (sign)
	{
		recheck_env_path(info);
		if (info->home && !ft_strcmp(pwd, info->home))
			ft_printf(RED"$~"CLN);
		else
			ft_printf(RED"$>"CLN);
	}
	else
	{
		recheck_env_path(info);
		if (info->home && !ft_strcmp(pwd, info->home))
			ft_printf("$~");
		else
			ft_printf("$>");
	}
}

int		print_env(t_minfo *info)
{
	int		i;

	i = 0;
	while (info->env[i])
	{
		ft_printf("%s\n", info->env[i]);
		i++;
	}
	return (0);
}
