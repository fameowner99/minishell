/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 19:25:41 by vmiachko          #+#    #+#             */
/*   Updated: 2017/11/22 17:55:11 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strcpy(char *dest, char *src)
{
	size_t c;

	c = 0;
	while (src[c] != '\0')
	{
		dest[c] = src[c];
		++c;
	}
	dest[c] = src[c];
	return (dest);
}
