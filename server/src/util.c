/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 01:03:37 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/16 00:07:38 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <sys/time.h>

double	get_time(void)
{
	static time_t	beginning;
	struct timeval	tod;
	double			ret;

	gettimeofday(&tod, NULL);

	if (beginning == 0)
		beginning = tod.tv_sec;

	ret = (double)(tod.tv_sec - beginning);
	ret += (double)tod.tv_usec / 1000000;

	return (ret);
}

int		die(const char *message)
{
	ft_putendl(message);
	exit(0);
	return (0);
}