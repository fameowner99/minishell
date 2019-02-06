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

int			parse_env(char **arr, t_env *env)
{
	if (!ft_strcmp(arr[0], "env"))
	{
		print_env(*env);
		return (TRUE);
	}
	if (!ft_strcmp(arr[0], "setenv"))
	{
		if (!arr[1] || !arr[2])
			ft_printf(RED"Usage : setenv [name] [value]\n"RESET);
		else
			set_var(env, arr[1], arr[2]);
		return (TRUE);
	}
	if (!ft_strcmp(arr[0], "unsetenv"))
	{
		if (!arr[1])
			ft_printf(RED"Usage : unsetenv [name]\n"RESET);
		else
			unset_var(env, arr[1]);
		return (TRUE);
	}
	return (FALSE);
}

static int	choose_command(char **arr, t_env *env, int length)
{
	int		error;

	error = FALSE;
	if (length > 0)
	{
		error |= parse_dir(arr);
		error |= parse_env(arr, env);
		error |= parse_cd(arr, env);
		error |= parse_echo(arr);
		if (error)
			return (error);
		error |= parse_exec_command(arr, *env);
		if (error)
			return (error);
		error |= exec_command(arr, *env);
	}
	return (error);
}

int			parse_line(char *line, t_env *env)
{
	char	**arr;
	int		error;
	int		length;

	arr = split_line(line);
	if (!arr)
		return (TRUE);
	if (!arr[0])
	{
		ft_free_2d((void**)arr);
		return (TRUE);
	}
	arr = unwrap(arr, env);
	length = (int)ft_strlen(arr[0]);
	if (length == 4 && !ft_strcmp(arr[0], "exit"))
	{
		ft_free_2d((void**)arr);
		return (FALSE);
	}
	error = choose_command(arr, env, length);
	if (error == FALSE && ft_strlen(arr[0]) > 0)
		ft_printf(RED"minishell: command not found: %s\n"RESET, arr[0]);
	ft_free_2d((void**)arr);
	return (TRUE);
}
