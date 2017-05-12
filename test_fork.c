		/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 20:13:36 by lwang             #+#    #+#             */
/*   Updated: 2017/05/03 20:25:51 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int		main(int argc, char **argv, char **env)
{
	int		i;
	pid_t	pid;
	int		r;
	char	*av[] = {argv[2], argv[3], NULL};//"/bin/ls", "-l", "haa",

	r = -100;
	i = 0;
	pid = fork();
	if (pid == 0)
	{
		// i = getenv("i");
		printf("I'm the child! i=%s\n\n", getenv("i"));
		// execve(argv[2], av, env);
		// printf("Something terrible happened.\n");
		// exit(1);
	}
	else if (pid > 0)
	{
		wait(&r);
		// i = 42;
		printf("I'm the parent! i=%d\nChild returned with %d status\n", i, r);
	}
	else
	{
		printf("Failed to fork process.\n");
		exit(1);
	}
	printf("Exit program! i=%d\n", i);
}
