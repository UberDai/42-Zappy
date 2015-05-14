/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 13:49:32 by amaurer           #+#    #+#             */
/*   Updated: 2013/11/19 13:55:38 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nbr)
{
	if (nbr < 0)
	{
		ft_putchar('-');
		if (nbr < -9)
			ft_putnbr(nbr / -10);
		ft_putchar(nbr % 10 * -1 + '0');
	}
	else
	{
		if (nbr > 9)
			ft_putnbr(nbr / 10);
		ft_putchar(nbr % 10 + '0');
	}
}
