/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 20:34:07 by vmiachko          #+#    #+#             */
/*   Updated: 2019/02/02 20:34:09 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_echo(char **arr)
{
	int i;

	i = 1;
	if (!ft_strcmp(arr[0], "echo"))
	{
		while (arr[i])
		{
			if (arr[i + 1])
				ft_printf(YELLOW"%s "RESET, arr[i]);
			else
				ft_printf(YELLOW"%s"RESET, arr[i]);
			++i;
		}
		ft_printf("\n");
		return (TRUE);
	}
	return (FALSE);
}
