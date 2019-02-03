/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 20:40:30 by vmiachko          #+#    #+#             */
/*   Updated: 2019/02/03 13:06:56 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*my_join(char *p1, char *p2, int i, int j)
{
	char	*res;
	int		l1;
	int		l2;

	res = NULL;
	if (!p1 && p2)
		return (ft_strdup(p2));
	if (p1 && !p2)
		return (p1);
	if (!p1 && !p2)
		return (NULL);
	l1 = ft_strlen(p1);
	l2 = ft_strlen(p2);
	res = ft_memalloc(l1 + l2 + 1);
	i = 0;
	j = 0;
	while (i < l1)
		res[j++] = p1[i++];
	i = 0;
	while (i < l2)
		res[j++] = p2[i++];
	res[j] = '\0';
	free(p1);
	return (res);
}

static char	*alloc_join(char *arr, char *buf)
{
	if (buf[0])
	{
		arr = ft_realloc(arr, ft_strlen(arr) + ft_strlen(buf) + 1);
		arr = my_join(arr, buf, 0, 0);
		ft_memset(buf, '\0', MAXDIR);
	}
	return (arr);
}

static char	*join_variable(char *result, char *buf, char *tmp)
{
	result = ft_realloc(result, ft_strlen(result)
					+ ft_strlen(buf) + 1);
	result = my_join(result, tmp, 0, 0);
	return (result);
}

char		*parse_variable(char *arr, int i, int j)
{
	char	*result;
	char	buf[MAXDIR];
	char	*tmp;

	ft_memset(buf, '\0', MAXDIR);
	result = NULL;
	while (arr[i])
	{
		if (arr[i] == '$')
		{
			++i;
			j = 0;
			result = alloc_join(result, buf);
			while (arr[i] && arr[i] != '$' && arr[i] != '/')
				buf[j++] = arr[i++];
			if ((tmp = getenv(buf)))
				result = join_variable(result, buf, tmp);
			ft_memset(buf, '\0', MAXDIR);
			j = 0;
		}
		else
			buf[j++] = arr[i++];
	}
	result = alloc_join(result, buf);
	return (result);
}
