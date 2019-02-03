/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 20:34:32 by vmiachko          #+#    #+#             */
/*   Updated: 2019/02/03 17:50:59 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			parse_dir(char **arr)
{
	if (!ft_strcmp(arr[0], "clear"))
	{
		CLEAR();
		return (TRUE);
	}
	return (FALSE);
}

int			parse_env(char **arr, char **envp)
{
	if (!ft_strcmp(arr[0], "env"))
	{
		print_env(envp);
		return (TRUE);
	}
	if (!ft_strcmp(arr[0], "setenv"))
	{
		if (!arr[1] || !arr[2])
			ft_printf(RED"Usage : setenv [name] [value]\n"RESET);
		else
			setenv(arr[1], arr[2], TRUE);
		return (TRUE);
	}
	if (!ft_strcmp(arr[0], "unsetenv"))
	{
		if (!arr[1])
			ft_printf(RED"Usage : unsetenv [name]\n"RESET);
		else
			unsetenv(arr[1]);
		return (TRUE);
	}
	return (FALSE);
}

int			parse_cd(char **arr)
{
	if (!ft_strcmp(arr[0], "cd"))
	{
		if (!arr[1])
		{
			arr[1] = ft_strdup(getenv("HOME"));
			arr[2] = NULL;
		}
		if (arr[1] && arr[2])
		{
			ft_printf(RED"cd : too many arguments\n"RESET);
			return (TRUE);
		}
		if (chdir(arr[1]) == -1)
			ft_printf(RED"cd: no such file or directory: %s\n"RESET, arr[1]);
		return (TRUE);
	}
	return (FALSE);
}

static int	choose_command(char **arr, char **envp, int length)
{
	int		error;

	error = FALSE;
	if (length > 0)
	{
		error |= parse_dir(arr);
		error |= parse_env(arr, envp);
		error |= parse_cd(arr);
		error |= parse_echo(arr);
		error |= parse_ls_pwd(arr, envp, "ls", "/ls");
		error |= parse_ls_pwd(arr, envp, "pwd", "/pwd");
	}
	return (error);
}

int			parse_line(char *line, char **envp)
{
	char	**arr;
	int		error;
	int		length;

	arr = ft_strsplit(line, ' ');
	if (!arr[0])
	{
		ft_free_2d((void**)arr);
		return (TRUE);
	}
	arr = unwrap(arr);
	length = (int)ft_strlen(arr[0]);
	if (length == 4 && !ft_strcmp(arr[0], "exit"))
	{
		ft_free_2d((void**)arr);
		return (FALSE);
	}
	error = choose_command(arr, envp, length);
	if (error == FALSE && ft_strlen(arr[0]) > 0)
		ft_printf(RED"minishell: command not found: %s\n"RESET, arr[0]);
	ft_free_2d((void**)arr);
	return (TRUE);
}
