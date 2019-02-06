/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 20:19:21 by vmiachko          #+#    #+#             */
/*   Updated: 2019/02/02 20:33:23 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		minishell(t_env *env)
{
	char	*line;
	int		running;

	line = NULL;
	running = TRUE;
	ft_printf(GREEN"==> "RESET);
	while (running)
	{
		if (get_next_line(STDIN, &line) <= 0)
			return ;
		running = parse_line(line, env);
		running ? ft_printf(GREEN"==> "RESET, line) : 0;
		line ? free(line) : 0;
		line = NULL;
	}
}

char		**unwrap(char **arr, t_env *env)
{
	int		row;
	char	*tmp;

	row = 0;
	while (arr[row])
	{
		tmp = arr[row];
		arr[row] = get_values_from_keys(arr[row], env);
		free(tmp);
		++row;
	}
	return (arr);
}
