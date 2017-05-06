/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:05:41 by lwang             #+#    #+#             */
/*   Updated: 2017/05/05 17:08:40 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/libft.h"

int			line_wordcount(char *str)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i])
		if (!WHITE_SPACE(str[i]) && (WHITE_SPACE(str[i + 1]) || str[i + 1] == '\0'))
			j++;
	return (j);
}

char		**line_split(char const *s)
{
	char	**dst;
	int		len;
	int		i;
	int		j;

	if (!s)
		return (0);
	dst = (char**)malloc(sizeof(char*) * (line_wordcount((char*)s) + 1));
	if (!dst)
		return (0);
	i = -1;
	j = 0;
	len = 0;
	while (s[++i])
	{
		if (!WHITE_SPACE(str[i]))
			len++;
		if (!WHITE_SPACE(str[i]) && (!WHITE_SPACE(str[i]) || s[i + 1] == '\0'))
		{
			dst[j++] = ft_strsub(s, i - len + 1, len);
			len = 0;
		}
	}
	dst[j] = 0;
	return (dst);
}

int main(void)
{
	char *line;
	char **av;

	get_next_line(0, &line);
	av = line_split(line);
	// av = ft_strsplit(line, ' ');
	while (*av)
		printf("%s\n", *av++);
}
