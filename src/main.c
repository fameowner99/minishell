/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 20:18:49 by vmiachko          #+#    #+#             */
/*   Updated: 2019/02/03 16:26:39 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_printf("received SIGINT\n");
		ft_printf(GREEN"==>"RESET);
	}
}

int		main(int argc, char **argv, char **envp)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		ft_printf("\ncan't catch SIGINT\n");
	argc = (int)argc;
	argv = (void*)argv;
	minishell(envp);
	return (0);
}
