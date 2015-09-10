/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 01:03:37 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/10 19:44:14 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
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

int		rand_range(int min, int max)
{
	return ((rand() % max) + min);
}

char	*append_string(char *src, const char *str)
{
	char	*output;

	output = calloc(strlen(src) + strlen(str) + 1, sizeof(char));
	memcpy(output, src, strlen(src));
	strcat(output, str);
	free(src);
	return (output);
}
