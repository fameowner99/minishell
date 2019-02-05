/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 12:28:50 by vmiachko          #+#    #+#             */
/*   Updated: 2019/02/05 12:29:40 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_length(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		++i;
	return (i);
}

int			empty_space(t_env env)
{
	int	i;

	i = 0;
	while (i < env.size)
	{
		if (env.arr[i] == NULL)
			return (i);
		++i;
	}
	return (-1);
}

t_env		copy_env(char **arr)
{
	t_env	res;
	int		i;

	res.size = get_length(arr);
	res.arr = malloc((res.size + 1) * sizeof(char *));
	i = 0;
	while (i < res.size)
	{
		res.arr[i] = strdup(arr[i]);
		++i;
	}
	res.arr[i] = NULL;
	return (res);
}

char		**realloc_2d(t_env *env, int newsize)
{
	char	**res;
	int		oldsize;
	int		i;

	oldsize = env->size;
	if (oldsize >= newsize)
		return (env->arr);
	res = malloc((newsize + 1) * sizeof(char *));
	i = 0;
	while (i < oldsize)
	{
		res[i] = env->arr[i];
		++i;
	}
	while (i < newsize)
	{
		res[i] = NULL;
		++i;
	}
	res[i] = NULL;
	free(env->arr);
	return (res);
}

char		*get_env(t_env *env, char *to_find)
{
	int		i;
	char	*str;

	if (!to_find)
		return (NULL);
	str = ft_strjoin(to_find, "=");
	i = 0;
	while (i < env->size)
	{
		if (env->arr[i] && ft_strstr(env->arr[i], str))
		{
			free(str);
			return (env->arr[i] + ft_strlen(str));
		}
		++i;
	}
	free(str);
	return (NULL);
}
