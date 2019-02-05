/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 20:18:49 by vmiachko          #+#    #+#             */
/*   Updated: 2019/02/05 12:21:05 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_printf("received SIGINT\n");
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_env	env;
	char	dir[MAXDIR];

	if (signal(SIGINT, sig_handler) == SIG_ERR)
		ft_printf("\ncan't catch SIGINT\n");
	argc = (int)argc;
	argv = (void*)argv;
	env = copy_env(envp);
	getcwd(dir, MAXDIR);
	set_var(&env, "OLDPWD", dir);
	minishell(&env);
	return (0);
}
