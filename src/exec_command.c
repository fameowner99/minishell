/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 15:57:24 by vmiachko          #+#    #+#             */
/*   Updated: 2019/02/05 17:39:13 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_command(char **arr, t_env env)
{
	pid_t		pid;
	int			v;

	if (arr[0] && (arr[0][0] == '/'
		|| (arr[0][0] == '.' && arr[0][1] == '/')))
	{
		if ((v = check_permission(arr[0])) > 0)
		{
			if ((pid = fork()) == -1)
				exit(EXIT_FAILURE);
			else if (pid == 0)
				execve(arr[0], arr, env.arr);
		}
		else if (v == 0)
			ft_printf(RED"minishell: permission denied: %s\n"RESET,
					arr[0]);
		else
			ft_printf(RED"minishell: no such file or directory\n"RESET);
		wait(NULL);
		return (TRUE);
	}
	return (FALSE);
}
