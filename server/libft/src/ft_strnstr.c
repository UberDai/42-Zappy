/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:03:11 by amaurer           #+#    #+#             */
/*   Updated: 2014/02/03 13:35:42 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *s1, char const *s2, size_t n)
{
	size_t		i;
	size_t		j;

	i = 0;
	if (s2[0] == '\0')
		return (char*)(s1);
	while (s1[i] != '\0' && i < n)
	{
		j = 0;
		while (s1[i] == s2[j] && i < n)
		{
			i++;
			j++;
			if ((s2[j]) == '\0')
				return (char*)(&(s1[i - j]));
		}
		i++;
		i = i - j;
	}
	return (NULL);
}
