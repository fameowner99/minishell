/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 20:18:49 by vmiachko          #+#    #+#             */
/*   Updated: 2019/02/06 20:12:38 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	t_env	env;
	char	dir[MAXDIR];

	argc = (int)argc;
	argv = (void*)argv;
	env = copy_env(envp);
	getcwd(dir, MAXDIR);
	set_var(&env, "OLDPWD", dir);
	minishell(&env);
	return (0);
}
