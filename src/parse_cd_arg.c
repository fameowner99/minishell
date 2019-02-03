/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cd_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 20:33:41 by vmiachko          #+#    #+#             */
/*   Updated: 2019/02/02 20:33:44 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*parse_home(char *path, int l_path)
{
	char	*result;
	char	*home;
	int		l_home;
	int		i;
	int		j;

	home = getenv("HOME");
	l_home = (int)ft_strlen(home);
	result = ft_memalloc(l_home + l_path);
	i = 0;
	j = 0;
	while (i < l_home)
		result[j++] = home[i++];
	i = 1;
	while (i < l_path)
		result[j++] = path[i++];
	path ? free(path) : 0;
	return (result);
}

int			check_tilda(char *path)
{
	if (path && path[0] && path[0] == '~' && path[1] != '~')
		return (TRUE);
	return (FALSE);
}

char		*parse_cd_arg(char *arr)
{
	char	*path;

	path = parse_variable(arr, 0, 0);
	if (check_tilda(path))
		path = parse_home(path, ft_strlen(path));
	return (path);
}
