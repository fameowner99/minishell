/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 20:13:14 by vmiachko          #+#    #+#             */
/*   Updated: 2019/02/06 20:26:29 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			count_words(char *line)
{
	int		quote;
	int		i;
	int		w;

	quote = FALSE;
	w = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			++i;
		if (line[i] && !quote)
			++w;
		while (line[i] && line[i] != ' ' && line[i] != '\t')
		{
			if (line[i] == '"')
				quote = quote ? FALSE : TRUE;
			++i;
		}
	}
	return (w);
}

void		add_pointers(char **arr, char *line, int size, int i)
{
	int		quote;
	int		w;
	char	buf[size];
	int		j;

	quote = FALSE;
	w = 0;
	while (line[i])
	{
		while (line[i] && !quote && (line[i] == ' ' || line[i] == '\t'))
			++i;
		j = 0;
		ft_memset(buf, '\0', size);
		while (line[i] && ((line[i] != ' ' && line[i] != '\t') || quote))
		{
			if (line[i] == '"')
			{
				quote = quote ? FALSE : TRUE;
				++i;
			}
			(line[i] && line[i] != '"') ? buf[j++] = line[i++] : 0;
		}
		buf[0] ? (arr[w++] = ft_strdup(buf)) : 0;
	}
	arr[w] = NULL;
}

int			check_quotes(const char *line)
{
	int		i;
	int		c;

	c = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
			++c;
		++i;
	}
	return (c % 2 == 0);
}

char		**split_line(char *line)
{
	char	**arr;
	int		w;

	if (!check_quotes(line))
	{
		ft_printf(RED"minishell: wrong number of quotes\n"RESET);
		return (NULL);
	}
	w = count_words(line);
	if (!w)
		return (NULL);
	arr = (char**)malloc((w + 2) * sizeof(char *));
	add_pointers(arr, line, ft_strlen(line), 0);
	return (arr);
}
