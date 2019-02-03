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

void		print_env(char **envp)
{
	int		i;
	char	**arr;

	arr = envp;
	i = 0;
	while (arr[i])
	{
		ft_printf("%s\n", arr[i]);
		++i;
	}
}

void		minishell(char **envp)
{
	char	*line;
	char	**semicolon;
	int		running;
	int		i;

	line = NULL;
	running = TRUE;
	ft_printf(GREEN"==> "RESET);
	while (running)
	{
		if (get_next_line(STDIN, &line) <= 0)
			return ;
		semicolon = ft_strsplit(line, ';');
		i = 0;
		while (semicolon[i] && running)
		{
			running = parse_line(semicolon[i], envp);
			++i;
		}
		ft_free_2d((void*)semicolon);
		running ? ft_printf(GREEN"==> "RESET, line) : 0;
		line ? free(line) : 0;
		line = NULL;
	}
}

char		**unwrap(char **arr)
{
	int		row;
	char	*tmp;

	row = 0;
	while (arr[row])
	{
		tmp = arr[row];
		arr[row] = parse_cd_arg(arr[row]);
		free(tmp);
		++row;
	}
	return (arr);
}
