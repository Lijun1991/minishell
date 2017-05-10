/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 19:59:32 by lwang             #+#    #+#             */
/*   Updated: 2017/05/09 22:52:27 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

////test char **env

// int		main(int argc, char **argv, char **env)
// {
// 	int		i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		printf("%s\n", env[i]);
// 		i++;
// 	}
// }


////test cjoin function dd
// char	*ft_strcjoin(const char *a, const char *b, char c)
// {
// 	int		i;
// 	int		j;
// 	int		size;
// 	char	*dst;

// 	i = 0;
// 	j = 0;
// 	if (!a || !b)
// 		return (NULL);
// 	size = strlen(a) + strlen(b);
// 	dst = (char*)malloc(sizeof(char) * (size + 2));
// 	if (!dst)
// 		return (NULL);
// 	while (a[i])
// 	{
// 		dst[i] = a[i];
// 		i++;
// 	}
// 	dst[i] = c;
// 	i++;
// 	while (b[j])
// 	{
// 		dst[i + j] = b[j];
// 		j++;
// 	}
// 	dst[i + j] = '\0';
// 	return (dst);
// }

// int main(void)
// {
// 	printf("%s\n", ft_strcjoin("123456", "lksdjfksdhf", '='));
// 	return (0);
// }

////test setenv & unsetenv

int main(int argc, char **argv, char **env)
{
	int		i;

	i = 0;
	printf("The env is:\n");
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}














































