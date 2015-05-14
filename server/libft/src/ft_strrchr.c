/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 15:49:35 by amaurer           #+#    #+#             */
/*   Updated: 2015/02/10 08:53:15 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, char c)
{
	char	*s2;

	s2 = (char *)s + ft_strlen(s);
	while (*s2 != c)
	{
		if (s2 == s)
			return (NULL);
		s2--;
	}
	return (s2);
}
