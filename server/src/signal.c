/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fothon <fothon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/25 01:38:48 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/14 21:39:37 by fothon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"
#include <stdlib.h>
#include <signal.h>

static void	signal_int(int dummy)
{
	(void)dummy;
	network_disconnect();
	printf("%s\n", "toto");
	exit(0);
}

void		signal_bind(void)
{
	signal(SIGINT, signal_int);
}
