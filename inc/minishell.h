/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 20:18:09 by vmiachko          #+#    #+#             */
/*   Updated: 2019/02/05 12:19:51 by vmiachko         ###   ########.fr       */
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
# include <sys/stat.h>

typedef struct	s_env
{
	char		**arr;
	int			size;
}				t_env;

void			minishell(t_env *env);
int				parse_line(char *line, t_env *env);
void			print_env(t_env env);
char			*parse_variable(char *arr, int i, int j, t_env *env);
char			*get_values_from_keys(char *arr, t_env *env);
int				parse_echo(char **arr);
int				parse_exec_command(char **arr, t_env env);
char			**unwrap(char **arr, t_env *env);
int				empty_space(t_env env);
char			**realloc_2d(t_env *env, int newsize);
t_env			copy_env(char **arr);
void			set_var(t_env *env, char *key, char *value);
void			unset_var(t_env *env, char *var);
char			*get_env(t_env *env, char *to_find);
int				parse_cd(char **arr, t_env *env);
int				check_permission(char *path);
int				exec_command(char **arr, t_env env);

#endif
