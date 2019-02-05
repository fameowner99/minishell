/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 12:30:17 by vmiachko          #+#    #+#             */
/*   Updated: 2019/02/05 12:32:02 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		unset_var(t_env *env, char *var)
{
	int		i;
	char	*str;

	str = ft_strjoin(var, "=");
	i = 0;
	while (i < env->size)
	{
		if (env->arr[i] && ft_strstr(env->arr[i], str))
		{
			free(env->arr[i]);
			free(str);
			env->arr[i] = NULL;
			return ;
		}
		++i;
	}
	free(str);
	ft_printf(RED"variable wasn't set.\n"RESET);
}

int			get_var_index(t_env *env, char *key)
{
	char	*str;
	int		i;

	if (!key)
		return (-1);
	str = ft_strjoin(key, "=");
	i = 0;
	while (i < env->size)
	{
		if (env->arr[i] && ft_strstr(env->arr[i], str))
		{
			free(str);
			return (i);
		}
		++i;
	}
	free(str);
	return (-1);
}

void		set_var(t_env *env, char *key, char *value)
{
	int		index;
	int		i;
	int		j;

	if ((index = get_var_index(env, key)) != -1)
	{
		free(env->arr[index]);
		env->arr[index] = NULL;
	}
	else if ((index = empty_space(*env)) == -1)
	{
		index = env->size;
		env->arr = realloc_2d(env, env->size * 2);
		env->size *= 2;
	}
	env->arr[index] = ft_memalloc(ft_strlen(key) + ft_strlen(value) + 2);
	j = 0;
	i = 0;
	while (key[i])
		env->arr[index][j++] = key[i++];
	env->arr[index][j++] = '=';
	i = 0;
	while (value[i])
		env->arr[index][j++] = value[i++];
}

void		print_env(t_env env)
{
	int		i;

	i = 0;
	while (i < env.size)
	{
		if (env.arr[i])
			ft_printf(YELLOW"%s\n"RESET, env.arr[i]);
		++i;
	}
}
