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
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	if (count != 1)
		return (1);
	return (0);
}