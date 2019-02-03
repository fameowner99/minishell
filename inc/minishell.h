/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 20:18:09 by vmiachko          #+#    #+#             */
/*   Updated: 2019/02/03 15:13:55 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# define STDIN 0
# define STDOUT 1
# define TRUE 1
# define FALSE 0
# define CLEAR() ft_printf("\033[H\033[J")
# define MAXDIR 500
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>

void	minishell(char **envp);
int		parse_line(char *line, char **envp);
void	print_env(char **envp);
char	*parse_variable(char *arr, int i, int j);
char	*parse_cd_arg(char *arr);
int		parse_echo(char **arr);
int		parse_ls_pwd(char **arr, char **envp,
			char *command_name, char *command_path);
char	**unwrap(char **arr);

#endif
