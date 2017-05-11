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