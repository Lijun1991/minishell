/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:27:43 by lwang             #+#    #+#             */
/*   Updated: 2017/05/09 15:02:52 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			wordcount(char *str, char c)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			j++;
	return (j);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**dst;
	int		len;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	dst = (char**)malloc(sizeof(char*) * (wordcount((char*)s, c) + 1));
	if (!dst)
		return (NULL);
	i = -1;
	j = 0;
	len = 0;
	while (s[++i])
	{
		if (s[i] != c)
			len++;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			dst[j++] = ft_strsub(s, i - len + 1, len);
			len = 0;
		}
	}
	dst[j] = 0;
	return (dst);
}
