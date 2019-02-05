/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 12:42:29 by vmiachko          #+#    #+#             */
/*   Updated: 2019/02/05 12:45:11 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_dir_to_prev(char *dir, t_env *env)
{
	char	*tmp;

	chdir((tmp = get_env(env, "OLDPWD")));
	if (tmp)
		ft_printf(YELLOW"%s\n"RESET, tmp);
	else
		ft_printf(YELLOW"%s\n"RESET, dir);
	set_var(env, "OLDPWD", dir);
}

static void	change_dir(char *arr, char *dir, t_env *env)
{
	if (chdir(arr) == -1)
		ft_printf(RED"cd: no such file or directory: %s\n"RESET, arr);
	else
		set_var(env, "OLDPWD", dir);
}

int			parse_cd(char **arr, t_env *env)
{
	char	dir[MAXDIR];

	if (!ft_strcmp(arr[0], "cd"))
	{
		ft_memset(dir, '\0', MAXDIR);
		getcwd(dir, MAXDIR);
		if (!arr[1])
		{
			arr[1] = ft_strdup(get_env(env, "HOME"));
			arr[2] = NULL;
		}
		if (arr[1] && arr[2])
		{
			ft_printf(RED"cd : too many arguments\n"RESET);
			return (TRUE);
		}
		if (!ft_strcmp(arr[1], "-"))
		{
			change_dir_to_prev(dir, env);
			return (TRUE);
		}
		change_dir(arr[1], dir, env);
		return (TRUE);
	}
	return (FALSE);
}
