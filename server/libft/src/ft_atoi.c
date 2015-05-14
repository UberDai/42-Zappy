/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 17:16:30 by amaurer           #+#    #+#             */
/*   Updated: 2015/04/27 20:01:47 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

const char	*trim(char const *s)
{
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	return (s);
}

int			ft_atoi(char const *s)
{
	int		negative;
	int		n;

	n = 0;
	s = trim(s);
	if (*s == '-' || *s == '+')
	{
		negative = (*s == '-') ? 1 : 0;
		s++;
	}
	else
		negative = 0;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			n = (n * 10) + *s - '0';
		else
			break ;
		s++;
	}
	if (negative)
		n *= -1;
	return (n);
}
