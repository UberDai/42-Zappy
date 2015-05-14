/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 14:55:16 by amaurer           #+#    #+#             */
/*   Updated: 2015/02/10 08:54:49 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtoupper(char const *s)
{
	char	*out;
	int		i;

	i = 0;
	out = ft_strdup(s);
	while (s[i])
	{
		out[i] = ft_toupper((char)s[i]);
		i++;
	}
	return (out);
}
