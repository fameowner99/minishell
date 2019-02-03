/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 15:15:03 by vmiachko          #+#    #+#             */
/*   Updated: 2019/02/03 16:27:17 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*parse_path_variable(char *command_name, int i)
{
	char		**arr;
	char		*path;
	char		*tmp;

	path = NULL;
	if (!(tmp = getenv("PATH")))
		return (NULL);
	arr = ft_strsplit(tmp, ':');
	while (arr[i])
	{
		path = ft_strjoin(arr[i], command_name);
		if (!access(path, X_OK))
		{
			ft_free_2d((void*)arr);
			return (path);
		}
		else
		{
			free(path);
			path = NULL;
		}
		++i;
	}
	ft_free_2d((void*)arr);
	return (path);
}

int				parse_ls_pwd(char **arr, char **envp,
			char *command_name, char *command_path)
{
	char		*path;
	pid_t		pid;

	if (!ft_strcmp(arr[0], command_name))
	{
		if ((pid = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			if ((path = parse_path_variable(command_path, 0)))
			{
				execve(path, arr, envp);
				free(path);
			}
			else
				ft_printf(RED"minishell: command not found: %s\n"RESET,
			command_name);
			exit(EXIT_SUCCESS);
		}
		wait(NULL);
		return (TRUE);
	}
	return (FALSE);
}
