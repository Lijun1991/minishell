/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 20:32:13 by lwang             #+#    #+#             */
/*   Updated: 2017/05/03 21:21:36 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell(char **argv, t_minfo *info)
{
	while(/* not exit */)
	{
		//Parse input in commands i.e. use gnl -- CHECK FOR ERRORS, NOT SEGFAULT OR LEAK!!!
		//Check if commands if a buitin i.e echo, cd, setenv, unsetenv, env or exit
		//if not, check if is in the PATH, before fork, check for access
//	then fork, parent waits, child execve
		//if not, display error
		//cleanup memory
	}
}
