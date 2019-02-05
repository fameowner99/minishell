/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 15:15:03 by vmiachko          #+#    #+#             */
/*   Updated: 2019/02/05 18:24:31 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_permission(char *path)
{
	struct stat file_stat;

	if (stat(path, &file_stat) < 0)
		return (-1);
	return (!S_ISDIR(file_stat.st_mode) && (file_stat.st_mode & S_IXUSR));
}

static char		*add(char *arr, char *command_name)
{
	char		*tmp;
	char		*path;

	path = ft_strjoin(arr, "/");
	tmp = path;
	path = ft_strjoin(tmp, command_name);
	free(tmp);
	return (path);
}

static char		*parse_path_v(char *command_name,
									int i, t_env env, int *flag)
{
	char		**arr;
	char		*path;
	char		*tmp;

	path = NULL;
	if (!(tmp = get_env(&env, "PATH")))
		return (NULL);
	arr = ft_strsplit(tmp, ':');
	while (arr[i])
	{
		path = add(arr[i], command_name);
		if ((*flag = check_permission(path)) > 0)
		{
			ft_free_2d((void*)arr);
			return (path);
		}
		else
			free(path);
		++i;
	}
	ft_free_2d((void*)arr);
	return (NULL);
}

int				parse_exec_command(char **arr, t_env env)
{
	char		*path;
	pid_t		pid;
	int			flag;

	if (arr[0] && (path = parse_path_v(arr[0], 0, env, &flag)))
	{
		if ((pid = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			execve(path, arr, env.arr);
			free(path);
			if (flag < 0)
				ft_printf(RED"something wrong with stat()\n"RESET);
			else
				ft_printf(RED"minishell: permission denied: %s\n"RESET,
					arr[0]);
			exit(EXIT_SUCCESS);
		}
		wait(NULL);
		path ? free(path) : 0;
		return (TRUE);
	}
	path ? free(path) : 0;
	return (FALSE);
}
